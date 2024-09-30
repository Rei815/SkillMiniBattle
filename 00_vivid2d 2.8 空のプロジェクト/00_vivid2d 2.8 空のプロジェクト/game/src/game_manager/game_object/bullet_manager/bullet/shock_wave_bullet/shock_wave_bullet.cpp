#include "shock_wave_bullet.h"
#include "../../../launcher/launcher.h"

const std::string   CShockWaveBullet::m_file_name = "data\\Models\\Bullet.mv1";
const float         CShockWaveBullet::m_max_speed = 50.0f;
const float         CShockWaveBullet::m_spread_speed = 7.5f;

/*
 *  コンストラクタ
 */
CShockWaveBullet::CShockWaveBullet()
    : IBullet(m_file_name, COLLIDER_ID::CAPSULE)
{

}

void CShockWaveBullet::Initialize(UNIT_CATEGORY category, CShot::BulletParameters* bulletParameter, const CVector3& position, const CVector3& direction)
{
    IBullet::Initialize(category, bulletParameter, position, direction);
    m_Speed = bulletParameter->speed;
    m_Direction = direction;
    m_Accleration = bulletParameter->acceleration;
}

void CShockWaveBullet::Update()
{
    m_Speed += m_Accleration;    // 徐々に加速させる

    if (m_Direction == CVector3::BACK)
    {
        m_CapsulePosA.x += m_spread_speed;
        m_CapsulePosB.x -= m_spread_speed;
        m_Velocity = m_Direction * m_Speed;
    }
    else if(m_Direction == CVector3::BACK + CVector3::RIGHT)
    {
        m_CapsulePosA.x += m_spread_speed;
        m_CapsulePosB.z -= m_spread_speed;
        m_Velocity = m_Direction * (m_Speed / 2.0f);

    }
    else if(m_Direction == CVector3::BACK + CVector3::LEFT)
    {
        m_CapsulePosA.x -= m_spread_speed;
        m_CapsulePosB.z -= m_spread_speed;
        m_Velocity = m_Direction * (m_Speed / 2.0f);
    }
    // 最高速度制限
    if (m_Speed > m_max_speed)
        m_Speed = m_max_speed;
    IBullet::Update();

}

void CShockWaveBullet::Draw()
{
    //int ok = DxLib::DrawCapsule3D(m_Transform.position + m_CapsulePosA,m_Transform.position + m_CapsulePosB, m_Radius, 8, GetColor(255, 255, 0), GetColor(255, 255, 255), FALSE);
}
