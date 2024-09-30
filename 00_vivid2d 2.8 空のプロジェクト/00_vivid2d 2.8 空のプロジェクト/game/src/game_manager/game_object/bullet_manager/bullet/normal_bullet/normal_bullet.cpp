#include "normal_bullet.h"
#include "../../../launcher/launcher.h"
#include "../../../effect_manager/effect_manager.h"

const std::string   CNormalBullet::m_file_name = "data\\Models\\Bullet.mv1";
const float         CNormalBullet::m_max_speed = 50.0f;

/*
 *  �R���X�g���N�^
 */
CNormalBullet::CNormalBullet()
    : IBullet(m_file_name, COLLIDER_ID::SPHERE)
    , m_Effect(nullptr)
{

}

void CNormalBullet::Initialize(UNIT_CATEGORY category, CShot::BulletParameters* bulletParameter, const CVector3& position, const CVector3& direction)
{
    IBullet::Initialize(category, bulletParameter, position, direction);
    m_Speed = bulletParameter->speed;
    m_Direction = direction;
    m_Accleration = bulletParameter->acceleration;
    if (category == UNIT_CATEGORY::PLAYER)
        m_Effect = CEffectManager::GetInstance().Create(EFFECT_ID::PLAYER_BULLET, position);
    else
    {
        MV1SetMaterialDifColor(m_Model.GetModelHandle(), 0, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));

        m_Effect = CEffectManager::GetInstance().Create(EFFECT_ID::ENEMY_BULLET, position);

    }
}

void CNormalBullet::Update()
{
    m_Speed += m_Accleration;    // ���X�ɉ���������

    // �ō����x����
    if (m_Speed > m_max_speed)
        m_Speed = m_max_speed;
    m_Velocity = m_Direction * m_Speed;
    if (m_Effect != nullptr)
        m_Effect->SetPosition(m_Transform.position);
    IBullet::Update();

}

void CNormalBullet::Finalize(void)
{
    if (m_Effect != nullptr)
        m_Effect->SetActive(false);
    IBullet::Finalize();
}
