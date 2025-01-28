#pragma once

#include "vivid.h"
#include <list>
#include "animation/animation_id.h"
#include "animation/animation.h"
class CAnimationManager
{
public:
    /*!
     *  @brief      インスタンスの取得
     *
     *  @return     インスタンス
     */
    static CAnimationManager& GetInstance(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(void);

    /*!
     *  @brief      更新
     */
    void        Update(void);

    ///*!
    // *  @brief      描画
    // */
    //void        Draw(void);

    /*!
     *  @brief      解放
     */
    void        Finalize(void);

    ///*!
    // *  @brief        アニメーション生成
    // *
    // *  @param[in]    id                  ギミックID
    // *  @return       アニメーション
    // */
    IAnimation*        Create(ANIMATION_ID id, void* object_pointer);

    /*!
     *  @brief      ギミックリスト型
     */
    using ANIMATION_LIST = std::list<IAnimation*>;

    /*!
     *  @brief      リスト取得
     *
     *  @return     アニメーションリスト
     */
    ANIMATION_LIST GetList();

private:
    /*!
     *  @brief      コンストラクタ
     */
    CAnimationManager(void);

    /*!
     *  @brief      コピーコンストラクタ
     *
     *  @param[in]  rhs     オブジェクト
     */
    CAnimationManager(const CAnimationManager& rhs);

    /*!
     *  @brief      デストラクタ
     */
    ~CAnimationManager(void);

    /*!
     *  @brief      代入演算子
     *
     *  @param[in]  rhs 代入オブジェクト
     *
     *  @return     自身のオブジェクト
     */
    CAnimationManager& operator=(const CAnimationManager& rhs);

    ANIMATION_LIST             m_AnimationList;             //!< アニメーションリスト
};