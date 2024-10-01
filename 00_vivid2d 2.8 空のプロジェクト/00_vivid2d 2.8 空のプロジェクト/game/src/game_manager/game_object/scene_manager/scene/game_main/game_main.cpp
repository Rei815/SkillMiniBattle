
/*!
 *  @file       game_main.cpp
 *  @brief      ゲームメインシーン
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "game_main.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../ui_manager/ui_manager.h"
#include "../../../controller_manager/controller_manager.h"
#include "../../../unit_manager/unit/player/player.h"

const int               CGameMain::m_fight_width = 205;
const int               CGameMain::m_fight_height = 53;
const int               CGameMain::m_gameclear_width = 368;
const int               CGameMain::m_gameclear_height = 54;
const int               CGameMain::m_gameover_width = 361;
const int               CGameMain::m_gameover_height = 54;
const vivid::Vector2    CGameMain::m_fight_position = vivid::Vector2((float)vivid::WINDOW_WIDTH / 2.0f - (float)m_fight_width / 2.0f, (float)vivid::WINDOW_HEIGHT / 2.0f - (float)m_fight_height / 2.0f);
const vivid::Vector2    CGameMain::m_gameclear_position = vivid::Vector2((float)vivid::WINDOW_WIDTH / 2.0f - (float)m_gameclear_width / 2.0f, (float)vivid::WINDOW_HEIGHT / 2.0f - (float)m_gameclear_height / 2.0f);
const vivid::Vector2    CGameMain::m_gameover_position = vivid::Vector2((float)vivid::WINDOW_WIDTH / 2.0f - (float)m_gameover_width / 2.0f, (float)vivid::WINDOW_HEIGHT / 2.0f - (float)m_gameover_height / 2.0f);
const int               CGameMain::m_wave_interval = 120;
const int               CGameMain::m_start_wave_interval = 120;

/*
 *  コンストラクタ
 */
CGameMain::CGameMain(void)
{
}

/*
 *  デストラクタ
 */
CGameMain::~CGameMain(void)
{
}

/*
 *  初期化
 */
void
CGameMain::Initialize(void)
{
    CBulletManager::GetInstance().Initialize();
    CUnitManager::GetInstance().Initialize();
    CUIManager::GetInstance().Initialize();
    CEffectManager::GetInstance().Initialize();
    CLauncher::GetInstance().Initialize();
    CControllerManager::GetInstance().Initialize();
    CStage::GetInstance().Initialize();

    CUnitManager::GetInstance().Create(UNIT_ID::PLAYER1, CVector3(0, 0, -1000));
    CUIManager::GetInstance().Create(UI_ID::PLAYER_LIFE);
    CUIManager::GetInstance().Create(UI_ID::RETICLE);

    m_WaitTime = 0;

    m_FightAlpha = 255;
    m_GameOverAlpha = 0;
    m_GameClearAlpha = 0;
    m_FightScale = vivid::Vector2(1.0f, 1.0f);
    m_GameClearScale = vivid::Vector2(10.0f, 10.0f);

    m_GameClearRotation = 0.0f;
    m_StartWaveTimer = 0;

    m_GameState = GAME_STATE::START;
    m_WaveState = WAVE_STATE::WAVE;

    m_PauseFlag = false;
    m_WaveClear = false;
    m_StartWave = true;
    m_ReceiveReward = false;
}

/*
 *  更新
 */
void
CGameMain::Update(void)
{
    switch (m_GameState)
    {
    case GAME_STATE::START:         Start();       break;
    case GAME_STATE::WAVE:          Wave();        break;
    case GAME_STATE::GAMEOVER:      GameOver();    break;
    case GAME_STATE::GAMECLEAR:     GameClear();   break;
    }

    if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::TAB))
    {
        if (m_PauseFlag)
             CUIManager::GetInstance().Delete(UI_ID::PAUSE);
        else CUIManager::GetInstance().Create(UI_ID::PAUSE);

        m_PauseFlag ^= true;
    }
    if(!m_PauseFlag)
    {
        CLauncher::GetInstance().Update();
        CStage::GetInstance().Update();
        CUnitManager::GetInstance().Update();

        CBulletManager& bm = CBulletManager::GetInstance();
        bm.Update();
        bm.CheckHitModel(CStage::GetInstance().GetModel());

        CEffectManager::GetInstance().Update();

        CUIManager::GetInstance().Update();
    }
    CControllerManager::GetInstance().Update();

}

/*
 *  描画
 */
void
CGameMain::Draw(void)
{
    CStage::GetInstance().Draw();

    CEffectManager::GetInstance().Draw();
    CBulletManager::GetInstance().Draw();
    CUnitManager::GetInstance().Draw();
    CUIManager::GetInstance().Draw();
    switch (m_GameState)
    {
    case GAME_STATE::START:
    {
        if (m_WaitTime < 30) break;

        const vivid::Rect rect = { 0, 0, m_fight_width, m_fight_height };
        const vivid::Vector2 anchor((float)m_fight_width / 2.0f, (float)m_fight_height / 2.0f);
        vivid::DrawTexture("data\\Textures\\fight.png", m_fight_position);
        vivid::DrawTexture("data\\Textures\\fight.png", m_fight_position, (m_FightAlpha << 24) | 0x00ffffff, rect, anchor, m_FightScale, 0.0f, vivid::ALPHABLEND::ADD);
    }
    break;
    case GAME_STATE::GAMEOVER:
    {
        if (m_WaitTime < 30) break;

        const vivid::Rect rect = { 0, 0, m_gameover_width, m_gameover_height };
        const vivid::Vector2 anchor((float)m_gameover_width / 2.0f, (float)m_gameover_height / 2.0f);

        vivid::DrawTexture("data\\Textures\\gameover.png", m_gameclear_position, (m_GameOverAlpha << 24) | 0x00ffffff);
    }
    break;
    case GAME_STATE::GAMECLEAR:
    {
        if (m_WaitTime < 30) break;

        const vivid::Rect rect = { 0, 0, m_gameclear_width, m_gameclear_height };
        const vivid::Vector2 anchor((float)m_gameclear_width / 2.0f, (float)m_gameclear_height / 2.0f);

        vivid::DrawTexture("data\\Textures\\gameclear.png", m_gameover_position, (m_GameClearAlpha << 24) | 0x00ffffff, rect, anchor, m_GameClearScale, m_GameClearRotation);
    }
    break;
    }
}

/*
 *  解放
 */
void
CGameMain::Finalize(void)
{
    CBulletManager::GetInstance().Finalize();
    CUnitManager::GetInstance().Finalize();
    CUIManager::GetInstance().Finalize();
    CEffectManager::GetInstance().Finalize();
    CControllerManager::GetInstance().Finalize();

    CStage::GetInstance().Finalize();
}

/*
 *  ゲームの状態取得
 */
GAME_STATE
CGameMain::GetGameState(void)
{
    return m_GameState;
}

/*
 *  ゲームの状態設定
 */
void
CGameMain::
SetGameState(GAME_STATE state)
{
    m_GameState = state;
}


void CGameMain::SetActiveWave(bool active)
{
    m_ActiveWave = active;
}

void CGameMain::SetWaveState(WAVE_STATE state)
{
    m_WaveState = state;
}


/*
 *  スタート
 */
void
CGameMain::Start(void)
{
    if (m_WaitTime > 120)
    {
        m_WaitTime = 0;

        m_GameState = GAME_STATE::WAVE;
    }
    else if (m_WaitTime > 30)
    {
        m_FightAlpha -= 10;

        if (m_FightAlpha < 0)
            m_FightAlpha = 0;

        m_FightScale.x += 0.01f;
        m_FightScale.y += 0.01f;

        if (m_FightScale.x > 1.5f)
            m_FightScale.x = m_FightScale.y = 1.5f;
    }

    ++m_WaitTime;

}

/*
 *  プレイ
 */
void
CGameMain::
Wave(void)
{
    switch (m_WaveState)
    {
    case WAVE_STATE::WAVE:              UpdateWave();       break;
    case WAVE_STATE::WAVE_FINISH:       UpdateWaveFinish(); break;
    case WAVE_STATE::WAVE_CLEAR:        UpdateWaveClear();  break;
    case WAVE_STATE::WAVE_REWARD:       UpdateWaveReward(); break;
    }

    CUnitManager& um = CUnitManager::GetInstance();

    if (!um.GetPlayer())        m_GameState = GAME_STATE::GAMEOVER;

    if (um.CheckDestoryBoss())  m_GameState = GAME_STATE::GAMECLEAR;
}

/*
 *  ゲームオーバー
 */
void
CGameMain::
GameOver(void)
{
    if (m_WaitTime > 240)
    {
        CSoundManager::GetInstance().Play(SOUND_ID::GAMEOVER);

        m_WaitTime = 0;

        CSceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
    }
    else if (m_WaitTime > 30)
    {
        m_GameOverAlpha += 2;

        if (m_GameOverAlpha > 255)
            m_GameOverAlpha = 255;
    }

    ++m_WaitTime;
}

/*
 *  ゲームクリア
 */
void
CGameMain::
GameClear(void)
{
    if (m_WaitTime > 240)
    {
        m_WaitTime = 0;

        CSoundManager::GetInstance().Play(SOUND_ID::GAMECLEAR);

        CSceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
    }
    else if (m_WaitTime > 30)
    {
        m_GameClearAlpha += 2;

        if (m_GameClearAlpha > 255)
            m_GameClearAlpha = 255;

        m_GameClearScale.x -= 0.2f;
        m_GameClearScale.y -= 0.2f;

        if (m_GameClearScale.x < 1.0f)
            m_GameClearScale.x = m_GameClearScale.y = 1.0f;

        m_GameClearRotation -= 20.0f * DX_PI_F / 180.0f;

        if (m_GameClearRotation < -1100.0f * DX_PI_F / 180.0f)
            m_GameClearRotation = -1100.0f * DX_PI_F / 180.0f;
    }

    ++m_WaitTime;
}

void CGameMain::UpdateWave(void)
{
    CPlayer* player = CUnitManager::GetInstance().GetPlayer();

    if (m_StartWave)
    {
        if (++m_StartWaveTimer > m_start_wave_interval)
        {
            m_StartWaveTimer = 0;
            m_StartWave = false;
            CUIManager::GetInstance().Create(UI_ID::WAVE_START);
            player->SetFireFlag(true);

        }
    }

    // Waveチェック
    if (CUnitManager::GetInstance().CheckFinishWave())
    {
        player->SetFireFlag(false);

        m_WaveState = WAVE_STATE::WAVE_FINISH;

    }

}

void CGameMain::UpdateWaveFinish(void)
{
    CUnitManager::GetInstance().SetGenerateFlag(false);

    m_WaveState = WAVE_STATE::WAVE_CLEAR;
}

void CGameMain::UpdateWaveClear(void)
{
    if (!m_WaveClear)
    {
        m_WaveClear = true;
        CUIManager::GetInstance().Create(UI_ID::WAVE_CLEAR);
        CUIManager::GetInstance().SetWaveClearUIActive(true);
    }

    if (m_WaveClear && !CUIManager::GetInstance().GetWaveClearUIActive())
        m_WaveState = WAVE_STATE::WAVE_REWARD;



}

void CGameMain::UpdateWaveReward(void)
{
    if (!m_ReceiveReward && !CUnitManager::GetInstance().GetAppearBossFlag())
    {
        m_ReceiveReward = true;

        CUIManager::GetInstance().Create(UI_ID::WAVE_REWARD);
        CPlayer* player = CUnitManager::GetInstance().GetPlayer();
        player->SetActionFlag(false);
    }
    if (m_ReceiveReward && CUIManager::GetInstance().GetReceivedReward())
    {
        CUIManager::GetInstance().SetReceivedReward(false);
        m_WaveTimer = 0;
        CUnitManager::GetInstance().SetAppearFinalEnemyFlag(false);
        CUnitManager::GetInstance().AddWaveCurrentCount();
        m_WaveClear = false;
        m_ReceiveReward = false;
        m_StartWave = true;
        CPlayer* player = CUnitManager::GetInstance().GetPlayer();
        player->SetActionFlag(true);

        m_WaveState = WAVE_STATE::WAVE;
    }

}

bool CGameMain::GetReceiveReward(void)
{
    return m_ReceiveReward;
}

