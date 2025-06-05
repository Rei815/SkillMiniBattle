#include "gimmick_manager.h"
#include "gimmick/fall_gimmick/fall_gimmick.h"
#include "gimmick/dodgeball_gimmick/dodgeball_gimmick.h"
#include "gimmick/daruma_falldown_gimmick/daruma_falldown_gimmick.h"
#include "gimmick/belt_conveyor_gimmick/belt_conveyor_gimmick.h"

/*
 *  �C���X�^���X�̎擾
 */
CGimmickManager&
CGimmickManager::
GetInstance(void)
{
    static CGimmickManager instance;

    return instance;
}

/*
 *  ������
 */
void
CGimmickManager::
Initialize(void)
{
    m_GimmickList.clear();
}

/*
 *  �X�V
 */
void
CGimmickManager::Update(void)
{
    if (m_GimmickList.empty()) return;

    GIMMICK_LIST::iterator it = m_GimmickList.begin();

    while (it != m_GimmickList.end())
    {
        std::shared_ptr<CGimmick> gimmick = (std::shared_ptr<CGimmick>)(*it);

        gimmick->Update();

        if (!gimmick->IsActive())
        {
            gimmick->Finalize();

            it = m_GimmickList.erase(it);

            continue;
        }

        ++it;
    }

}

/*
 *  �`��
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
 *  ���
 */
void CGimmickManager::Finalize(void)
{
    if (m_GimmickList.empty()) return;

    GIMMICK_LIST::iterator it = m_GimmickList.begin();

    while (it != m_GimmickList.end())
    {
        (*it)->Finalize();

        ++it;
    }

    m_GimmickList.clear();
}

void CGimmickManager::Create(GIMMICK_ID id, std::shared_ptr<IObject> object)
{
    std::shared_ptr<CGimmick> gimmick = nullptr;
    switch (id)
    {
    case GIMMICK_ID::FALL_GIMMICK:              gimmick = std::make_shared<CFallGimmick>();               break;
    case GIMMICK_ID::DARUMA_FALLDOWN_GIMMICK:   gimmick = std::make_shared<CDaruma_FallDownGimmick>();    break;
    case GIMMICK_ID::DODGEBALL_GIMMICK:         gimmick = std::make_shared<CDodgeBallGimmick>();          break;
    case GIMMICK_ID::BELT_CONVEYOR_GIMMICK:     gimmick = std::make_shared<CBeltConveyorGimmick>();       break;
    }

    if (!gimmick) return;

    gimmick->Initialize(object);
    m_GimmickList.emplace_back(gimmick);

}

void CGimmickManager::Create(GIMMICK_ID id, std::shared_ptr<IObject> object, float time)
{
    std::shared_ptr<CGimmick> gimmick = nullptr;
    switch (id)
    {
    case GIMMICK_ID::FALL_GIMMICK:              gimmick = std::make_shared<CFallGimmick>();               break;
    case GIMMICK_ID::DARUMA_FALLDOWN_GIMMICK:   gimmick = std::make_shared<CDaruma_FallDownGimmick>();    break;
    case GIMMICK_ID::DODGEBALL_GIMMICK:         gimmick = std::make_shared<CDodgeBallGimmick>();          break;
    case GIMMICK_ID::BELT_CONVEYOR_GIMMICK:     gimmick = std::make_shared<CBeltConveyorGimmick>();       break;
    }

    if (!gimmick) return;

    gimmick->Initialize(object, time);
    m_GimmickList.emplace_back(gimmick);

}

CGimmickManager::GIMMICK_LIST CGimmickManager::GetList()
{
    return m_GimmickList;
}

/*
 *  �R���X�g���N�^
 */
CGimmickManager::
CGimmickManager(void)
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
CGimmickManager::
CGimmickManager(const CGimmickManager& rhs)
{
    (void)rhs;
}

/*
 *  �f�X�g���N�^
 */
CGimmickManager::
~CGimmickManager(void)
{
}

/*
 *  ������Z�q
 */
CGimmickManager&
CGimmickManager::
operator=(const CGimmickManager& rhs)
{
    (void)rhs;

    return *this;
}
