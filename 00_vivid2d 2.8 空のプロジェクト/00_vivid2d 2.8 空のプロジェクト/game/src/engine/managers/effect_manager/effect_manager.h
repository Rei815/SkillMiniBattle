#pragma once

#include <list>
#include "../../../mathematics/mathematics.h"

#include "effect\effect_id.h"
#include "effect/effect.h"
using namespace std;

class IEffect;

class CEffectManager
{
public:
    /*!
     *  @brief      インスタンスの取得
     *
     *  @return     インスタンス
     */
    static CEffectManager& GetInstance(void);

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
     *  @brief      エフェクト生成
     *
     *  @param[in]  id          エフェクトID
     *  @param[in]  pos         位置
     *  @param[in]  scale       拡大率
     */
    std::shared_ptr<IEffect>        Create(EFFECT_ID id, const CVector3& pos = CVector3::ZERO, float scale = 1.0f);

    /*!
     *  @brief      エフェクト生成
     *
     *  @param[in]  id          エフェクトID
     *  @param[in]  pos         位置
     *  @param[in]  rot         回転
     */
    std::shared_ptr<IEffect>        Create(EFFECT_ID id, const CVector3& pos, const CVector3& rot);


    /*!
     *  @brief      エフェクト生成
     *
     *  @param[in]  id          エフェクトID
     *  @param[in]  pos         位置
     *  @param[in]  rot         回転
     *  @param[in]  scale       拡大率
     */
    std::shared_ptr<IEffect>        Create(EFFECT_ID id, const CVector3& pos, const CVector3& rot, const float scale);

    /*!
     *  @brief      エフェクト生成
     *
     *  @param[in]  id          エフェクトID
     *  @param[in]  pos         位置
     *  @param[in]  rot         回転
     *  @param[in]  scale       拡大率
     */
    std::shared_ptr<IEffect>        Create(EFFECT_ID id, const CVector3& pos, const CVector3& rot, const CVector3& scale);

    /*!
     *  @brief      すべてのエフェクトを一時停止
     */
    void            PauseAllEffect();

    /*!
     *  @brief      すべてのエフェクトを再開
     */
    void            ResumeAllEffect();

private:

    std::shared_ptr<IEffect> CreateClass(EFFECT_ID id);
    /*!
     *  @brief      コンストラクタ
     */
    CEffectManager(void);

    /*!
     *  @brief      コピーコンストラクタ
     *
     *  @param[in]  rhs     オブジェクト
     */
    CEffectManager(const CEffectManager& rhs);

    /*!
     *  @brief      デストラクタ
     */
    ~CEffectManager(void);

    /*!
     *  @brief      代入演算子
     *
     *  @param[in]  rhs 代入オブジェクト
     *
     *  @return     自身のオブジェクト
     */
    CEffectManager& operator=(const CEffectManager& rhs);

    /*!
     *  @brief      エフェクトリスト型
     */
    using EFFECT_LIST = list<std::shared_ptr<IEffect>>;

    EFFECT_LIST     m_EffectList;   //!< エフェクトリスト
};
