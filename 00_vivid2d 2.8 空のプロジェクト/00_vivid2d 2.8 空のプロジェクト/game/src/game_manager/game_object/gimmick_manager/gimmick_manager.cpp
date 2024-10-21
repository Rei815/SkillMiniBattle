#include "gimmick_manager.h"
#include "gimmick/fall_gimmick/fall_gimmick.h"
#include "gimmick/dodgeball_gimmick/dodgeball_gimmick.h"
/*
 *  インスタンスの取得
 */
CGimmickManager&
CGimmickManager::
GetInstance(void)
{
    static CGimmickManager instance;

    return instance;
}

/*
 *  初期化
 */
void
CGimmickManager::
Initialize(void)
{
    m_GimmickList.clear();
}

/*
 *  更新
 */
void
CGimmickManager::Update(void)
{
    if (m_GimmickList.empty()) return;

    GIMMICK_LIST::iterator it = m_GimmickList.begin();

    while (it != m_GimmickList.end())
    {
        CGimmick* gimmick = (CGimmick*)(*it);

        gimmick->Update();

        if (!gimmick->GetActive())
        {
            gimmick->Finalize();

            delete gimmick;

            it = m_GimmickList.erase(it);

            continue;
        }

        ++it;
    }

}

/*
 *  描画
 */
void CGimmickManager::Draw(void)
{
    if (m_GimmickList.empty()) return;

    GIMMICK_LIST::iterator it = m_GimmickList.begin();

    while (it != m_GimmickList.end())
    {
        (*it)->Draw();

        ++it;
    }
}

/*
 *  解放
 */
void CGimmickManager::Finalize(void)
{
    if (m_GimmickList.empty()) return;

    GIMMICK_LIST::iterator it = m_GimmickList.begin();

    while (it != m_GimmickList.end())
    {
        (*it)->Finalize();

        delete (*it);

        ++it;
    }

    m_GimmickList.clear();
}

void CGimmickManager::Create(GIMMICK_ID id, IObject* object)
{
    CGimmick* gimmick = nullptr;
    switch (id)
    {
    case GIMMICK_ID::FALL_GIMMICK: gimmick = new CFallGimmick(); break;
    case GIMMICK_ID::DODGEBALL_GIMMICK: gimmick = new CDodgeBallGimmick(); break;
    }

    if (!gimmick) return;

    gimmick->Initialize(object);
    m_GimmickList.push_back(gimmick);

}

void CGimmickManager::Create(GIMMICK_ID id, IObject* object, float time)
{
    CGimmick* gimmick = nullptr;
    switch (id)
    {
    case GIMMICK_ID::FALL_GIMMICK: gimmick = new CFallGimmick(); break;
    case GIMMICK_ID::DODGEBALL_GIMMICK: gimmick = new CDodgeBallGimmick(); break;
    }

    if (!gimmick) return;

    gimmick->Initialize(object, time);
    m_GimmickList.push_back(gimmick);

}

CGimmickManager::GIMMICK_LIST CGimmickManager::GetList()
{
    return m_GimmickList;
}

/*
 *  コンストラクタ
 */
CGimmickManager::
CGimmickManager(void)
{
}

/*
 *  コピーコンストラクタ
 */
CGimmickManager::
CGimmickManager(const CGimmickManager& rhs)
{
    (void)rhs;
}

/*
 *  デストラクタ
 */
CGimmickManager::
~CGimmickManager(void)
{
}

/*
 *  代入演算子
 */
CGimmickManager&
CGimmickManager::
operator=(const CGimmickManager& rhs)
{
    (void)rhs;

    return *this;
}
