
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
#include "scene\game\game.h"
#include "scene\game\fall_game\fall_game.h"
#include "scene\game\daruma_falldown_game\daruma_falldown_game.h"
#include "scene\game\dodgeball_game\dodgeball_game.h"
#include "scene\game\debug_game\debug_game.h"
#include "scene\result\result.h"

const int               CSceneManager::m_fade_speed = 5;
const vivid::Vector2    CSceneManager::m_fade_position = { 0.0f, 0.0f };
const unsigned int      CSceneManager::m_fade_color = 0xff000000;
const int               CSceneManager::m_min_fade_alpha = 0;
const int               CSceneManager::m_max_fade_alpha = 255;

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
}

/*
 *  描画
 */
void
CSceneManager::Draw(void)
{
    // シーン描画
    if (m_Scene) m_Scene->Draw();
}

/*
 *  シーンエフェクト描画
 */
void
CSceneManager::DrawSceneEffect(void)
{
}

/*
 *  解放
 */
void
CSceneManager::Finalize(void)
{
    // シーン解放
    if (m_Scene)
    {
        m_Scene->Finalize();

        delete m_Scene;

        m_Scene = nullptr;
    }
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

/*
 *  現在のシーンを取得
 */
IScene*
CSceneManager::GetScene(void)
{
    return m_Scene;
}

/*
 *  コンストラクタ
 */
CSceneManager::CSceneManager(void)
    : m_Scene(nullptr)
    , m_CurrentSceneID(SCENE_ID::WAIT)
    , m_NextSceneID(SCENE_ID::WAIT)
    , m_ChangeScene(false)
    , m_FadeAlpha(m_max_fade_alpha)
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
void
CSceneManager::CreateScene(SCENE_ID id)
{
    //IDを基準にシーン多分岐
    switch (id)
    {
    case SCENE_ID::TITLE:              m_Scene = new CTitle();         break;
    case SCENE_ID::SELECTMODE:         m_Scene = new CSelectMode();    break;
    case SCENE_ID::SELECTPLAYER:       m_Scene = new CSelectPlayer();  break;
    case SCENE_ID::SELECTGAME:         m_Scene = new CSelectGame();    break;
    case SCENE_ID::FALLGAME:           m_Scene = new CFallGame();      break;
    case SCENE_ID::DARUMAFALLDOWN:     m_Scene = new CDaruma_FallDownGame();      break;
    case SCENE_ID::DEBUGGAME:          m_Scene = new CDebugGame();     break;
    case SCENE_ID::RESULT:             m_Scene = new CResult();        break;
    case SCENE_ID::TITLE:        m_Scene = new CTitle();        break;
    case SCENE_ID::SELECTMODE:   m_Scene = new CSelectMode();  break;
    case SCENE_ID::SELECTPLAYER:  m_Scene = new CSelectPlayer();  break;
    case SCENE_ID::SELECTGAME:  m_Scene = new CSelectGame();  break;
    case SCENE_ID::FALLGAME:     m_Scene = new CFallGame();     break;
    case SCENE_ID::DODGEBALLGAME: m_Scene = new CDodgeBallGame();   break;
    case SCENE_ID::DEBUGGAME:     m_Scene = new CDebugGame();     break;
    case SCENE_ID::RESULT:     m_Scene = new CResult();     break;
    }
}

/*
 *  フェードイン
 */
void
CSceneManager::FadeIn(void)
{
    m_FadeAlpha -= m_fade_speed;

    if (m_FadeAlpha < m_min_fade_alpha)
    {
        m_FadeAlpha = m_min_fade_alpha;

        // シーン更新
        m_State = STATE::SCENE_UPDATE;
    }
}

/*
 *  シーン更新
 */
void
CSceneManager::SceneUpdate(void)
{
    // シーン更新
    if (m_Scene) m_Scene->Update();

    // シーン変更が発生
    if (m_CurrentSceneID != m_NextSceneID || m_ChangeScene)
    {
        // フェードアウト
        m_State = STATE::SCENE_CHANGE;

        m_ChangeScene = false;
    }
}

/*
 *  フェードアウト
 */
void
CSceneManager::FadeOut(void)
{
    m_FadeAlpha += m_fade_speed;

    if (m_FadeAlpha > m_max_fade_alpha)
    {
        m_FadeAlpha = m_max_fade_alpha;

        // シーン変更
        m_State = STATE::SCENE_CHANGE;
    }
}

/*
 *  シーン変更
 */
void
CSceneManager::SceneChange(void)
{
    if (m_Scene)
    {
        m_Scene->Finalize();

        delete m_Scene;

        m_Scene = nullptr;
    }

    // 新しいシーン生成
    CreateScene(m_NextSceneID);

    // 初期化
    m_Scene->Initialize();

    // 更新
    m_Scene->Update();

    m_CurrentSceneID = m_NextSceneID;

    // フェードイン
    //m_State = STATE::SCENE_CHANGE;
    m_State = STATE::SCENE_UPDATE;
}
