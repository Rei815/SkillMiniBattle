#include "animation_manager.h"
#include "animation/key_scale/key_scale.h"
#include "animation/plane_up/plane_up.h"
#include "animation/plane_scale/plane_scale.h"
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
        IAnimation* animation = dynamic_cast<IAnimation*>((*it).get());

        animation->Update();

        if (!animation->IsActive())
        {
            animation->Finalize();

            it = m_AnimationList.erase(it);

            continue;
        }

        ++it;
    }

}


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

        ++it;
    }

    m_AnimationList.clear();
}

IAnimation* CAnimationManager::Create(ANIMATION_ID id, void* object_pointer)
{
    std::shared_ptr<IAnimation> animation = nullptr;

    switch (id)
    {
    case ANIMATION_ID::KEY_SCALE:
        animation = std::make_shared<CKeyScale>();
        break;
    case ANIMATION_ID::PLANE_UP:
        animation = std::make_shared<CPlaneUp>();
        break;
    case ANIMATION_ID::PLANE_SCALE:
        animation = std::make_shared<CPlaneScale>();
        break;
    }
    if (!animation) return nullptr;

    animation->Initialize();
    m_AnimationList.emplace_back(animation);
    return dynamic_cast<IAnimation*>(animation.get());

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
