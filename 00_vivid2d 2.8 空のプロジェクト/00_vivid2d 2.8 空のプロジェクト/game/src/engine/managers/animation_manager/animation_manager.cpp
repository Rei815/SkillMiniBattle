#include "animation_manager.h"
#include "animation/key_scale/key_scale.h"
#include "animation/plane_up/plane_up.h"
#include "animation/plane_scale/plane_scale.h"
/*
 *  インスタンスの取得
 */
CAnimationManager&
CAnimationManager::
GetInstance(void)
{
    static CAnimationManager instance;

    return instance;
}

/*
 *  初期化
 */
void
CAnimationManager::
Initialize(void)
{
    m_AnimationList.clear();
}

/*
 *  更新
 */
void
CAnimationManager::Update(void)
{
    if (m_AnimationList.empty()) return;

    ANIMATION_LIST::iterator it = m_AnimationList.begin();

    while (it != m_AnimationList.end())
    {
        std::shared_ptr<IAnimation> animation = *it;

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
 *  解放
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

std::shared_ptr<IAnimation> CAnimationManager::Create(ANIMATION_ID id, std::shared_ptr<void> pointer)
{
    std::shared_ptr<IAnimation> animation = nullptr;

    switch (id)
    {
    case ANIMATION_ID::KEY_SCALE:   animation = std::make_shared<CKeyScale>();      break;
    case ANIMATION_ID::PLANE_UP:    animation = std::make_shared<CPlaneUp>();       break;
    case ANIMATION_ID::PLANE_SCALE: animation = std::make_shared<CPlaneScale>();    break;
    }
    if (!animation) return nullptr;

    animation->Initialize(pointer);
    m_AnimationList.emplace_back(animation);
    return animation;
}

CAnimationManager::ANIMATION_LIST CAnimationManager::GetList()
{
    return m_AnimationList;
}

/*
 *  コンストラクタ
 */
CAnimationManager::
CAnimationManager(void)
{
}

/*
 *  コピーコンストラクタ
 */
CAnimationManager::
CAnimationManager(const CAnimationManager& rhs)
{
    (void)rhs;
}

/*
 *  デストラクタ
 */
CAnimationManager::
~CAnimationManager(void)
{
}

/*
 *  代入演算子
 */
CAnimationManager&
CAnimationManager::
operator=(const CAnimationManager& rhs)
{
    (void)rhs;

    return *this;
}
