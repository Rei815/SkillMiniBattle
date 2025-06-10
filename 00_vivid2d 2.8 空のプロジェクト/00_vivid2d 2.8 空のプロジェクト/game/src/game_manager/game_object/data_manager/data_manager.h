#pragma once

#include "vivid.h"
#include <list>
#include "../unit_manager/unit/player/player.h"
#include "../unit_manager/unit/unit_id.h"
#include "../scene_manager/scene/game/game_id.h"

class CDataManager
{
public:
    /*!
     *  @brief      インスタンスの取得
     *
     *  @return     インスタンス
     */
    static CDataManager& GetInstance(void);

    /*!
     *  @brief      初期化
     */
    void            Initialize(void);

    /*!
     *  @brief      更新
     */
    void            Update(void);

    /*!
     *  @brief      解放
     */
    void            Finalize(void);

    /*!
     *  @brief      プレイヤーを勝たせる
     *
     *  @param[in]  unitID     ユニットID
     */
    void            PlayerWin(UNIT_ID unitID);

    /*!
     *  @brief      参加しているプレイヤーの数を取得
     *
     *  @return     プレイヤーの数
     */
    int             GetCurrentPlayer();

    /*!
     *  @brief      参加しているプレイヤーの数を設定
     *
     *  @param[in]  num     プレイヤーの数
     */
    void            SetCurrentPlayer(int num);

    /*!
     *  @brief      ゲームのIDを取得
     *
     *  @return     ゲームのID
     */
    GAME_ID         GetSelectGameID();

    /*!
     *  @brief      ゲームのIDを設定
     *
     *  @param[in]  gameID     ゲームのID
     */
    void            SetGameID(GAME_ID gameID);

    /*!
     *  @brief      プレイヤーの勝利を取得
     *
     *  @param[in]  unitID     ユニットのID
     * 
     *  @return     プレイヤーの勝利数
     */
    int             GetPlayerWin(int unitID);

    /*!
     *  @brief      ミニゲームの数を取得
     *
     *  @return     ミニゲームの数
     */
    int             GetMaxGameNum();
    /*!
     *  @brief      前回のミニゲームのランキングをリセット
     */
    void            ResetLastGameRanking();

    /*!
     *  @brief      前回のミニゲームのランキングにプレイヤーを追加
     */
    void            AddLastGameRanking(UNIT_ID unit_id);

    /*!
     *  @brief      前回のミニゲームのランキングを取得
     * 
     *  @param[in]  num     ユニットのID
     *  @return     ユニットのID
     */
    UNIT_ID         GetLastGameRanking(int num);

    /*!
     *  @brief      コントローラーの接続数を取得
     *
     *  @return     コントローラーの接続数
     */
    int             GetConnectControllerNum();
private:

    /*!
     *  @brief      コンストラクタ
     */
    CDataManager(void);

    /*!
     *  @brief      コピーコンストラクタ
     *
     *  @param[in]  rhs     オブジェクト
     */
    CDataManager(const CDataManager& rhs);

    /*!
     *  @brief      デストラクタ
     */
    ~CDataManager(void);

    /*!
     *  @brief      代入演算子
     *
     *  @param[in]  rhs 代入オブジェクト
     *
     *  @return     自身のオブジェクト
     */
    CDataManager& operator=(const CDataManager& rhs);

    static const int    m_max_game_num;                         //!< 最大のゲーム数

    UNIT_ID             m_LastGameRanking[(int)UNIT_ID::NONE];  //!< 1つ前のゲームのランキング
    int                 m_NowGameRankingNum;                    //!< 1つ前のゲームのランキングをつけるため、次の順位を格納する変数
    int                 m_PlayerWins[(int)UNIT_ID::NONE];       //!< プレイヤーの勝利数
    int                 m_CurrentJoinPlayerNum;                 //!< 現在の参加しているプレイヤー
    GAME_ID             m_CurrentGameID;                        //!< 現在選ばれているゲームのID
};