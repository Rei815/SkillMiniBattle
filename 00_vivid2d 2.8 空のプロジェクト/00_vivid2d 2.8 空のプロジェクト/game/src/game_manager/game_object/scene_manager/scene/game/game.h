#pragma once

#include"..\scene.h"
#include "../../../model/model.h"
#include "game_id.h"
#include "../../../object_manager/object/object.h"
#include "../../../unit_manager/unit/unit.h"
#include "../../../ui_manager/ui/game_bg/game_bg.h"
/*!
*  @brief  ゲームの状態
*/
enum class GAME_STATE
{
    START,
    PLAY,
    FINISH,
};

class CGame : public IScene
{
public:

    /*!
     *  @brief      コンストラクタ
     */
    CGame(void);

    /*!
     *  @brief      デストラクタ
     */
    virtual ~CGame(void);

    /*!
     *  @brief      初期化
     */
    virtual void    Initialize(SCENE_ID scene_id);

    /*!
     *  @brief      更新
     */
    virtual void    Update(void);

    /*!
     *  @brief      描画
     */
    virtual void    Draw(void);

    /*!
     *  @brief      解放
     */
    virtual void    Finalize(void);

    /*!
     *  @brief      ゲームの状態取得
     *
     *  @return     ゲームの状態ID
     */
    GAME_STATE      GetGameState(void);

    /*!
     *  @brief      ゲームの状態設定
     *
     *  @param[in]  state   ゲーム状態ID
     */
    void            SetGameState(GAME_STATE state);

protected:

    /*!
     *  @brief      ランキングに追加
     *
     *  @param[in]  unit   追加するunitのID
     */
    void            AddRanking(UNIT_ID unitID);

    /*!
     *  @brief      スタート
     */
    virtual void    Start(void);

    /*!
     *  @brief      プレイ
     */
    virtual void    Play(void);

    /*!
     *  @brief      終了
     */
    virtual void    Finish(void);

    /*!
     *  @brief      終了判定
     */
    virtual void    CheckFinish(void);

    static const float m_start_count_time;
    static const float m_start_text_time;
    static const float m_finish_text_time;

    GAME_STATE      m_GameState;    //!< ゲームの状態
    CTimer          m_WaitTimer;    //!< 待機時間のタイマー
    bool            m_CountFlag;    //!< カウントダウンのフラグ
    bool            m_SetActionflag;//!< プレイヤーアクションフラグ設定用
    bool            m_FinishFlag;   //!< ミニゲームが終了したか
    bool            m_ResultFlag;   //!< リザルトが出ているか

    using ENTRY_LIST = std::list<std::shared_ptr<IUnit>>;   //!< 参加もしくは生存中のプレイヤーのリスト
    using RESULT_LIST = std::list<std::shared_ptr<IUnit>>;  //!< 敗北してリザルトに移ったプレイヤーのリスト

    ENTRY_LIST          m_EntryList;    //!< エントリーリスト
    RESULT_LIST         m_ResultList;   //!< リザルトリスト

    CTimer              m_PlayTimer;    //!< プレイ中のタイマー
    CGameBG             m_BackGround;   //!< ゲーム背景(UIリストとは別で動かす)

};