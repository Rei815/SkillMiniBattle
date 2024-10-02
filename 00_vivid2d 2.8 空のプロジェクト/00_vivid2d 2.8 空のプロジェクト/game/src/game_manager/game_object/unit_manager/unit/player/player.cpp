#include "player.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../camera/camera.h"
#include "../../unit_manager.h"
#include "../../../ui_manager/ui_manager.h"


const float             CPlayer::m_radius = 50.0f;

const float             CPlayer::m_move_speed = 0.5f;
const float             CPlayer::m_jump_power = 15.0f;
const float             CPlayer::m_move_friction = 0.975f;
const float             CPlayer::m_max_life = 3.0f;
const int               CPlayer::m_max_invincible_time = 60;
const int               CPlayer::m_invincible_visible_interval = 4;
const float             CPlayer::m_fall_accelerator = 0.05f;

CPlayer::CPlayer(UNIT_ID unit_id)
    : IUnit(m_max_life, UNIT_CATEGORY::PLAYER, unit_id)
    , m_Accelerator(CVector3())
    , m_InvincibleTime(0)
    , m_Offset(CVector3())
    , m_IsGround(true)
    , m_FallSpeed(0)
    , m_StopFlag(false)
    , m_ActionFlag(true)
    , m_Controller()
    , m_WinsNum()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Initialize(const CVector3& position, MOVE_ID moveID)
{
    (void)position;

    IUnit::Initialize(position, moveID);

    m_Radius = m_radius;

    m_Model.Initialize("data\\Models\\Player.mv1", position);

    MV1SetMaterialDifColor(m_Model.GetModelHandle(), 0, m_Color);

    m_Accelerator = CVector3(0,0,0);

    m_Life = m_MaxLife = m_max_life;

    m_InvincibleTime = m_max_invincible_time;

    CCamera::GetInstance().Initialize();

    m_Offset = CCamera::GetInstance().GetPosition() - m_Transform.position;

    m_StopFlag = false;
}

void CPlayer::Update(void)
{
    IUnit::Update();
    m_Model.Update(m_Transform);
    CCamera::GetInstance().Follow(m_Transform.position,m_Offset);
    CCamera::GetInstance().Update();
}

void CPlayer::Draw(void)
{
    if ((m_InvincibleTime / m_invincible_visible_interval) % 2 == 1)
    {
        IUnit::Draw();
        m_Model.Draw();
    }
}

void CPlayer::Finalize(void)
{
    IUnit::Finalize();
    m_Model.Finalize();
    CCamera::GetInstance().Finalize();
}

void CPlayer::SetActionFlag(bool flag)
{
    m_ActionFlag = flag;
}

/*
 *  çUåÇ
 */
void
CPlayer::
Attack(void)
{
    if (m_ActionFlag)
    {
        Control();
    }
        Move();

        Damage();
}

void CPlayer::Control(void)
{
    //ç∂à⁄ìÆ
    if (GetJoypadInputState(m_Controller) & PAD_INPUT_LEFT)
        m_Accelerator.x += -m_move_speed;

    //âEà⁄ìÆ
    if (GetJoypadInputState(m_Controller) & PAD_INPUT_RIGHT)
        m_Accelerator.x += m_move_speed;


    //ÉWÉÉÉìÉv
    if (m_IsGround && GetJoypadInputState(m_Controller) & PAD_INPUT_1 && !m_StopFlag)
        if (m_IsGround == true)
        {
            m_IsGround = false;

            m_Accelerator.y = m_jump_power;

            CEffectManager::GetInstance().Create(EFFECT_ID::JUMP, m_Transform.position);

        }

    //í‚é~
    if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::LSHIFT))
         m_StopFlag = true;
    else m_StopFlag = false;

}

/*
 *  éÄñS
 */
void
CPlayer::
Defeat(void)
{
    IUnit::Defeat();

}

void CPlayer::Move(void)
{

    //èdóÕèàóù
    if (!m_IsGround && !m_StopFlag)
    {
        m_Accelerator.y -= m_FallSpeed;

        m_FallSpeed += m_fall_accelerator;
    }
    if (!m_StopFlag)
    m_Velocity += m_Accelerator;

    if(!m_StopFlag)
    m_Transform.position += m_Velocity;

    m_Velocity.x *= m_move_friction;
    m_Velocity.y *= m_move_friction;
    m_Velocity.z *= m_move_friction;


    if (m_Transform.position.y <= 0)
    {
        m_Transform.position.y = 0;
        m_Velocity.y = 0.0f;
        m_Accelerator.y = 0;
        m_FallSpeed = 0.0f;
        m_IsGround = true;
    }

    m_Accelerator = CVector3::ZERO;
}

void CPlayer::Damage(void)
{
    if (!m_InvincibleFlag)
        return;
    if (--m_InvincibleTime < 0)
    {
        m_InvincibleTime = m_max_invincible_time;

        m_InvincibleFlag = false;
    }

}

float CPlayer::GetLife(void)
{
    return m_Life;
}

