#pragma once

#include "vivid.h"
#include <list>
#include "animation/animation_id.h"
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

    /*!
     *  @brief      描画
     */
    void        Draw(void);

    /*!
     *  @brief      解放
     */
    void        Finalize(void);

    ///*!
    // *  @brief        アニメーション生成
    // *
    // *  @param[in]  id                  ギミックID
    // */
    void        Create(ANIMATION_ID id);

    ///*!
    // *  @brief      ギミック生成
    // *
    // *  @param[in]  id                  ギミックID
    // *  @param[in]  object              オブジェクトのポインタ
    // *  @param[in]  time                遅延時間
    // */
    //void        Create(GIMMICK_ID id, IObject* object, float time);

    /*!
     *  @brief      ギミックリスト型
     */
    //using ANIMATION_LIST = std::list<IAnim*>;

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

    //ANIMATION_LIST             m_AnimationList;             //!< アニメーションリスト
};