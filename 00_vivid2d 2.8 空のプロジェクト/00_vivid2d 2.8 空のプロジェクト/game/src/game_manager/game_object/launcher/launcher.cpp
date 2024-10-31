#include "launcher.h"
#include "../bullet_manager/bullet_manager.h"
#include "shot/basic/basic.h"
#include "shot/burst/burst.h"
#include "shot/shotgun/shotgun.h"
#include "shot/homing/homing.h"
#include "shot/homing_burst/homing_burst.h"
#include "shot/homing_shotgun/homing_shotgun.h"
#include "shot/homing_shotgun_delay/homing_shotgun_delay.h"
#include "shot/shock_wave/shock_wave.h"
#include "shot/three_way/three_way.h"
#include "shot/five_way/five_way.h"
#include "shot/dodge_ball/dodge_ball.h"

/*
 *  初期化
 */
void CLauncher::Initialize(void)
{
    m_ShotList.clear();
}

/*
 *  更新
 */
void CLauncher::Update(void)
{
    if (m_ShotList.empty()) return;

    SHOT_LIST::iterator it = m_ShotList.begin();

    while (it != m_ShotList.end())
    {
        CShot* shot = (CShot*)(*it);

        shot->Update();

        ++it;
    }
}

/*
 *  解放
 */
void CLauncher::Finalize(void)
{
    if (m_ShotList.empty()) return;

    SHOT_LIST::iterator it = m_ShotList.begin();

    while (it != m_ShotList.end())
    {
        (*it)->Finalize();

        delete (*it);

        ++it;
    }

    m_ShotList.clear();
}

CLauncher& CLauncher::GetInstance(void)
{
    static CLauncher instance;

    return instance;
}

CShot* CLauncher::Create(SHOT_ID shotID)
{
    CShot* shot = nullptr;
    switch (shotID)
    {
    case SHOT_ID::BASIC:                 shot = new CBasic();               break;
    case SHOT_ID::THREE_WAY:             shot = new CThreeWay();            break;
    case SHOT_ID::FIVE_WAY:              shot = new CFiveWay();             break;
    case SHOT_ID::BURST:                 shot = new CBurst();               break;
    case SHOT_ID::SHOTGUN:               shot = new CShotgun();             break;
    case SHOT_ID::HOMING:                shot = new CHoming();              break;
    case SHOT_ID::HOMING_BURST:          shot = new CHomingBurst();         break;
    case SHOT_ID::HOMING_SHOTGUN:        shot = new CHomingShotgun();       break;
    case SHOT_ID::HOMING_SHOTGUN_DELAY:  shot = new CHomingShotgunDelay();  break;
    case SHOT_ID::SHOCK_WAVE:            shot = new CShockWave();           break;
    case SHOT_ID::DODGE_BALL:            shot = new CDodgeBall();           break;
    case SHOT_ID::MAX:                                                      break;
    }

    if (!shot)
        return nullptr;
    shot->Initialize();
    m_ShotList.push_back(shot);

    return shot;
}

/*
 *  コンストラクタ
 */
CLauncher::
CLauncher(void)
{
}

/*
 *  コピーコンストラクタ
 */
CLauncher::
CLauncher(const CLauncher& rhs)
{
    (void)rhs;
}

/*
 *  デストラクタ
 */
CLauncher::
~CLauncher(void)
{
}

/*
 *  代入演算子
 */
CLauncher&
CLauncher::
operator=(const CLauncher& rhs)
{
    (void)rhs;

    return *this;
}
