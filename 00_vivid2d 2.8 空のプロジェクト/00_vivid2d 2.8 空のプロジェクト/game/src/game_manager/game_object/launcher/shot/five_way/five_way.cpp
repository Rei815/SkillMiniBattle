#include "five_way.h"
#include "../../../bullet_manager/bullet_manager.h"

const CFiveWay::BulletParameters CFiveWay::m_bullet_parameters =
//          ’e‚ÌID  ”­Ë‘¬“x UŒ‚‘¬“x ‘•“U” ”­Ë”       ‘¬“x     ƒuƒŒ       ”¼Œa     UŒ‚—Í —U“±’x‰„ŠÔ  ‰Á‘¬—Í
{ BULLET_ID::NORMAL,      0,      60,     1,     1,      30.0f,  0.0f,      30.0f,      1.0,             0,     0 };

CFiveWay::CFiveWay()
    : CShot(m_bullet_parameters)

{
}

CFiveWay::~CFiveWay()
{
}

void CFiveWay::Update(void)
{
    if (!m_ShotFlag)
        return;

    CBulletManager& bm = CBulletManager::GetInstance();

    if (--m_BulletInterval < 0 && m_ShotCount < m_BulletParameters->capacity)
    {
        m_BulletInterval = m_BulletParameters->bulletInterval;

        bm.Create(m_UnitCategory, m_BulletParameters, *m_Position, m_Direction);
        bm.Create(m_UnitCategory, m_BulletParameters, *m_Position, m_Direction + CVector3::RIGHT);
        bm.Create(m_UnitCategory, m_BulletParameters, *m_Position, m_Direction + CVector3::LEFT);
        bm.Create(m_UnitCategory, m_BulletParameters, *m_Position, m_Direction + CVector3(0.5,0,0));
        bm.Create(m_UnitCategory, m_BulletParameters, *m_Position, m_Direction + CVector3(-0.5, 0, 0));

        ++m_ShotCount;
    }
    Interval();

}
