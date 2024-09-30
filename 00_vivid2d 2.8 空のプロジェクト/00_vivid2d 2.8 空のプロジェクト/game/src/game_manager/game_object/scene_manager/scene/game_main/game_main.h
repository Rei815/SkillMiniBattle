
/*!
 *  @file       game_main.h
 *  @brief      ゲームメインシーン
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"
#include"..\scene.h"
#include "../../../model_manager/model/model.h"
#include "../../../stage/stage.h"
 
 /*!
  *  @brief  ゲームの状態
  */
enum class GAME_STATE
{
    START,
    WAVE_START,
    WAVE,
    WAVE_CLEAR,
    GAMEOVER,
    GAMECLEAR,
};

class CModel;
/*!
 *  @class      CGameMain
 *
 *  @brief      ゲームメインシーン
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
class CGameMain
    : public IScene
{
public:

    enum class WAVE_STATE
    {
        WAVE,
        WAVE_FINISH,
        WAVE_CLEAR,
        WAVE_REWARD,
    };

    /*!
     *  @brief      コンストラクタ
     */
    CGameMain(void);

    /*!
     *  @brief      デストラクタ
     */
    ~CGameMain(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(void);

    /*!
     *  @brief      更新
     */
    void        Update(void);

    /*!
     *  @brief      描画
     */
    void        Draw(void);

    /*!
     *  @brief      解放
     */
    void        Finalize(void);

    /*!
     *  @brief      ゲームの状態取得
     *
     *  @return     ゲームの状態ID
     */
    GAME_STATE  GetGameState(void);

    /*!
     *  @brief      ゲームの状態設定
     *
     *  @param[in]  state   ゲーム状態ID
     */
    void        SetGameState(GAME_STATE state);


    /*!
     *  @brief      Waveのアクティブ設定
     *
     */
    void SetActiveWave(bool active);

    /*!
     *  @brief      Waveのクリア設定
     *
     */
    void SetWaveState(WAVE_STATE state);

    /*!
     *  @brief      報酬フラグ取得
     *
     *  @return     報酬フラグ
     */
    bool GetReceiveReward(void);

private:


    /*!
     *  @brief      スタート
     */
    void    Start(void);

    /*!
     *  @brief      プレイ
     */
    void    Wave(void);

    /*!
     *  @brief      ゲームオーバー
     */
    void    GameOver(void);

    /*!
     *  @brief      ゲームクリア
     */
    void    GameClear(void);

    /*!
     *  @brief      Wave更新
     */
    void        UpdateWave(void);
    /*!
     *  @brief      WaveFinish更新
     */
    void        UpdateWaveFinish(void);
    /*!
     *  @brief      WaveClear更新
     */
    void        UpdateWaveClear(void);
    /*!
     *  @brief      WaveReward更新
     */
    void        UpdateWaveReward(void);


    GAME_STATE          m_GameState;            //!< ゲームの状態

    static const int                m_fight_width;          //!< FIGHTの幅
    static const int                m_fight_height;         //!< FIGHTの高さ
    static const int                m_gameclear_width;      //!< ゲームクリアの幅
    static const int                m_gameclear_height;     //!< ゲームクリアの高さ
    static const int                m_gameover_width;       //!< ゲームオーバーの幅
    static const int                m_gameover_height;      //!< ゲームオーバーの高さ
    static const vivid::Vector2     m_fight_position;       //!< ゲーム開始位置
    static const vivid::Vector2     m_gameclear_position;   //!< ゲームクリア開始位置
    static const vivid::Vector2     m_gameover_position;    //!< ゲームオーバー開始位置
    static const int                m_wave_interval;        //!< Wave間の待機時間
    static const int                m_start_wave_interval;  //!< Wave開始からの待機時間


    int                             m_WaitTime;             //!< 待機時間
    int                             m_FightAlpha;           //!< FIGHTアルファ値
    int                             m_GameOverAlpha;        //!< ゲームオーバーアルファ値
    int                             m_GameClearAlpha;       //!< ゲームクリアアルファ値
    vivid::Vector2                  m_FightScale;           //!< FIGHT拡大率
    vivid::Vector2                  m_GameClearScale;       //!< ゲームクリア拡大率
    float                           m_GameClearRotation;    //!< ゲームクリア回転値
    bool                            m_PauseFlag;            //!< ポーズフラグ
    bool                            m_ActiveWave;           //!< Wave中かどうか
    bool                            m_StartWave;            //!< Wave開始したかどうか
    bool                            m_WaveClear;            //!< Waveクリアしたかどうか
    int                             m_WaveTimer;            //!< Wave間のタイマー
    int                             m_StartWaveTimer;       //!< Wave開始からののタイマー
    bool                            m_ReceiveReward;        //!< 報酬を受け取れるかどうか

    WAVE_STATE          m_WaveState;

};
