#include "scene_manager.h"
#include "scene\title\title.h"
#include "scene\game_roll_and_reveal\game_roll_and_reveal.h"
#include "scene\select_skill\select_skill.h"
#include "scene\game\game.h"
#include "scene\game\fallout_game\fallout_game.h"
#include "scene\game\daruma_falldown_game\daruma_falldown_game.h"
#include "scene\game\dodgeball_game\dodgeball_game.h"
#include "scene\game\belt_conveyor_game\belt_conveyor_game.h"
#include "scene\minigame_result\minigame_result.h"
#include "scene\game_result\game_result.h"
#include "scene\entry\entry.h"
#include "../ui_manager/ui_manager.h"
#include "../controller_manager/controller_manager.h"
#include "../effect_manager/effect_manager.h"
#include "../ui_manager/ui/pause/pause.h"

const int               CSceneManager::m_fade_speed = 10;
const float             CSceneManager::m_wait_time = 0.0f;

/*
 *  インスタンスの取得
 */
CSceneManager&
CSceneManager::GetInstance(void)
{
    static CSceneManager instance;

    return instance;
}

/*
 *  初期化
 */
void
CSceneManager::Initialize(void)
{
    // ルートシーン生成
    m_NextSceneID = SCENE_ID::TITLE;

    // シーン変更
    m_State = STATE::SCENE_CHANGE;

    m_SceneChangeWaitTimer.SetUp(m_wait_time);
    m_FadeSpeed = m_fade_speed;
    m_FadeColor = 0x00ffffff;
    m_PauseController = nullptr;
}

/*
 *  更新
 */
void
CSceneManager::Update(void)
{
    switch (m_State)
    {
    case STATE::FADEIN:          FadeIn();      break;
    case STATE::SCENE_UPDATE:    SceneUpdate();  break;
    case STATE::FADEOUT:         FadeOut();     break;
    case STATE::SCENE_CHANGE:    SceneChange(); break;
    }
    CUIManager& um = CUIManager::GetInstance();
    um.Update();

    CEffectManager& em = CEffectManager::GetInstance();
    CControllerManager& cm = CControllerManager::GetInstance();

    if(m_PauseController == nullptr)
        m_PauseController = cm.GetSpecifiedButtonDownController(BUTTON_ID::START);
    if (m_PauseController == nullptr) return;
        m_PauseController->Update();
        if (m_PauseController->GetButtonDown(BUTTON_ID::START) && 
            GetLastSceneID() != SCENE_ID::TITLE && m_State == STATE::SCENE_UPDATE)
    {
        Pause();
    }
}

/*
 *  描画
 */
void
CSceneManager::Draw(void)
{
    // シーン描画
    if (m_SceneList.empty()) return;

    SCENE_LIST::iterator it = m_SceneList.begin();

    while (it != m_SceneList.end())
    {
        (*it)->Draw();

        ++it;
    }
    CUIManager::GetInstance().Draw();

}

/*
 *  シーンエフェクト描画
 */
void
CSceneManager::DrawSceneEffect(void)
{
    vivid::DrawTexture("data\\Textures\\white.png", vivid::Vector2(), m_FadeColor);

}

/*
 *  解放
 */
void
CSceneManager::Finalize(void)
{
    // シーン解放
    if (m_SceneList.empty()) return;

    SCENE_LIST::iterator it = m_SceneList.begin();

    while (it != m_SceneList.end())
    {
        (*it)->Finalize();

        it = m_SceneList.erase(it);

        continue;
    }

    m_SceneList.clear();
}

/*
 *  シーン切換え
 */
void
CSceneManager::ChangeScene(SCENE_ID id)
{
    // 次のシーンIDを登録
    m_NextSceneID = id;

    m_ChangeScene = true;
}

void CSceneManager::PushScene(SCENE_ID id)
{
    CreateScene(id);
}

void CSceneManager::RemoveScene(SCENE_ID id)
{
    if (m_SceneList.size() <= 1) return;

    SCENE_LIST::iterator it = m_SceneList.begin();
    while (it != m_SceneList.end())
    {
        std::shared_ptr<IScene> scene = *it;

        if (scene->GetSceneID() == id)
        {
            scene->Delete();
            return;
        }
        ++it;
    }
}

CSceneManager::SCENE_LIST CSceneManager::GetList()
{
    return m_SceneList;
}

bool CSceneManager::Pausing(void)
{
    return m_PauseFlag;
}

void CSceneManager::SetPauseFlag(bool flag)
{
    m_PauseFlag = flag;
}

SCENE_ID CSceneManager::GetLastSceneID(void)
{
    if (!m_SceneList.empty())
    {
        SCENE_LIST::iterator it = m_SceneList.end();
        --it;

        return (*it)->GetSceneID();
    }
    else
        return SCENE_ID::DUMMY;
}

void CSceneManager::Pause()
{
    CUIManager& um = CUIManager::GetInstance();

    CEffectManager& em = CEffectManager::GetInstance();

    if (m_PauseFlag == false)
        em.PauseAllEffect();
    else
        em.ResumeAllEffect();


    if (m_PauseFlag)
    {
        um.Delete(UI_ID::PAUSE);
        m_PauseController = nullptr;
    }
    else
    {
        std::shared_ptr<CPause> pause = dynamic_pointer_cast<CPause>(um.Create(UI_ID::PAUSE));
        pause->SetPauseController(m_PauseController);
    }
    m_PauseFlag ^= true;

}

/*
 *  コンストラクタ
 */
CSceneManager::CSceneManager(void)
    : m_SceneList()
    , m_CurrentSceneID(SCENE_ID::DUMMY)
    , m_NextSceneID(SCENE_ID::DUMMY)
    , m_ChangeScene(false)
    , m_PauseController(nullptr)
{
}

/*
 *  コピーコンストラクタ
 */
CSceneManager::CSceneManager(const CSceneManager& rhs)
{
    (void)rhs;

}

/*
 *  デストラクタ
 */
CSceneManager::~CSceneManager(void)
{
}

/*
 *  代入演算子
 */
CSceneManager&
CSceneManager::operator=(const CSceneManager& rhs)
{
    (void)rhs;

    return *this;
}

/*
 *  シーン生成
 */
std::shared_ptr<IScene>
CSceneManager::CreateScene(SCENE_ID id)
{
    //IDを基準にシーン多分岐
    std::shared_ptr<IScene> scene = nullptr;

    switch (id)
    {
    case SCENE_ID::TITLE:               scene = std::make_shared<CTitle>();                 break;
    case SCENE_ID::SELECT_SKILL:        scene = std::make_shared<CSelectSkill>();           break;
    case SCENE_ID::GAME_ROLL_AND_REVEAL:scene = std::make_shared<CGameRollAndReveal>();     break;
    case SCENE_ID::FALL_GAME:           scene = std::make_shared<CFallOutGame>();           break;
    case SCENE_ID::DARUMA_FALLDOWN_GAME:scene = std::make_shared<CDaruma_FallDownGame>();   break;
    case SCENE_ID::DODGEBALL_GAME:      scene = std::make_shared<CDodgeBallGame>();         break;
    case SCENE_ID::BELTCONVEYOR_GAME:   scene = std::make_shared<CBeltConveyorGame>();      break;
    case SCENE_ID::MINIGAME_RESULT:     scene = std::make_shared<CMiniGameResult>();        break;
    case SCENE_ID::GAME_RESULT:         scene = std::make_shared<CGameResult>();            break;
    case SCENE_ID::ENTRY:               scene = std::make_shared<CEntry>();                 break;
    }
    m_SceneList.emplace_back(scene);
    
    //初期化
    scene->Initialize(id);

    //初期化時の調整を反映するため、1フレーム分だけ更新する
    scene->Update();

    return scene;
}

/*
 *  フェードイン
 */
void
CSceneManager::FadeIn(void)
{
    unsigned int alpha = vivid::alpha::GetAlpha(m_FadeColor);
    if (alpha == 0u)
    {
        m_FadeSpeed = m_fade_speed;

        // シーン更新
        m_State = STATE::SCENE_UPDATE;
    }
    m_FadeColor = vivid::alpha::AdjustAlpha(m_FadeColor, m_FadeSpeed);

}

/*
 *  シーン更新
 */
void
CSceneManager::SceneUpdate(void)
{
    // シーン更新
    if (m_SceneList.empty()) return;

    SCENE_LIST::iterator it = m_SceneList.begin();

    while (it != m_SceneList.end())
    {
        std::shared_ptr<IScene> scene = *it;

        //アクティブかつポーズ中でない
        if(scene->GetSceneState() == SCENE_STATE::ACTIVE && !m_PauseFlag)
            scene->Update();

        if (!scene->IsActive())
        {
            scene->Finalize();

            it = m_SceneList.erase(it);

            continue;
        }

        ++it;
    }

    // シーン変更が発生
    if (m_CurrentSceneID != m_NextSceneID || m_ChangeScene)
    {
        // フェードアウト
        m_State = STATE::FADEOUT;

        m_ChangeScene = false;
    }
}

/*
 *  フェードアウト
 */
void
CSceneManager::FadeOut(void)
{
    unsigned int alpha = vivid::alpha::GetAlpha(m_FadeColor);
    if (alpha == 255u)
    {
        m_SceneChangeWaitTimer.Update();
        if (m_SceneChangeWaitTimer.Finished())
        {
            m_SceneChangeWaitTimer.Reset();
            // シーン変更
            m_State = STATE::SCENE_CHANGE;
            m_FadeSpeed = -m_fade_speed;
        }
    }

    m_FadeColor = vivid::alpha::AdjustAlpha(m_FadeColor, m_FadeSpeed);
}

/*
 *  シーン変更
 */
void
CSceneManager::SceneChange()
{
    if (!m_SceneList.empty())
    {
        SCENE_LIST::iterator it = m_SceneList.begin();
        while (it != m_SceneList.end())
        {
            std::shared_ptr<IScene> scene = *it;
            if (scene->IsActive() == true)
            {
                scene->Finalize();

                it = m_SceneList.erase(it);

                scene = nullptr;
            }

        }
    }

    // 新しいシーン生成
    CreateScene(m_NextSceneID);

    m_CurrentSceneID = m_NextSceneID;

    // フェードイン
    m_State = STATE::FADEIN;
}

std::shared_ptr<IScene> CSceneManager::GetScene(SCENE_ID scene_id)
{
    if (m_SceneList.empty()) return nullptr;

    SCENE_LIST::iterator it = m_SceneList.begin();

    while (it != m_SceneList.end())
    {
        std::shared_ptr<IScene> scene = *it;

        if (scene->IsActive() && scene->GetSceneID() == scene_id)
            return scene;

        ++it;
    }
    return nullptr;
}