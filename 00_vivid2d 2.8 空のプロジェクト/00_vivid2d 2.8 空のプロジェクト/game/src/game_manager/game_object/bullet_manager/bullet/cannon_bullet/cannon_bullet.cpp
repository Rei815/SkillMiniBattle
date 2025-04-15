#include "cannon_bullet.h"
#include "../../../launcher/launcher.h"
#include "../../../effect_manager/effect_manager.h"

const std::string   CCannonBullet::m_file_name = "data\\Models\\Bullet.mv1";
const float         CCannonBullet::m_max_speed = 50.0f;

/*
 *  コンストラクタ
 */
CCannonBullet::CCannonBullet()
    : IBullet(m_file_name, COLLIDER_ID::SPHERE)
//    , m_Effect(nullptr)
{

}

void CCannonBullet::Initialize(UNIT_CATEGORY category, CShot::BulletParameters* bulletParameter, const CVector3& position, const CVector3& direction)
{
    IBullet::Initialize(category, bulletParameter, position, direction);
    m_Speed = bulletParameter->speed;
    m_Direction = direction;
    m_Accleration = bulletParameter->acceleration;
    
    MV1SetMaterialDifColor(m_Model.GetModelHandle(), 0, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
}

void CCannonBullet::Update()
{

    IBullet::Update();

}

void CCannonBullet::Finalize(void)
{
    IBullet::Finalize();
}
