#pragma once

#include "vivid.h"
#include <list>
#include "../unit_manager/unit/player/player.h"
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
    
    RANKING_LIST        m_OverallRankingList[4];             //!< 全体のランキングリスト

    int                 m_PlayerWins[4];
    int                 m_CurrentPlayerNum;

    GAME_ID             m_CurrentGameID;
};