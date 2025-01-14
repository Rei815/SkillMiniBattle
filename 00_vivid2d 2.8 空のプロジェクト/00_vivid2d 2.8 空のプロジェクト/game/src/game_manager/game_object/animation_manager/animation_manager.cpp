//#include "animation_manager.h"
///*
// *  �C���X�^���X�̎擾
// */
//CAnimationManager&
//CAnimationManager::
//GetInstance(void)
//{
//    static CAnimationManager instance;
//
//    return instance;
//}
//
///*
// *  ������
// */
//void
//CAnimationManager::
//Initialize(void)
//{
//    m_GimmickList.clear();
//}
//
///*
// *  �X�V
// */
//void
//CAnimationManager::Update(void)
//{
//    if (m_GimmickList.empty()) return;
//
//    GIMMICK_LIST::iterator it = m_GimmickList.begin();
//
//    while (it != m_GimmickList.end())
//    {
//        CGimmick* gimmick = (CGimmick*)(*it);
//
//        gimmick->Update();
//
//        if (!gimmick->GetActive())
//        {
//            gimmick->Finalize();
//
//            delete gimmick;
//
//            it = m_GimmickList.erase(it);
//
//            continue;
//        }
//
//        ++it;
//    }
//
//}
//
///*
// *  �`��
// */
//void CAnimationManager::Draw(void)
//{
//    if (m_GimmickList.empty()) return;
//
//    GIMMICK_LIST::iterator it = m_GimmickList.begin();
//
//    while (it != m_GimmickList.end())
//    {
//        (*it)->Draw();
//
//        ++it;
//    }
//}
//
///*
// *  ���
// */
//void CAnimationManager::Finalize(void)
//{
//    if (m_GimmickList.empty()) return;
//
//    GIMMICK_LIST::iterator it = m_GimmickList.begin();
//
//    while (it != m_GimmickList.end())
//    {
//        (*it)->Finalize();
//
//        delete (*it);
//
//        ++it;
//    }
//
//    m_GimmickList.clear();
//}
//
//void CAnimationManager::Create(GIMMICK_ID id, IObject* object)
//{
//    CGimmick* gimmick = nullptr;
//    switch (id)
//    {
//    case GIMMICK_ID::FALL_GIMMICK: gimmick = new CFallGimmick(); break;
//    case GIMMICK_ID::DODGEBALL_GIMMICK: gimmick = new CDodgeBallGimmick(); break;
//    case GIMMICK_ID::DARUMA_FALLDOWN_GIMMICK: gimmick = new CDaruma_FallDownGimmick(); break;
//    }
//
//    if (!gimmick) return;
//
//    gimmick->Initialize(object);
//    m_GimmickList.push_back(gimmick);
//
//}
//
//void CAnimationManager::Create(GIMMICK_ID id, IObject* object, float time)
//{
//    CGimmick* gimmick = nullptr;
//    switch (id)
//    {
//    case GIMMICK_ID::FALL_GIMMICK: gimmick = new CFallGimmick(); break;
//    case GIMMICK_ID::DODGEBALL_GIMMICK: gimmick = new CDodgeBallGimmick(); break;
//    case GIMMICK_ID::DARUMA_FALLDOWN_GIMMICK: gimmick = new CDaruma_FallDownGimmick(); break;
//    }
//
//    if (!gimmick) return;
//
//    gimmick->Initialize(object, time);
//    m_GimmickList.push_back(gimmick);
//
//}
//
//CAnimationManager::GIMMICK_LIST CAnimationManager::GetList()
//{
//    return m_GimmickList;
//}
//
///*
// *  �R���X�g���N�^
// */
//CAnimationManager::
//CAnimationManager(void)
//{
//}
//
///*
// *  �R�s�[�R���X�g���N�^
// */
//CAnimationManager::
//CAnimationManager(const CAnimationManager& rhs)
//{
//    (void)rhs;
//}
//
///*
// *  �f�X�g���N�^
// */
//CAnimationManager::
//~CAnimationManager(void)
//{
//}
//
///*
// *  ������Z�q
// */
//CAnimationManager&
//CAnimationManager::
//operator=(const CAnimationManager& rhs)
//{
//    (void)rhs;
//
//    return *this;
//}
