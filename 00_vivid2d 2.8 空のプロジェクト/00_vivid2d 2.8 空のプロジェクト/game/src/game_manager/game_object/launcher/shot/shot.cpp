#include "shot.h"
#include "../../bullet_manager/bullet_manager.h"
const CShot::BulletParameters CShot::m_bullet_parameters =
//          ’e‚ÌID  ”­ŽË‘¬“x UŒ‚‘¬“x ‘•“U”        ‘¬“x     ƒuƒŒ       ”¼Œa     UŒ‚—Í —U“±Žž’x‰„ŽžŠÔ  ‰Á‘¬—Í
{BULLET_ID::NORMAL,       0,      30,     1,      30.0f,      0,      45.0f,      1.0f,             0,      0};

CShot::CShot()
    : m_BulletInterval()
    , m_ShotFlag()
    , m_ShotCount()
    , m_UnitCategory()
    , m_Position()
    , m_Direction(CVector3())
{
}

CShot::CShot(BulletParameters bulletParameters)
    : m_BulletParameters(new BulletParameters(bulletParameters))
    , m_BulletInterval()
    , m_ShotFlag()
    , m_ShotCount()
    , m_UnitCategory()
    , m_Position()
    , m_Direction(CVector3())
{
}

CShot::~CShot()
{
}

void CShot::Initialize()
{
    m_BulletInterval = m_BulletParameters->bulletInterval;
    m_FireInterval = m_BulletParameters->fireInterval;
    m_ShotFlag = false;
    m_ShotCount = 0;
}

void CShot::Update(void)
{
    if (!m_ShotFlag)
        return;

    CBulletManager& bm = CBulletManager::GetInstance();

    if (--m_BulletInterval < 0 && m_ShotCount < m_BulletParameters->capacity)
    {
        m_BulletInterval = m_BulletParameters->bulletInterval;

        for (int i = 0; i < m_BulletParameters->bullets; i++)
        {
            CVector3 dir = m_Direction;

            dir = CVector3::DeviationToDirection(m_Direction, m_BulletParameters->deviation);

            //’x‚ê‚Äƒz[ƒ~ƒ“ƒO‚Ìê‡³‹K‰»
            if(m_BulletParameters->homingDelayTime != 0)
                dir = dir.Normalize();

            bm.Create(m_UnitCategory, m_BulletParameters, m_Position, dir);

        }


        ++m_ShotCount;
    }

    Interval();
}

void CShot::Finalize(void)
{
}

void CShot::Shot(UNIT_CATEGORY unitCategory, CVector3& position, const CVector3& direction)
{
    if (m_ShotFlag)
        return;

    m_UnitCategory = unitCategory;
    m_Position = position;

    m_Direction = direction;


    m_ShotFlag = true;
}

void CShot::AddShot()
{
    m_BulletParameters->bulletInterval = 15;
    m_BulletParameters->capacity++;
}

void CShot::AddBullet()
{
    m_BulletParameters->deviation = 0.15f;

    m_BulletParameters->bullets++;
}

int CShot::GetBullets()
{
    return m_BulletParameters->bullets;
}

int CShot::GetCapacity()
{
    return m_BulletParameters->capacity;
}


bool CShot::GetShotFlag()
{
    return m_ShotFlag;
}

void CShot::Interval()
{
    if (m_ShotCount >= m_BulletParameters->capacity && m_ShotFlag)
    {
        if (--m_FireInterval <= 0)
        {
            m_FireInterval = m_BulletParameters->fireInterval;
            m_ShotCount = 0;
            m_ShotFlag = false;

            m_ShotCount = 0;
        }
    }
}
