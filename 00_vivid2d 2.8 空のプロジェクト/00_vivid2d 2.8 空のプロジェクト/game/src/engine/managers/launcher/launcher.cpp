#include "launcher.h"
#include "../bullet_manager/bullet_manager.h"
#include "shot/basic/basic.h"
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
        std::shared_ptr<CShot> shot = *it;

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

        ++it;
    }

    m_ShotList.clear();
}

CLauncher& CLauncher::GetInstance(void)
{
    static CLauncher instance;

    return instance;
}

std::shared_ptr<CShot> CLauncher::Create(SHOT_ID shotID)
{
    std::shared_ptr<CShot> shot = nullptr;
    switch (shotID)
    {
    case SHOT_ID::BASIC:                 shot = std::make_shared<CBasic>();         break;
    case SHOT_ID::DODGE_BALL:            shot = std::make_shared<CDodgeBall>();     break;
    case SHOT_ID::MAX:                                                              break;
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
