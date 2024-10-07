#include "gimmick_manager.h"
#include "gimmick/fall_gimmick/fall_gimmick.h"
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

        delete (*it);

        ++it;
    }

    m_GimmickList.clear();
}

void CGimmickManager::Create(GIMMICK_ID id)
{
    CGimmick* gimmick = nullptr;

    switch (id)
    {
    case GIMMICK_ID::FALL_GIMMICK:    gimmick = new CFallGimmick();     break;
        break;
    }
    if (!gimmick) return;

    gimmick->Initialize();
    m_GimmickList.push_back(gimmick);

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
