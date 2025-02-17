
/*!
 *  @file       scene_manager.cpp
 *  @brief      シーン管理
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "scene_manager.h"
#include "scene\title\title.h"
#include "scene\select_mode\select_mode.h"
#include "scene\select_player\select_player.h"
#include "scene\select_game\select_game.h"
#include "scene\select_skill\select_skill.h"
#include "scene\game\game.h"
#include "scene\game\fallout_game\fallout_game.h"
#include "scene\game\daruma_falldown_game\daruma_falldown_game.h"
#include "scene\game\dodgeball_game\dodgeball_game.h"
#include "scene\game\belt_conveyor_game\belt_conveyor_game.h"
#include "scene\game\debug_game\debug_game.h"
#include "scene\result_minigame\result_minigame.h"
#include "scene\result_game\result_game.h"
#include "scene\game\maze_game\maze_game.h"
#include "../ui_manager/ui_manager.h"
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

    m_Timer.SetUp(m_wait_time);
    m_FadeSpeed = m_fade_speed;
    m_FadeColor = 0x00ffffff;
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
    case STATE::SCENE_UPDATE:    SceneUpdate(); break;
    case STATE::FADEOUT:         FadeOut();     break;
    case STATE::SCENE_CHANGE:    SceneChange(); break;
    }


    CGame* gameScene = GetGameScene();
    //ゲーム中はポーズ中にUIの動きを止める
    if (gameScene)
    {
        if(!gameScene->GetPauseFlag())
            CUIManager::GetInstance().Update();
    }
    else
    {
        CUIManager::GetInstance().Update();
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
    //// シーン解放
    //if (m_SceneList.empty()) return;

    //SCENE_LIST::iterator it = m_SceneList.begin();

    //while (it != m_SceneList.end())
    //{
    //    (*it)->Finalize();

    //    delete (*it);

    //    m_SceneList.erase(it);

    //    ++it;
    //}

    //m_SceneList.clear();
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

void CSceneManager::PopScene(SCENE_ID id)
{
    if (m_SceneList.size() <= 1) return;

    SCENE_LIST::iterator it = m_SceneList.begin();
    while (it != m_SceneList.end())
    {
        IScene* scene = (IScene*)(*it);

        if (scene->GetSceneID() == id)
        {
            scene->SetActive(false);
            return;
        }
        ++it;
    }
}

CSceneManager::SCENE_LIST CSceneManager::GetList()
{
    return m_SceneList;
}

/*
 *  現在のシーンを取得
 */
//IScene*
//CSceneManager::GetScene(void)
//{
//    return m_Scene;
//}

SCENE_ID CSceneManager::GetLastSceneID(void)
{
    if (!m_SceneList.empty())
    {
        SCENE_LIST::iterator it = m_SceneList.end();
        --it;

        return (*it)->GetSceneID();
    }
    else
        return SCENE_ID::WAIT;
}

/*
 *  コンストラクタ
 */
CSceneManager::CSceneManager(void)
    : m_SceneList()
    , m_CurrentSceneID(SCENE_ID::WAIT)
    , m_NextSceneID(SCENE_ID::WAIT)
    , m_ChangeScene(false)
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
IScene*
CSceneManager::CreateScene(SCENE_ID id)
{
    //IDを基準にシーン多分岐
    IScene* scene = nullptr;

    switch (id)
    {
    case SCENE_ID::TITLE:               scene = new CTitle();                   break;
    case SCENE_ID::SELECTMODE:          scene = new CSelectMode();              break;
    case SCENE_ID::SELECTPLAYER:        scene = new CSelectPlayer();            break;
    case SCENE_ID::SELECTSKILL:         scene = new CSelectSkill();             break;
    case SCENE_ID::SELECTGAME:          scene = new CSelectGame();              break;
    case SCENE_ID::FALLGAME:            scene = new CFallOutGame();             break;
    case SCENE_ID::DARUMAFALLDOWN:      scene = new CDaruma_FallDownGame();     break;
    case SCENE_ID::DODGEBALLGAME:       scene = new CDodgeBallGame();           break;
    case SCENE_ID::BELTCONVEYORGAME:    scene = new CBeltConveyorGame();        break;
    case SCENE_ID::DEBUGGAME:           scene = new CDebugGame();               break;
    case SCENE_ID::RESULT_MINIGAME:     scene = new CResultMiniGame();          break;
    case SCENE_ID::RESULT_GAME:         scene = new CResultGame();              break;
    case SCENE_ID::MAZE_GAME:           scene = new CMazeGame();                break;
    }
    m_SceneList.push_back(scene);
    scene->Initialize(id);
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
        IScene* scene = (IScene*)(*it);
        if(scene->GetSceneState() == SCENE_STATE::ACTIVE)
            scene->Update();

        if (!scene->GetActive())
        {
            scene->Finalize();

            delete scene;

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
        m_Timer.Update();
        if (m_Timer.Finished())
        {
            m_Timer.Reset();
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
            IScene* scene = (IScene*)(*it);
            if (scene->GetActive() == true)
            {
                scene->Finalize();

                delete scene;

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

IScene* CSceneManager::GetScene(SCENE_ID scene_id)
{
    if (m_SceneList.empty()) return nullptr;

    SCENE_LIST::iterator it = m_SceneList.begin();

    while (it != m_SceneList.end())
    {
        IScene* scene = (IScene*)(*it);

        if (scene->GetActive() && scene->GetSceneID() == scene_id)
            return scene;

        ++it;
    }
    return nullptr;
}

CGame* CSceneManager::GetGameScene()
{
    if (m_SceneList.empty()) return nullptr;

    SCENE_LIST::iterator it = m_SceneList.begin();

    while (it != m_SceneList.end())
    {
        CGame* gameScene = dynamic_cast<CGame*>(*it);

        ++it;
        if (gameScene == nullptr) continue;

        if (gameScene->GetActive())
            return gameScene;

    }
    return nullptr;
}
