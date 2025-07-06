#pragma once

#include "vivid.h"
#include <list>
#include "../scene_manager/scene/game/game_id.h"
#include "../../../game/components/player_component/player_id.h"

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
    void            PlayerWin(PLAYER_ID unitID);

    /*!
     *  @brief      参加しているプレイヤーの数を取得
     *
     *  @return     プレイヤーの数
     */
    int             GetCurrentJoinPlayer();

    /*!
     *  @brief      参加しているプレイヤーの数を設定
     *
     *  @param[in]  num     プレイヤーの数
     */
    void            SetCurrentJoinPlayer(int num);

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
     *  @brief      必要な勝利数を取得
     *
     *  @return     必要な勝利数
     */
    int             GetRequiredWins();

    /*!
     *  @brief      最大の参加可能なプレイヤーの数を取得
     *
     *  @return     最大の参加可能なプレイヤーの数を取得
     */
    int             GetMaxJoinPlayerNum();

    /*!
     *  @brief      操作可能なコントローラー数を取得
     *
     *  @return     操作可能なコントローラー数
     */
    int             GetActiveControllerNum();

    /*!
     *  @brief      前回のミニゲームのランキングをリセット
     */
    void            ResetLastGameRanking();

    /*!
     *  @brief      前回のミニゲームのランキングにプレイヤーを追加
     */
    void            AddLastGameRanking(PLAYER_ID unit_id);

    /*!
     *  @brief      前回のミニゲームのランキングを取得
     * 
     *  @param[in]  num     ユニットのID
     *  @return     ユニットのID
     */
    PLAYER_ID         GetLastGameRanking(int num);

    /*!
     *  @brief      コントローラーの接続数を取得
     *
     *  @return     コントローラーの接続数
     */
    int             GetConnectControllerNum();

    static const int    m_max_player_join = 4;                      //!< 参加可能な最大人数
    static const int    m_active_controller_num = 5;                //!< 操作可能なコントローラー数

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
    static const int    m_required_wins;                        //!< 必要な勝利数
    static const int    m_min_player_join;                      //!< ゲームに必要な最小の人数

    PLAYER_ID             m_LastGameRanking[(int)PLAYER_ID::NONE];  //!< 1つ前のゲームのランキング
    int                 m_NowGameRankingNum;                    //!< 1つ前のゲームのランキングをつけるため、次の順位を格納する変数
    int                 m_PlayerWins[(int)PLAYER_ID::NONE];       //!< プレイヤーの勝利数
    int                 m_CurrentJoinPlayerNum;                 //!< 現在の参加しているプレイヤー
    GAME_ID             m_CurrentGameID;                        //!< 現在選ばれているゲームのID

};