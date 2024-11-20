#pragma once

#include "vivid.h"
#include <list>
#include "../unit_manager/unit/player/player.h"

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
    using RANKING_LIST = std::list<CPlayer*>;

    RANKING_LIST           m_OverallRankingList;             //!< 全体のランキングリスト

};