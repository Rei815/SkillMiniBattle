#include "cannon_bullet.h"
#include "../../../launcher/launcher.h"
#include "../../../effect_manager/effect_manager.h"

const std::string   CCannonBullet::m_file_name = "data\\Models\\Bullet.mv1";
const float         CCannonBullet::m_max_speed = 50.0f;
const float	        CCannonBullet::m_effect2_speed = 125.0f;

/*
 *  コンストラクタ
 */
CCannonBullet::CCannonBullet()
    : IBullet(m_file_name, COLLIDER_ID::SPHERE)
    , m_Effect(nullptr)
    , m_Effect2(nullptr)
{

}

void CCannonBullet::Initialize(UNIT_CATEGORY category, CShot::BulletParameters* bulletParameter, const CVector3& position, const CVector3& direction)
{
    IBullet::Initialize(category, bulletParameter, position, direction);
    m_Speed = bulletParameter->speed;
    m_Direction = direction;
    m_Accleration = bulletParameter->acceleration;
    
    MV1SetMaterialDifColor(m_Model.GetModelHandle(), 0, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));

    m_Effect = CEffectManager::GetInstance().Create(EFFECT_ID::ENEMY_BULLET, position);


    //directionの向きの回転を作りたい（未完成）
    //角度はラジアン値で、回転の順番はZ軸→X軸→Y軸
    const float math_pi = 3.1415926535897931;
    CVector3 rotation = CVector3(0,0,0);
    CVector3 TempDir = direction;
    float TempCos = 0;
    //Y軸
    TempCos = (TempDir.z / sqrt(TempDir.x * TempDir.x + TempDir.z * TempDir.z));
    if (-1.0f <= TempCos && TempCos <= 1.0f)
    {
        if (TempDir.x >= 0.0f)
        {
            rotation.y = acos(TempCos);
        }
        else
        {
            rotation.y = -acos(TempCos);
        }
    }
    TempDir.z = sqrt(TempDir.x * TempDir.x + TempDir.z * TempDir.z);
    TempDir.x = 0.0f;
    
    //X軸
    TempCos = (TempDir.z / sqrt(TempDir.y * TempDir.y + TempDir.z * TempDir.z));
    if (-1.0f <= TempCos && TempCos <= 1.0f)
    {
        if (TempDir.y >= 0.0f)
        {
            rotation.x = acos(TempCos);
        }
        else
        {
            rotation.x = -acos(TempCos);
        }
    }

    m_Effect2 = CEffectManager::GetInstance().Create(EFFECT_ID::FORECAST_LINE, position, rotation);
}

void CCannonBullet::Update()
{
    m_Speed += m_Accleration;    // 徐々に加速させる

    // 最高速度制限
    if (m_Speed > m_max_speed)
        m_Speed = m_max_speed;
    m_Velocity = m_Direction * m_Speed;
    
    if (m_Effect != nullptr)
        m_Effect->SetPosition(m_Transform.position);

    if (m_Effect2 != nullptr)
        m_Effect2->SetPosition(m_Effect2->GetPosition() + m_Direction * m_effect2_speed);

    IBullet::Update();

}

void CCannonBullet::Finalize(void)
{
    if (m_Effect != nullptr)
        m_Effect->SetActive(false);
    if (m_Effect2 != nullptr)
        m_Effect2->SetActive(false);
    IBullet::Finalize();
}
