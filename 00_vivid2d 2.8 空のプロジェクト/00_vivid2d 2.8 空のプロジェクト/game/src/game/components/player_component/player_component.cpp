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
const float             PlayerComponent::m_move_speed = 0.6f;
const float             PlayerComponent::m_jump_power = 20.0f;
const float             PlayerComponent::m_fly_away_speed = 40.0f;
const float             PlayerComponent::m_max_life = 3.0f;
const float             PlayerComponent::m_max_invincible_time = 1.0f;
const float             PlayerComponent::m_fall_accelerator = 0.025f;
const CVector3          PlayerComponent::m_move_friction = CVector3(0.9f, 0.975f, 0.9f);
const int               PlayerComponent::m_invincible_visible_interval = 4;
const float             PlayerComponent::m_alpha_speed = 0.025f;
const CVector3          PlayerComponent::m_gravity = CVector3(0.0f, -0.85f, 0.0f);
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
    , m_Alpha()
    , m_DefeatFlag(false)
    , m_Gravity(m_gravity)
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
    model->SetMaterialColor(1, m_player_body_color[(int)m_PlayerID]);

    m_Accelerator = CVector3(0, 0, 0);

    m_InvincibleTimer.SetUp(m_max_invincible_time);

    m_StopFlag = false;
    m_FrictionFlag = true;

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
    SetAffectedVelocity(TempVelocity * m_fly_away_speed * power);
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
    m_ActiveFlag = flag;
}

bool PlayerComponent::GetPlayerMoving()
{
    bool Input = false;

    if (m_Controller)
    {
        vivid::Vector2 stick = m_Controller->GetLeftStick();

        //左移動
        if ((stick != vivid::Vector2::ZERO && stick.x < -0.5f))
            Input = true;

        //右移動
        if ((stick != vivid::Vector2::ZERO && stick.x > 0.5f))
            Input = true;

        //上移動
        if ((stick != vivid::Vector2::ZERO && stick.y < -0.5f))
            Input = true;

        //下移動
        if ((stick != vivid::Vector2::ZERO && stick.y > 0.5f))
            Input = true;

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
    //左移動
    if ((stick != vivid::Vector2::ZERO && stick.x < -0.5f))
        m_Accelerator.x += -m_move_speed * m_MoveSpeedRate;

    //右移動
    if ((stick != vivid::Vector2::ZERO && stick.x > 0.5f))
        m_Accelerator.x += m_move_speed * m_MoveSpeedRate;
    //上移動
    if ((stick != vivid::Vector2::ZERO && stick.y < -0.5f))
        m_Accelerator.z += m_move_speed * m_MoveSpeedRate;

    //下移動
    if ((stick != vivid::Vector2::ZERO && stick.y > 0.5f))
        m_Accelerator.z += -m_move_speed * m_MoveSpeedRate;


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
    m_Velocity += m_Gravity;

    // --- 位置情報の取得と更新 ---
    // 変更前：m_Transform.position += m_Velocity;
    // 変更後：
    auto transform = m_Owner->GetComponent<TransformComponent>();
    if (transform)
    {
        transform->Translate(m_Velocity * delta_time);
    }

    // --- 接地判定 ---
        //一度接地したらジャンプや判定の外に行かない限り接地したオブジェクトに追従する
    CObjectManager& om = CObjectManager::GetInstance();
    const float ground_check_line_length = 100.0f;
    const float ground_check_offset_x = m_radius - m_radius / 3.0f;

    for (int i = 0; i < 9; i++)
    {
        CVector3 startPos = transform->GetPosition() + CVector3(-ground_check_offset_x + (ground_check_offset_x) * (i % 3), 0.0f, -ground_check_offset_x + (ground_check_offset_x) * (i / 3));
        CVector3 endPos = startPos - CVector3(0, ground_check_line_length, 0);
        CVector3 hitPos;
        if (auto hitObject = om.CheckHitLineForAll(startPos, endPos, m_Owner, hitPos))
        {
            if (hitObject->GetTag() == GameObjectTag::FLOOR) // 仮のID
            {
                m_GroundObject = hitObject.get();
                m_IsGround = true;
                m_Velocity.y = 0;
            }
        }
        else
        {
            m_GroundObject = nullptr;
            m_IsGround = false;
        }

    }
    if (m_GroundObject)
    {
        CVector3 position = transform->GetPosition();
        auto groundObjectTransform = m_GroundObject->GetComponent<TransformComponent>();
        CVector3 groundObjectPosition = groundObjectTransform->GetPosition();
        transform->SetPosition(CVector3(position.x, groundObjectPosition.y + m_radius, position.z));
    }

    if (!m_StopFlag)
    {
        m_Velocity += m_Accelerator;
        m_Velocity + m_AffectedVelocity;
    }
    //摩擦による減速
    if (m_FrictionFlag)
    {
        m_Velocity.x *= m_move_friction.x;
        m_Velocity.y *= m_move_friction.y;
        m_Velocity.z *= m_move_friction.z;

        m_AffectedVelocity.x *= m_move_friction.x;
        m_AffectedVelocity.y *= m_move_friction.y;
        m_AffectedVelocity.z *= m_move_friction.z;
    }

    //地上なら落ちないように
    if (m_IsGround)
    {
        if (m_Velocity.y > 0.0f)
            m_Velocity.y = 0.0f;

        if (m_AffectedVelocity.y > 0.0f)
            m_AffectedVelocity.y = 0.0f;
    }

    m_Accelerator = CVector3::ZERO;

}
void PlayerComponent::Impact(const CVector3& direction, float power)
{
}

void PlayerComponent::Appear(void)
{
}

void PlayerComponent::Play(float delta_time)
{
    if (m_ActionFlag)
    {
        Control();
    }
    Move(delta_time);

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

void PlayerComponent::RevertAlpha(float alpha = 1.0f)
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
