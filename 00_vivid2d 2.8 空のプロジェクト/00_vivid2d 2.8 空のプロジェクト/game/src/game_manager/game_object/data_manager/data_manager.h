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
    void        Initialize(void);

    /*!
     *  @brief      更新
     */
    void        Update(void);

    /*!
     *  @brief      解放
     */
    void        Finalize(void);

    void        PlayerWin(UNIT_ID unitID);

    int         GetCurrentPlayer();

    void        SetCurrentPlayer(int num);

    GAME_ID     GetGameID();

    void        SetGameID(GAME_ID gameID);

    int         GetPlayerWin(int unitID);

    int         GetMaxGameNum();

    void        SetMaxGameNum(int num);

    void        ResetLastGameRanking();

    void        AddLastGameRanking(UNIT_ID unit_id);

    UNIT_ID     GetLastGameRanking(int num);
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

    /*!
     *  @brief      プレイヤーリスト型
     */
    using RANKING_LIST = std::vector<CPlayer*>;
    
    
    RANKING_LIST        m_OverallRankingList[(int)UNIT_ID::NONE];             //!< 全体のランキングリスト

    UNIT_ID             m_LastGameRanking[(int)UNIT_ID::NONE];              //1つ前のゲームのランキング
    int                 m_NowGameRankingNum;                                //1つ前のゲームのランキングをつけるため、次の順位を格納する変数

    int                 m_PlayerWins[(int)UNIT_ID::NONE];
    int                 m_CurrentPlayerNum;

    GAME_ID             m_CurrentGameID;

    int                 m_MaxGameNum;
};