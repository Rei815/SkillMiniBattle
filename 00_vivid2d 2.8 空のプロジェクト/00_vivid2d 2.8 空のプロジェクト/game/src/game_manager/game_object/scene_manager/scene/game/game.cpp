
#include "game.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../ui_manager/ui_manager.h"
#include "../../../controller_manager/controller_manager.h"
#include "../../../unit_manager/unit/player/player.h"

const int               CGame::m_fight_width = 205;
const int               CGame::m_fight_height = 53;
const int               CGame::m_gameclear_width = 368;
const int               CGame::m_gameclear_height = 54;
const int               CGame::m_gameover_width = 361;
const int               CGame::m_gameover_height = 54;
const vivid::Vector2    CGame::m_fight_position = vivid::Vector2((float)vivid::WINDOW_WIDTH / 2.0f - (float)m_fight_width / 2.0f, (float)vivid::WINDOW_HEIGHT / 2.0f - (float)m_fight_height / 2.0f);
const vivid::Vector2    CGame::m_gameclear_position = vivid::Vector2((float)vivid::WINDOW_WIDTH / 2.0f - (float)m_gameclear_width / 2.0f, (float)vivid::WINDOW_HEIGHT / 2.0f - (float)m_gameclear_height / 2.0f);
const vivid::Vector2    CGame::m_gameover_position = vivid::Vector2((float)vivid::WINDOW_WIDTH / 2.0f - (float)m_gameover_width / 2.0f, (float)vivid::WINDOW_HEIGHT / 2.0f - (float)m_gameover_height / 2.0f);
const int               CGame::m_wave_interval = 120;
const int               CGame::m_start_wave_interval = 120;

/*
 *  コンストラクタ
 */
CGame::CGame(void)
{
}

/*
 *  デストラクタ
 */
CGame::~CGame(void)
{
}

/*
 *  初期化
 */
void
CGame::Initialize(void)
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

    m_PauseFlag = false;
    m_WaveClear = false;
    m_StartWave = true;
    m_ReceiveReward = false;
}

/*
 *  更新
 */
void
CGame::Update(void)
{
    switch (m_GameState)
    {
    case GAME_STATE::START:     Start();        break;
    case GAME_STATE::PLAY:      Play();         break;
    case GAME_STATE::FINISH:    Finish();       break;
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
CGame::Draw(void)
{
    CStage::GetInstance().Draw();

    CEffectManager::GetInstance().Draw();
    CBulletManager::GetInstance().Draw();
    CUnitManager::GetInstance().Draw();
    CUIManager::GetInstance().Draw();
    switch (m_GameState)
    {
    case GAME_STATE::START:
        break;
    case GAME_STATE::PLAY:
        break;
    case GAME_STATE::FINISH:
        break;
    }
}

/*
 *  解放
 */
void
CGame::Finalize(void)
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
CGame::GetGameState(void)
{
    return m_GameState;
}

/*
 *  ゲームの状態設定
 */
void
CGame::
SetGameState(GAME_STATE state)
{
    m_GameState = state;
}


/*
 *  スタート
 */
void
CGame::Start(void)
{
    if (m_WaitTime > 120)
    {
        m_WaitTime = 0;

        m_GameState = GAME_STATE::PLAY;
    }

    ++m_WaitTime;

}

/*
 *  プレイ
 */
void CGame::Play(void)
{

}

//void
//CGameMain::
//Wave(void)
//{
//    switch (m_WaveState)
//    {
//    case WAVE_STATE::WAVE:              UpdateWave();       break;
//    case WAVE_STATE::WAVE_FINISH:       UpdateWaveFinish(); break;
//    case WAVE_STATE::WAVE_CLEAR:        UpdateWaveClear();  break;
//    case WAVE_STATE::WAVE_REWARD:       UpdateWaveReward(); break;
//    }
//
//    CUnitManager& um = CUnitManager::GetInstance();
//
//    if (!um.GetPlayer())        m_GameState = GAME_STATE::GAMEOVER;
//
//    if (um.CheckDestoryBoss())  m_GameState = GAME_STATE::GAMECLEAR;
//}

/*
 *  ゲームオーバー
 */
void
CGame::
Finish(void)
{
    if (m_WaitTime > 240)
    {
        CSoundManager::GetInstance().Play(SOUND_ID::GAMEOVER);

        m_WaitTime = 0;

        CSceneManager::GetInstance().ChangeScene(SCENE_ID::RESULT);
    }
    else if (m_WaitTime > 30)
    {
        m_GameOverAlpha += 2;

        if (m_GameOverAlpha > 255)
            m_GameOverAlpha = 255;
    }

    ++m_WaitTime;
}

