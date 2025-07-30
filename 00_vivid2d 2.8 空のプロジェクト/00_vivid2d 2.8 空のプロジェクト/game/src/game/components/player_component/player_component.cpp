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
const float             PlayerComponent::m_jump_power = 1450.0f;
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
	, m_Velocity(CVector3::ZERO)
	, m_MoveSpeed(m_move_speed)
	, m_JumpPower(m_jump_power)
	, m_InitialPosition(transform.position)

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
	m_ForwardVector = CVector3::FORWARD;
    // ダミーのプレイヤーは動かず、浮かせる
    if (m_Controller->GetID() == CONTROLLER_ID::DUMMY)
    {
		m_Gravity = CVector3::ZERO;
    }
}

void PlayerComponent::Update(float delta_time, CGameObject* owner)
{
    switch (m_PlayerState)
    {
    case PLAYER_STATE::APPEAR:  Appear();           break;
    case PLAYER_STATE::PLAY:    Play(delta_time);   break;
    }

    // わずかな移動は無視するための閾値
    const float a_little_speed = 0.01f;

    // キャラクターに速度がある場合のみ、向きを変える
    if (m_Velocity.LengthSq() > a_little_speed)
    {
        // 移動している場合：目標の向きは、移動方向。m_ForwardVectorを更新する。
        m_ForwardVector = CVector3(m_Velocity.x, 0.0f, m_Velocity.z).Normalize();

    }
    float targetAngle = atan2f(m_ForwardVector.x, m_ForwardVector.z) * 180.0f / DX_PI_F;

    if (!std::isnan(targetAngle))

    {
        // 計算した角度をTransformComponentに設定する
        auto transform = owner->GetComponent<TransformComponent>();
        if (transform)
        {
            CVector3 currentRotation = transform->GetRotation();
            transform->SetRotation({ currentRotation.x, targetAngle, currentRotation.z });
        }
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
    if (m_Controller == nullptr) return false;
    bool Input = false;

    if (m_Controller)
    {
        vivid::Vector2 stick = m_Controller->GetLeftStick();

        CVector3 moveDir(stick.x, 0.0f, -stick.y);
        // スティックのデッドゾーン（無反応領域）処理。
        // アナログスティックのわずかな傾きや、ニュートラルポジションのズレを無視する。
        // LengthSq()は平方の値なので、0.5fは実際のスティック入力の大きさが約0.7以上の場合に反応することを意味する。
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
        // ベクトルを正規化して、長さを必ず 1 にする
        moveDir.Normalize();

        // 4. 長さ1の方向に、本来の移動速度を掛けて力を決定する
        m_Accelerator.x = moveDir.x * m_move_speed * m_MoveSpeedRate;
        m_Accelerator.z = moveDir.z * m_move_speed * m_MoveSpeedRate;
    }

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

void PlayerComponent::Move(float delta_time)
{
    if (!m_IsGround)
    {
        m_Velocity.y += m_Gravity.y * delta_time;
    }
    m_Velocity += m_Accelerator;
    CVector3 total_velocity = m_Velocity + m_AffectedVelocity;
    CVector3 totalMoveThisFrame = total_velocity * delta_time;


    SubstepMove(totalMoveThisFrame);

    if (m_FrictionFlag)
    {
        m_Velocity.x *= m_move_friction.x;
        m_Velocity.z *= m_move_friction.z;
    }
    m_Accelerator = CVector3::ZERO;
    m_AffectedVelocity = CVector3::ZERO;
}

void PlayerComponent::HandleGroundCollisions(CGameObject* owner)
{
    auto transform = m_Owner->GetComponent<TransformComponent>();
    if (!transform) return;
    CObjectManager& om = CObjectManager::GetInstance();

    const float ground_check_line_length = 100.0f;
    const float ground_check_offset = m_radius * 0.7f;
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

        if (auto hitObject = om.CheckHitLineForAll(startPos, endPos, m_Owner, hitResult))
        {
            if (hitObject->GetTag() == GAME_OBJECT_TAG::FLOOR)
            {
                // hitNormal: レイが当たった面の法線（面に垂直なベクトル）
                // CVector3::UP: 真上を示すベクトル(0, 1, 0)
                 // 2つのベクトルの内積を計算し、面の傾きを調べる
                float dot = CVector3::Dot(hitResult.hitNormal, CVector3::UP);
                // 内積の値が1に近いほど、法線が真上を向いている（＝平坦な地面である）ことを示す
                 // 0.9f は約25.8度以下の傾斜を「歩ける地面」とみなす、という設定
                if (dot > 0.9f)
                {
                    foundGroundThisFrame = true;
                    tempGroundObject = hitObject.get();

                    // 9本のレイの中で、最も高い位置にある地面のY座標を記録する
                    if (hitResult.hitPosition.y > highestGroundY)
                    {
                        highestGroundY = hitResult.hitPosition.y;
                    }
                }
            }
        }
    }

    CVector3 currentPos = transform->GetPosition();
    float distanceToGround = currentPos.y - (highestGroundY + m_height / 2.0f);

    // 「地面が見つかり」「落下中」で、かつ「地面が足元のごく近くにある」場合のみ接地しているとみなす
    const float snap_distance = 10.0f; // この距離以内なら吸い付く
    if (foundGroundThisFrame && m_Velocity.y <= 0 && distanceToGround <= snap_distance)
    {
        //　床の表面の高さ
        float groundSurfaceY = highestGroundY + (m_height / 2.0f);

        m_IsGround = true;
        m_GroundObject = tempGroundObject;
        m_Velocity.y = 0;
        transform->SetPosition({ currentPos.x, groundSurfaceY, currentPos.z });
    }
    else
    {
        m_IsGround = false;
        m_GroundObject = nullptr;
    }

}


void PlayerComponent::HandleWallCollisions(CGameObject* owner)
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

void PlayerComponent::HandleCeilingCollisions(CGameObject* owner)
{
    auto transform = owner->GetComponent<TransformComponent>();
    if (!transform) return;

    // 上昇中でなければ天井衝突判定は不要
    if (m_Velocity.y <= 0)
    {
        return;
    }

    // レイの長さを定義（キャラクターの半分の高さ + α）
    const float rayLength = (m_height / 2.0f) + 5.0f;
    // レイを飛ばす位置の水平方向のオフセット
    const float rayHorizontalOffset = m_radius * 0.7f;

    CVector3 currentPos = transform->GetPosition();
    // キャラクターの中心から頭上へ向かって3x3の格子状にレイを飛ばす
    for (int i = 0; i < 9; i++)
    {
        // 格子状のレイのオフセットを計算
        float col = static_cast<float>(i % 3) - 1.0f; // 結果は -1, 0, 1 のいずれか
        float row = static_cast<float>(i / 3) - 1.0f; // 結果は -1, 0, 1 のいずれか

        CVector3 offset(col * rayHorizontalOffset, 0.0f, row * rayHorizontalOffset);

        // 四隅のレイの長さを調整し、円形に近づける
        if (col != 0.0f && row != 0.0f)
        {
            offset *= 0.707f; // sin(45度) の近似値
        }   
        
        // レイの始点と終点
        CVector3 startPos = currentPos + offset;
        CVector3 endPos = startPos + CVector3(0.0f, rayLength, 0.0f); // Y+方向（上）へ

        CollisionResult hitResult;

        if (auto hitObject = CObjectManager::GetInstance().CheckHitLineForAll(startPos, endPos, owner, hitResult))
        {
            if (hitObject->GetTag() == GAME_OBJECT_TAG::WALL || hitObject->GetTag() == GAME_OBJECT_TAG::FLOOR)
            {
                // 天井に衝突した場合、Y方向の速度を0にする
                m_Velocity.y = 0;

                // めり込み分を計算して押し戻す
                float penetrationDepth = endPos.y - hitResult.hitPosition.y;
                transform->Translate(CVector3(0.0f, -penetrationDepth, 0.0f));

                // 1点でも衝突したら、このフレームでの天井判定は終了して良い
                return;
            }
        }
    }
}

void PlayerComponent::SubstepMove(const CVector3& totalMove, int maxSubsteps)
{
    auto transform = m_Owner->GetComponent<TransformComponent>();
    if (!transform) return;

    float totalMoveLength = totalMove.Length(totalMove);
    if (totalMoveLength < 0.001f) return;

    // サブステップの回数を計算
    int substeps = static_cast<int>(ceilf(totalMoveLength / (m_radius * 0.5f)));
    if (substeps > maxSubsteps) substeps = maxSubsteps;
    if (substeps < 1) substeps = 1;

    // 1サブステップあたりの移動量
    CVector3 substepMove = totalMove / static_cast<float>(substeps);

    // 分割して移動と衝突判定を繰り返す
    for (int i = 0; i < substeps; ++i)
    {
        // === 水平方向の移動 (XとZを分離) ===

        // 1. まずはX軸方向に動かしてみる
        transform->Translate(CVector3(substepMove.x, 0.0f, 0.0f));
        HandleWallCollisions(m_Owner); // 壁の衝突判定

        // 2. 次にZ軸方向に動かしてみる
        transform->Translate(CVector3(0.0f, 0.0f, substepMove.z));
        HandleWallCollisions(m_Owner); // 壁の衝突判定


        // === 垂直方向の移動 (地面と天井) ===

        // 3. 最後にY軸方向に動かしてみる
        transform->Translate(CVector3(0.0f, substepMove.y, 0.0f));

        if (substepMove.y > 0)
        {
            // 上昇中 -> 天井との判定
            HandleCeilingCollisions(m_Owner);
        }
        else
        {
            // 落下中 -> 地面との判定
            HandleGroundCollisions(m_Owner);
        }
    }
}