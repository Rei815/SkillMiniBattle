#include "player_component.h"
#include "../../../engine/managers/controller_manager/controller_manager.h"
#include "../../../engine/core/game_object/game_object.h"
#include "../../../engine/components/transform_component/transform_component.h"
#include "../../../engine/components/model_component/model_component.h"
#include "../../../engine/managers/object_manager/object_manager.h"
#include "../../../engine/managers/effect_manager/effect_manager.h"
#include "../../../engine/managers/skill_manager/skill/skill.h"
const float             PlayerComponent::m_radius = 50.0f;
const float             PlayerComponent::m_height = 70.0f;
const float             PlayerComponent::m_model_scale = 0.33f;
const float             PlayerComponent::m_move_speed = 40.0f;
const float             PlayerComponent::m_jump_power = 1600.0f;
const float             PlayerComponent::m_fly_away_speed = 2400.0f;
const float             PlayerComponent::m_max_life = 3.0f;
const float             PlayerComponent::m_max_invincible_time = 1.0f;
const float             PlayerComponent::m_fall_accelerator = 0.025f;
const CVector3          PlayerComponent::m_move_friction = CVector3(0.9f, 0.975f, 0.9f);
const int               PlayerComponent::m_invincible_visible_interval = 4;
const float             PlayerComponent::m_alpha_speed = 0.025f;
const CVector3          PlayerComponent::m_gravity = CVector3(0.0f, -5000.0f, 0.0f);
const COLOR_F PlayerComponent::m_player_body_color[] =
{
    { 1.0f, 0.66f, 0.66f, 1.0f }, // Player1 (0xffffaaaa)
    { 0.66f, 0.66f, 1.0f, 1.0f }, // Player2 (0xffaaaaff)
    { 1.0f, 1.0f, 0.66f, 1.0f }, // Player3 (0xffffffaa)
    { 0.66f, 1.0f, 0.66f, 1.0f }  // Player4 (0xffaaffaa)
};

const COLOR_F PlayerComponent::m_player_eye_color[] =
{
    { 0.4f, 0.0f, 0.0f, 1.0f }, // Player1 (0xff660000)
    { 0.0f, 0.0f, 0.4f, 1.0f }, // Player2 (0xff000066)
    { 0.4f, 0.4f, 0.0f, 1.0f }, // Player3 (0xff666600)
    { 0.0f, 0.4f, 0.0f, 1.0f }  // Player4 (0xff006600)
};

PlayerComponent::PlayerComponent(PLAYER_ID id, CTransform transform)
    : m_MoveSpeedRate(1.0f)
    , m_JumpPowerRate(1.0f)
    , m_Skill(nullptr)
    , m_Accelerator(CVector3::ZERO)
    , m_InvincibleTimer(m_max_invincible_time)
    , m_StopFlag(false)
    , m_FrictionFlag(true)
    , m_ActionFlag(true)
    , m_Controller(nullptr)
    , m_ForwardVector(CVector3::FORWARD)
    , m_AffectedVelocity(CVector3::ZERO)
    , m_ActiveFlag(true)
    , m_PlayerID(id)
    , m_InvincibleFlag(false)
    , m_PlayerState(PLAYER_STATE::APPEAR)
    , m_Alpha(0.0f)
    , m_DefeatFlag(false)
    , m_Gravity(m_gravity)
	, m_IsGround(false)
    , m_GroundObject(nullptr)
{
}

void PlayerComponent::OnAttach(CGameObject* owner)
{
    CControllerManager& cm = CControllerManager::GetInstance();
    CControllerManager::CONTROLLER_LIST controllerList = cm.GetList();
    CControllerManager::CONTROLLER_LIST::iterator it = controllerList.begin();
	m_Owner = owner;
    //IDによってカテゴリーの切り替え
    switch (m_PlayerID)
    {
    case PLAYER_ID::PLAYER1:
        m_Owner->SetCategory(FACTION_CATEGORY::PLAYER1);
        break;
    case PLAYER_ID::PLAYER2:
        m_Owner->SetCategory(FACTION_CATEGORY::PLAYER2);
        break;
    case PLAYER_ID::PLAYER3:
        m_Owner->SetCategory(FACTION_CATEGORY::PLAYER3);
        break;
    case PLAYER_ID::PLAYER4:
        m_Owner->SetCategory(FACTION_CATEGORY::PLAYER4);
        break;
    }
    //コントローラーに設定されているUnitIDと合っている場合自身のコントローラーとして取得
    while (it != controllerList.end())
    {
        if ((*it)->GetPlayerID() == m_PlayerID)
        {
            m_Controller = std::shared_ptr<CController>(*it);
            break;
        }
        ++it;
    }
    auto transform = owner->GetComponent<TransformComponent>();
    owner->GetComponent<TransformComponent>()->SetScale(CVector3(m_model_scale, m_model_scale, m_model_scale));

    m_InitialPosition = transform->GetPosition();
    auto model = owner->GetComponent<ModelComponent>();
    model->SetMaterialColor(0, m_player_body_color[(int)m_PlayerID]);
    model->SetMaterialColor(1, m_player_eye_color[(int)m_PlayerID]);

    m_InvincibleTimer.SetUp(m_max_invincible_time);

    m_StopFlag = false;
    m_FrictionFlag = true;

    // ダミーのプレイヤーは動かず、浮かせる
    if (m_Controller->GetID() == CONTROLLER_ID::DUMMY)
    {
		m_Gravity = CVector3::ZERO;
    }
}

void PlayerComponent::Update(float delta_time, CGameObject* owner)
{
    // オーナーのポインタを保持
    m_Owner = owner;
    switch (m_PlayerState)
    {
    case PLAYER_STATE::APPEAR:  Appear();           break;
    case PLAYER_STATE::PLAY:    Play(delta_time);   break;
    case PLAYER_STATE::DEFEAT:  Defeat();           break;
    }

    // わずかな移動は無視するための閾値
    const float a_little_speed = 0.01f;

    // キャラクターに速度がある場合のみ、向きを変える
    if (m_Velocity.LengthSq() > a_little_speed)
    {
        // 1. 移動速度ベクトルから目標の角度を計算 (atan2fを使用)
        float targetAngle = atan2f(m_Velocity.x, m_Velocity.z) * 180.0f / DX_PI_F;


        // 2. 計算した角度を即座にTransformに設定
        auto transform = owner->GetComponent<TransformComponent>();
        CVector3 rotation = transform->GetRotation();
        rotation.y = targetAngle;
        m_ForwardVector = CVector3(m_Velocity.x, 0, m_Velocity.z).Normalize();
        transform->SetRotation(rotation);
    }

}
/*
 *  被弾
 */
void PlayerComponent::HitBullet(std::shared_ptr<IBullet> bullet, CVector3 hit_position)
{
    if (m_InvincibleFlag)
        return;

    m_ActionFlag = false;
    m_FrictionFlag = false;
    m_InvincibleFlag = true;
    m_IsGround = false;
    m_Accelerator = CVector3::ZERO;
    m_Accelerator.y = m_jump_power;

    //衝撃を与える
    Impact(hit_position, bullet->GetVelocity().Normalize(), bullet->GetPower());
}

/*
*  衝撃
*/
void PlayerComponent::Impact(const CVector3& hit_position, const CVector3& direction, float power)
{
    auto transform = m_Owner->GetComponent<TransformComponent>();
    //当たった向きを取得
    CVector3 TempVelocity = (transform->GetPosition() -hit_position);

    //垂直方向の速度は最後に計算するので、一度ゼロにする
    TempVelocity.y = 0.0f;

    //ベクトルの大きさを２にする
    TempVelocity = TempVelocity.Normalize() * 2.0f;

    //弾の速度ベクトルの大きさを１にして加算する（当たった向きと弾の速度が真逆の場合に、水平方向の速度が打ち消されるのを防ぐため）
    TempVelocity += direction;

    //垂直方向の速度は最後に計算するので、再びゼロにする
    TempVelocity.y = 0.0f;

    //速度を倍率で調整するため、ベクトルの大きさを１にする
    TempVelocity = TempVelocity.Normalize();

    //垂直方向のベクトルを追加
    TempVelocity.y = 0.2f;

    //自身の移動速度をゼロにし、外部からの影響による移動速度をベクトルとその倍率でセットする
    m_Velocity = CVector3::ZERO;

    // 2. 計算した吹き飛ばしベクトルを、直接 m_Velocity に加算する！
    m_Velocity += TempVelocity * m_fly_away_speed * power;

    // SetAffectedVelocity の呼び出しは削除する
    // SetAffectedVelocity(TempVelocity * m_fly_away_speed * power);
}

PLAYER_ID PlayerComponent::GetPlayerID() const
{
    return m_PlayerID;
}

bool PlayerComponent::IsDefeated() const
{
    return m_DefeatFlag;
}

void PlayerComponent::SetDefeated(bool flag)
{
    m_DefeatFlag = flag;
}

bool PlayerComponent::IsInvincible(void)
{
    return m_InvincibleFlag;
}

void PlayerComponent::SetInvincible(bool flag)
{
    m_InvincibleFlag = flag;
}

void PlayerComponent::SetSkill(std::shared_ptr<CSkill> skill)
{
    m_Skill = skill;
}

bool PlayerComponent::IsGround() const
{
    return m_IsGround;
}

void PlayerComponent::SetActionFlag(bool flag)
{
    m_ActionFlag = flag;
}

bool PlayerComponent::GetPlayerMoving()
{
    bool Input = false;



    if (m_Controller)
    {
        vivid::Vector2 stick = m_Controller->GetLeftStick();

        CVector3 moveDir(stick.x, 0.0f, -stick.y);
        // 2. ベクトルの長さが少しでもあれば（＝入力があれば）処理する
        if (moveDir.LengthSq() > 0.5f && !m_StopFlag) // わずかな入力のブレは無視
        {
            Input = true;

        }

        //ジャンプ
        if (m_Controller->GetButtonDown(BUTTON_ID::A) && !m_StopFlag)
            Input = true;

    }


    return Input;
}

void PlayerComponent::SetForwardVector(const CVector3& forward_vector)
{
    if (forward_vector != CVector3::ZERO)
    {
        m_ForwardVector = forward_vector;
    }
}

CVector3 PlayerComponent::GetForwardVector()
{
    return m_ForwardVector;
}

std::shared_ptr<CSkill> PlayerComponent::GetSkill()
{
    return m_Skill;
}

float PlayerComponent::GetHeight()
{
    return m_height;
}

float PlayerComponent::GetRadius()
{
    return m_radius;
}

CVector3 PlayerComponent::GetVelocity()
{
    return m_Velocity;
}

CVector3 PlayerComponent::GetDefaultGravity()
{
    return m_gravity;
}

void PlayerComponent::SetVelocity(const CVector3& velocity)
{
    m_Velocity = velocity;
}

void PlayerComponent::SetGravity(const CVector3& gravity)
{
    m_Gravity = gravity;;
}

void PlayerComponent::SetIsGround(bool isGround)
{
    m_IsGround = isGround;
}

void PlayerComponent::SetGroundObject(CGameObject* gameObject)
{
    m_GroundObject = gameObject;
}

void PlayerComponent::SetAffectedVelocity(CVector3 velocity)
{
    m_AffectedVelocity = velocity;
}

void PlayerComponent::AddAffectedVelocity(CVector3 velocity)
{
    m_AffectedVelocity += velocity;
}

void PlayerComponent::StartInvincible(float invincible_time)
{
    m_InvincibleFlag = true;
    m_InvincibleTimer.SetUp(invincible_time);
}

void PlayerComponent::Control(void)
{
    if (m_Controller == nullptr) return;
    vivid::Vector2 stick = m_Controller->GetLeftStick();
    // 1. スティックの入力から、まずは「行きたい方向」のベクトルを作る
    // ※コントローラーは上方向がマイナスで返ってくることが多いため、Z成分は反転させています
    CVector3 moveDir(stick.x, 0.0f, -stick.y);

    // 2. ベクトルの長さが少しでもあれば（＝入力があれば）処理する
    if (moveDir.LengthSq() > 0.01f) // わずかな入力のブレは無視
    {
        // 3. ★★★ ここが最重要ポイント ★★★
        // ベクトルを正規化して、長さを必ず 1 にする
        moveDir.Normalize();

        // 4. 長さ1の方向に、本来の移動速度を掛けて力を決定する
        m_Accelerator.x = moveDir.x * m_move_speed * m_MoveSpeedRate;
        m_Accelerator.z = moveDir.z * m_move_speed * m_MoveSpeedRate;
    }

    // --- ▲▲▲ ここまでが移動処理 ▲▲▲ ---
    //ジャンプ
    if (m_Controller->GetButtonDown(BUTTON_ID::A) && !m_StopFlag)
        if (m_IsGround == true)
        {
            m_GroundObject = nullptr;
            m_IsGround = false;

            m_Accelerator.y = m_jump_power * m_JumpPowerRate;

            auto transform = m_Owner->GetComponent<TransformComponent>();
            CEffectManager::GetInstance().Create(EFFECT_ID::JUMP, transform->GetPosition());

        }

    //スキル
    if (m_Skill != nullptr)
        if (m_Controller->GetButtonDown(BUTTON_ID::B) && !m_StopFlag)
            m_Skill->Action();

}

void PlayerComponent::Move(float delta_time)
{
    auto transform = m_Owner->GetComponent<TransformComponent>();
    if (!transform) return;

    // --- 1. 力の計算 ---
    // このフレームで動きたい速度ベクトルを、これまで通り計算します
    m_Velocity += m_Accelerator;
    if (!m_IsGround)
    {
        m_Velocity += m_Gravity * delta_time;
    }
    m_Velocity += m_AffectedVelocity * delta_time;

    // --- 2. 水平方向（X, Z）の移動と衝突解決 ---
    CVector3 horizontalVelocity = CVector3(m_Velocity.x, 0.0f, m_Velocity.z);
    transform->Translate(horizontalVelocity * delta_time);
    HandleWallCollisions(delta_time, m_Owner); // 横に動かした結果、壁にめり込んだら押し戻す

    // --- 3. 垂直方向（Y）の移動と衝突解決 ---
    CVector3 verticalVelocity = CVector3(0.0f, m_Velocity.y, 0.0f);
    transform->Translate(verticalVelocity * delta_time);
    HandleCeilingCollisions(delta_time, m_Owner); // 上に動かした結果、天井にめり込んだら押し戻す

    // --- 4. 接地判定と補正 ---
    // 全ての移動が終わった最終的な位置で、接地しているかを確認
    CObjectManager& om = CObjectManager::GetInstance();
    const float ground_check_line_length = (m_height / 2.0f) + 5.0f;
    const float ground_check_offset = m_radius * 0.9f;
    bool foundGroundThisFrame = false;
    float highestGroundY = -FLT_MAX;
    CGameObject* tempGroundObject = nullptr;

    for (int i = 0; i < 9; i++)
    {
        float groundMultiplier = 1.0f;

        // 床の判定を円のようにするための倍率設定
        if ((i % 3) != 1 && (i / 3) != 1)
            groundMultiplier = sinf(45.0f * DX_PI_F / 180.0f);
        CVector3 currentPos = transform->GetPosition();
        CVector3 startPos = currentPos + CVector3((-ground_check_offset + ground_check_offset * (i % 3)) * groundMultiplier, 0.0f, (-ground_check_offset + ground_check_offset * (i / 3)) * groundMultiplier);
        CVector3 endPos = startPos - CVector3(0, ground_check_line_length, 0);
        CollisionResult hitResult;
        DrawLine3D(startPos, endPos, 0xFF0000);

        if (auto hitObject = om.CheckHitLineForAll(startPos, endPos, m_Owner, hitResult))
        {
            if (hitObject->GetTag() == GAME_OBJECT_TAG::FLOOR)
            {
                float dot = CVector3::Dot(hitResult.hitNormal, CVector3::UP);
                if (dot > 0.9f)
                {
                    foundGroundThisFrame = true;
                    tempGroundObject = hitObject.get();
                    if (hitResult.hitPosition.y > highestGroundY)
                    {
                        highestGroundY = hitResult.hitPosition.y;
                    }
                }
            }
        }
    }

    if (foundGroundThisFrame && m_Velocity.y <= 0)
    {
        m_IsGround = true;
        m_GroundObject = tempGroundObject;
        m_Velocity.y = 0;
        CVector3 currentPos = transform->GetPosition();
        transform->SetPosition(CVector3(currentPos.x, highestGroundY + (m_height / 2.0f), currentPos.z));
    }
    else
    {
        m_IsGround = false;
        m_GroundObject = nullptr;
    }

    // --- 5. 後処理 ---
    if (m_FrictionFlag)
    {
        m_Velocity.x *= m_move_friction.x;
        m_Velocity.z *= m_move_friction.z;
        m_AffectedVelocity *= m_move_friction;
    }
    m_Accelerator = CVector3::ZERO;
}

void PlayerComponent::Impact(const CVector3& direction, float power)
{
}

void PlayerComponent::Appear(void)
{
    RevertAlpha();
    if (m_Alpha == 1.0f)
        m_PlayerState = PLAYER_STATE::PLAY;
}

void PlayerComponent::Play(float delta_time)
{

    if (m_ActionFlag)
        Control();
    Move(delta_time);

	// 無敵時間中の処理
    if (!m_InvincibleFlag)
        return;

    m_InvincibleTimer.Update();
    if (m_InvincibleTimer.Finished())
    {
        m_InvincibleTimer.SetUp(m_max_invincible_time);

        m_InvincibleFlag = false;
    }

}

void PlayerComponent::Defeat(void)
{
}

void PlayerComponent::DecAlpha(float alpha)
{
    //アルファ値が設定値になったら終了
    if (m_Alpha == alpha)
    {
        m_Alpha = alpha;
        return;
    }

    if (m_Alpha > 0.0f)
        m_Alpha -= m_alpha_speed;
    else
        m_Alpha = 0.0f;

    auto ModelComp = m_Owner->GetComponent<ModelComponent>();
   ModelComp->SetAlpha(m_Alpha);

}

void PlayerComponent::RevertAlpha(float alpha)
{
    //アルファ値が設定値になったら終了
    if (m_Alpha >= alpha)
    {
        m_Alpha = alpha;
        return;
    }

    m_Alpha += m_alpha_speed;

    auto ModelComp = m_Owner->GetComponent<ModelComponent>();
    ModelComp->SetAlpha(m_Alpha);
}

void PlayerComponent::SetAlpha(float alpha)
{
    m_Alpha = alpha;
    auto ModelComp = m_Owner->GetComponent<ModelComponent>();
    ModelComp->SetAlpha(m_Alpha);

}

void PlayerComponent::SetMoveSpeedRate(float rate)
{
    m_MoveSpeedRate = rate;
}

void PlayerComponent::MulMoveSpeedRate(float rate)
{
    if (rate == 0.0f)
        return;

    m_MoveSpeedRate = m_MoveSpeedRate * rate;
}

void PlayerComponent::DivMoveSpeedRate(float rate)
{
    if (rate == 0.0f)
        return;

    m_MoveSpeedRate = m_MoveSpeedRate / rate;
}

void PlayerComponent::SetJumpPowerRate(float rate)
{
    m_JumpPowerRate = rate;
}

void PlayerComponent::MulJumpPowerRate(float rate)
{
    if (rate == 0.0f)
        return;

    m_JumpPowerRate = m_JumpPowerRate * rate;
}

void PlayerComponent::DivJumpPowerRate(float rate)
{
    if (rate == 0.0f)
        return;

    m_JumpPowerRate = m_JumpPowerRate / rate;
}

void PlayerComponent::HandleWallCollisions(float delta_time, CGameObject* owner)
{
    auto transform = owner->GetComponent<TransformComponent>();
    if (!transform) return;

    // 8方向（45度ごと）にレイを飛ばして壁をチェック
    for (int i = 0; i < 8; ++i)
    {
        CVector3 currentPos = transform->GetPosition();

        // チェックする方向のベクトルを計算
        // プレイヤーの前方を基準に回転させると、カメラに追従する移動などで便利
        // ここでは単純化のため、ワールド座標のZ+を前方として計算します
        float angle = 45.0f * i;
        CVector3 checkDir = CVector3(sinf(angle * DX_PI_F / 180.0f), 0.0f, cosf(angle * DX_PI_F / 180.0f));

        // レイの始点と終点
        CVector3 startPos = currentPos;
        // レイの長さはキャラクターの半径と同じにする
        CVector3 endPos = startPos + checkDir * m_radius;

        CollisionResult hitResult;
        // 自分自身を除外して、線分と他のオブジェクトの当たり判定を行う
        if (auto hitObject = CObjectManager::GetInstance().CheckHitLineForAll(startPos, endPos, owner, hitResult))
        {
            if (hitObject->GetTag() == GAME_OBJECT_TAG::WALL || hitObject->GetTag() == GAME_OBJECT_TAG::FLOOR)
            {
                // ヒットした場合、めり込んだ分だけ押し出す
                CVector3 pushBackVector = endPos - hitResult.hitPosition;
                transform->Translate(-pushBackVector);
                // 2. 壁方向に進もうとする速度を打ち消す（すり抜け対策）
                CVector3 wallNormal = -checkDir; // 壁の法線は、レイの向きと逆
                float speedIntoWall = CVector3::Dot(m_Velocity, wallNormal);

                // 壁に向かう速度成分がある場合
                if (speedIntoWall > 0)
                {
                    // その速度成分を打ち消すベクトルを速度から引く
                    m_Velocity -= wallNormal * speedIntoWall;
                }
            }
        }
    }
}

void PlayerComponent::HandleCeilingCollisions(float delta_time, CGameObject* owner)
{
    auto transform = owner->GetComponent<TransformComponent>();
    if (!transform) return;

    // ★★★ 上昇中でなければ、天井判定は行わない ★★★
    if (m_Velocity.y <= 0)
    {
        return;
    }

    float headY = transform->GetPosition().y + (m_height / 2.0f);
    float rayLength = (m_height / 2.0f) + 5.0f;
    const float ground_check_offset_x = m_radius * 0.9f;

    for (int i = 0; i < 9; i++)
    {
        CVector3 currentPos = transform->GetPosition();

        CVector3 startPos = currentPos + CVector3(-ground_check_offset_x + (ground_check_offset_x) * (i % 3), 0.0f, -ground_check_offset_x * (i / 3));
        CVector3 endPos = startPos - CVector3(0, -rayLength, 0);

        CollisionResult hitResult;
        DrawLine3D(startPos, endPos, 0xFF0000);

        if (auto hitObject = CObjectManager::GetInstance().CheckHitLineForAll(startPos, endPos, owner, hitResult))
        {
            // 1. 上昇速度をゼロにする
            m_Velocity.y = 0;

            // 2. めり込んだ分だけ、下に押し出す
            float pushDownDistance = (startPos.y + rayLength) - hitResult.hitPosition.y;
            transform->Translate(CVector3(0, -pushDownDistance, 0));
        }
    }
}