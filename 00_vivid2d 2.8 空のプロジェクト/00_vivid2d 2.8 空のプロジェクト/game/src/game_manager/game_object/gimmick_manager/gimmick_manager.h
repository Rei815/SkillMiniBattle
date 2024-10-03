#pragma once

#include "vivid.h"
#include <list>
#include "gimmick/gimmick.h"
class CGimmickManager
{
public:
    /*!
     *  @brief      インスタンスの取得
     *
     *  @return     インスタンス
     */
    static CGimmickManager& GetInstance(void);

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
     *  @brief      ギミック生成
     *
     *  @param[in]  id              ギミックのID
     */
    void        Create(GIMMICK_ID id);

private:
    /*!
     *  @brief      コンストラクタ
     */
    CGimmickManager(void);

    /*!
     *  @brief      コピーコンストラクタ
     *
     *  @param[in]  rhs     オブジェクト
     */
    CGimmickManager(const CGimmickManager& rhs);

    /*!
     *  @brief      デストラクタ
     */
    ~CGimmickManager(void);

    /*!
     *  @brief      代入演算子
     *
     *  @param[in]  rhs 代入オブジェクト
     *
     *  @return     自身のオブジェクト
     */
    CGimmickManager& operator=(const CGimmickManager& rhs);

    /*!
     *  @brief      ギミックリスト型
     */
    using GIMMICK_LIST = std::list<IGimmick*>;

    GIMMICK_LIST             m_GimmickList;             //!< UIリスト
};