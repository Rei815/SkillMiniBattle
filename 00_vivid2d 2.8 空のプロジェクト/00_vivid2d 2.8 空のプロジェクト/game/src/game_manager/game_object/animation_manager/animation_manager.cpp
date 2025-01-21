#include "animation_manager.h"
#include "animation/key_scale/key_scale.h"
#include "animation/plane_up_down/plane_up_down.h"
/*
 *  �C���X�^���X�̎擾
 */
CAnimationManager&
CAnimationManager::
GetInstance(void)
{
    static CAnimationManager instance;

    return instance;
}

/*
 *  ������
 */
void
CAnimationManager::
Initialize(void)
{
    m_AnimationList.clear();
}

/*
 *  �X�V
 */
void
CAnimationManager::Update(void)
{
    if (m_AnimationList.empty()) return;

    ANIMATION_LIST::iterator it = m_AnimationList.begin();

    while (it != m_AnimationList.end())
    {
        IAnimation* animation = (IAnimation*)(*it);

        animation->Update();

        if (!animation->GetActive())
        {
            animation->Finalize();

            delete animation;

            it = m_AnimationList.erase(it);

            continue;
        }

        ++it;
    }

}

///*
// *  �`��
// */
//void CAnimationManager::Draw(void)
//{
//    if (m_AnimationList.empty()) return;
//
//    ANIMATION_LIST::iterator it = m_AnimationList.begin();
//
//    while (it != m_AnimationList.end())
//    {
//        (*it)->Draw();
//
//        ++it;
//    }
//}

/*
 *  ���
 */
void CAnimationManager::Finalize(void)
{
    if (m_AnimationList.empty()) return;

    ANIMATION_LIST::iterator it = m_AnimationList.begin();

    while (it != m_AnimationList.end())
    {
        (*it)->Finalize();

        delete (*it);

        ++it;
    }

    m_AnimationList.clear();
}

void CAnimationManager::Create(ANIMATION_ID id, void* object_pointer)
{
    IAnimation* animation = nullptr;

    switch (id)
    {
    case ANIMATION_ID::KEY_SCALE:
        animation = new CKeyScale();
        break;
    case ANIMATION_ID::PLANE_UP_DOWN:
        animation = new CPlaneUpDown();
        break;
    }
    if (!animation) return;

    animation->Initialize(object_pointer);
    m_AnimationList.push_back(animation);

}


CAnimationManager::ANIMATION_LIST CAnimationManager::GetList()
{
    return m_AnimationList;
}

/*
 *  �R���X�g���N�^
 */
CAnimationManager::
CAnimationManager(void)
{
}

/*
 *  �R�s�[�R���X�g���N�^
 */
CAnimationManager::
CAnimationManager(const CAnimationManager& rhs)
{
    (void)rhs;
}

/*
 *  �f�X�g���N�^
 */
CAnimationManager::
~CAnimationManager(void)
{
}

/*
 *  ������Z�q
 */
CAnimationManager&
CAnimationManager::
operator=(const CAnimationManager& rhs)
{
    (void)rhs;

    return *this;
}
