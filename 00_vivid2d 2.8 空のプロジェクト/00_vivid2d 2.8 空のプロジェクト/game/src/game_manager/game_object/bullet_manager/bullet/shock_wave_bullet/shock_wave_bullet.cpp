#include "shock_wave_bullet.h"
#include "../../../launcher/launcher.h"

const std::string   CShockWaveBullet::m_file_name = "data\\Models\\stomp_coll.mv1";
const float         CShockWaveBullet::m_max_speed = 50.0f;
const float         CShockWaveBullet::m_spread_speed = 8.0f;
const float         CShockWaveBullet::m_height = 21.0f;
const int           CShockWaveBullet::m_life_time = 60;
const float         CShockWaveBullet::m_acceleration = 0.2f;
const float         CShockWaveBullet::m_scale = 0.5f;
const float         CShockWaveBullet::m_power = 0.5f;

/*
 *  コンストラクタ
 */
CShockWaveBullet::CShockWaveBullet()
    : IBullet(m_file_name, COLLIDER_ID::MODEL)
{

}

void CShockWaveBullet::Initialize(UNIT_CATEGORY category, const CVector3& position, const CVector3& direction)
{
    m_BulletID = BULLET_ID::SHOCK_WAVE;
    CVector3 _position = position;
    _position.y -= m_height / 2.0f;
    IBullet::Initialize(category, position, direction);
    m_Speed = m_spread_speed;
    m_Velocity = CVector3::ZERO;
    m_LifeTimer = m_life_time;
    m_Transform.scale = m_scale;
    m_Power = m_power;
}

void CShockWaveBullet::Update()
{
    m_Speed += m_acceleration;
    // 最高速度制限
    if (m_Speed > m_max_speed)
        m_Speed = m_max_speed;

    m_Transform.scale.x += vivid::GetDeltaTime() * m_Speed;
    m_Transform.scale.z += vivid::GetDeltaTime() * m_Speed;
    IBullet::Update();
}

void CShockWaveBullet::Draw()
{
}
