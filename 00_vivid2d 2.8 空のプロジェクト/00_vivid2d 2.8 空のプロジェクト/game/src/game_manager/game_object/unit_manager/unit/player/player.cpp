#include "player.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../../launcher/launcher.h"
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
const int               CPlayer::m_dust_cloud_interval = 10;
const float             CPlayer::m_dust_cloud_scale_adjust = 15.0f;

CPlayer::CPlayer()
    : IUnit(m_max_life, UNIT_CATEGORY::PLAYER, UNIT_ID::PLAYER)
    , m_Accelerator(CVector3())
    , m_InvincibleTime(0)
    , m_Offset(CVector3())
    , m_IsGround(true)
    , m_FallSpeed(0)
    , m_DustCloudTime(0)
    , m_StopFlag(false)
    , m_ActionFlag(true)
    , m_FireFlag(true)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Initialize(const CVector3& position, MOVE_ID moveID, bool aimFlag)
{
    (void)position;

    IUnit::Initialize(position, moveID, aimFlag);

    m_Radius = m_radius;
    m_Model.Initialize("data\\Models\\Player.mv1", position);
    m_Accelerator = CVector3(0,0,0);
    m_Life = m_MaxLife = m_max_life;
    m_InvincibleTime = m_max_invincible_time;
    CCamera::GetInstance().Initialize();

    m_Offset = CCamera::GetInstance().GetPosition() - m_Transform.position;
    m_DustCloudTime = 0;
    m_StopFlag = false;
    CLauncher& lan = CLauncher::GetInstance();
    m_Shot = lan.Create(SHOT_ID::BASIC);
    
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

    std::string max_life = "ç≈ëÂëÃóÕ :" + std::to_string((int)m_MaxLife);
    vivid::Vector2 life_position = vivid::Vector2(vivid::WINDOW_WIDTH - vivid::GetTextWidth(20, max_life) - 2.0f, 0);
    vivid::DrawText(20, max_life, life_position);

    std::string damage_rate = "çUåÇó¶ :" + std::to_string(m_DamageRate);
    vivid::Vector2 damage_rate_position = vivid::Vector2(vivid::WINDOW_WIDTH - vivid::GetTextWidth(20, damage_rate) - 2.0f, 20);
    vivid::DrawText(20, damage_rate, damage_rate_position);

    std::string bullets_num = "î≠éÀêî :" + std::to_string(m_Shot->GetBullets());
    vivid::Vector2 bullets_position = vivid::Vector2(vivid::WINDOW_WIDTH - vivid::GetTextWidth(20, bullets_num) - 2.0f, 40);
    vivid::DrawText(20, bullets_num, bullets_position);

    std::string capacity = "ëïìUêî :" + std::to_string(m_Shot->GetCapacity());
    vivid::Vector2 capacity_position = vivid::Vector2(vivid::WINDOW_WIDTH - vivid::GetTextWidth(20, capacity) - 2.0f, 60);
    vivid::DrawText(20, capacity, capacity_position);

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

void CPlayer::SetFireFlag(bool flag)
{
    m_FireFlag = flag;
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
        Fire();

        Control();

    }
        Move();

        Damage();


}

void CPlayer::Control(void)
{
    //ç∂à⁄ìÆ
    if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::A))
        m_Accelerator.x += -m_move_speed;

    //âEà⁄ìÆ
    if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::D))
        m_Accelerator.x += m_move_speed;


    //ÉWÉÉÉìÉv
    if (m_IsGround && vivid::keyboard::Button(vivid::keyboard::KEY_ID::SPACE) && !m_StopFlag)
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

    //ìyâåÉGÉtÉFÉNÉgÇÃê∂ê¨
    if (--m_DustCloudTime <= 0 && m_Accelerator.x != 0 && m_IsGround)
    {
        m_DustCloudTime = m_dust_cloud_interval;

        //ë´å≥Ç©ÇÁèoÇ∑
        CVector3 pos = m_Transform.position;
        pos.y -= m_radius;

        //ìyâåëÂÇ´Ç≥í≤êÆ
        float scale = abs(m_Velocity.x) / m_dust_cloud_scale_adjust * 25.0f;

        CEffectManager::GetInstance().Create(EFFECT_ID::DUST_CLOUD, pos, scale);
    }
}

/*
 *  éÄñS
 */
void
CPlayer::
Dead(void)
{
    m_ActiveFlag = false;
}

void CPlayer::Fire(void)
{
    if (vivid::mouse::Button(vivid::mouse::BUTTON_ID::LEFT) && m_FireFlag)
    {
        vivid::Point mousePoint = vivid::mouse::GetCursorPos();
        CVector3 mousePos;
        mousePos.x = mousePoint.x;
        mousePos.y = mousePoint.y;
        mousePos.z = 1.0f;
        CVector3 endPos = ConvScreenPosToWorldPos(mousePos);
        CVector3 startPos = CCamera::GetInstance().GetPosition();
        CVector3 dir = CUnitManager::GetInstance().CheckHitLine(startPos, endPos) - m_Transform.position;
        m_Shot->Shot(m_Category, m_Transform.position, dir.Normalize());

    }
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

