#include "cannon_bullet.h"
#include "../../../launcher/launcher.h"

const std::string   CCannonBullet::m_file_name = "data\\Models\\Bullet.mv1";
const float         CCannonBullet::m_max_speed = 50.0f;

/*
 *  コンストラクタ
 */
CCannonBullet::CCannonBullet()
    : IBullet(COLLIDER_ID::SPHERE)
{

}

void CCannonBullet::Initialize(UNIT_CATEGORY category, CShot::BulletParameters* bulletParameter, const CVector3& position, const CVector3& direction)
{
    IBullet::Initialize(category, bulletParameter, position, direction);
    m_Speed = bulletParameter->speed;
    m_Direction = direction;
    m_Accleration = bulletParameter->acceleration;
}

void CCannonBullet::Update()
{
    IBullet::Update();
}
