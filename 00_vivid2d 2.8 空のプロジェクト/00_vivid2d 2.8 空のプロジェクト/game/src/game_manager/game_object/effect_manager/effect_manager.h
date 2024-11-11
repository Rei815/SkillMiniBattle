#pragma once

#include <list>
#include "../../../mathematics/mathematics.h"

#include "effect\effect_id.h"
#include "effect/effect.h"
using namespace std;

class IEffect;

/*!
 *  @class      CEffectManager
 *
 *  @brief      エフェクト管理クラス
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
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
     */
    IEffect*        Create(EFFECT_ID id, const CVector3& pos);


    /*!
     *  @brief      エフェクト生成
     *
     *  @param[in]  id          エフェクトID
     *  @param[in]  pos         位置
     *  @param[in]  scale       拡大率
     */
    IEffect*        Create(EFFECT_ID id, const CVector3& pos, const float scale);


    /*!
     *  @brief      エフェクト生成
     *
     *  @param[in]  id          エフェクトID
     *  @param[in]  pos         位置
     *  @param[in]  rot         回転
     */
    IEffect*        Create(EFFECT_ID id, const CVector3& pos, const CVector3& rot);


    /*!
     *  @brief      エフェクト生成
     *
     *  @param[in]  id          エフェクトID
     *  @param[in]  pos         位置
     *  @param[in]  rot         回転
     *  @param[in]  scale       拡大率
     */
    IEffect*        Create(EFFECT_ID id, const CVector3& pos, const CVector3& rot, const float scale);


    /*!
     *  @brief      エフェクト生成
     *
     *  @param[in]  id          エフェクトID
     *  @param[in]  pos         位置
     *  @param[in]  color       色
     *  @param[in]  rotation    回転値
     */
    IEffect*        Create(EFFECT_ID id, const vivid::Vector2& pos, unsigned int color, float rotation);

    /*!
     *  @brief      親の位置設定
     *
     *  @param[in]  effectID        エフェクトid
     *  @param[in]  parentPos       親の位置
     */
    void        SetParentPosition(EFFECT_ID effectID,CVector3& parentPos);

private:
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
    using EFFECT_LIST = list<IEffect*>;

    EFFECT_LIST     m_EffectList;   //!< エフェクトリスト
};
