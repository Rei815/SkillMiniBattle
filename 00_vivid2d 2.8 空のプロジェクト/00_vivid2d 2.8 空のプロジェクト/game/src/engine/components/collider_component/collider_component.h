#pragma once
#include "../../core/component/component.h"
#include "../../mathematics/mathematics.h"

// 全ての当たり判定コンポーネントの親クラス
class ColliderComponent : public IComponent
{
public:
    ColliderComponent() = default;
    virtual ~ColliderComponent() = default;

    /**
     * @brief 指定されたラインとの当たり判定をチェックします。
     * @param startPos ラインの開始座標
     * @param endPos ラインの終了座標
     * @param out_hitPosition [out] 衝突した位置を格納する変数
     * @return 衝突した場合は true
     */
    virtual bool CheckHitLine(
        const CVector3& startPos,
        const CVector3& endPos,
        CVector3& out_hitPosition) const = 0; // = 0 で純粋仮想関数

    /*
     * @brief 当たり判定が有効かどうかを設定します。
     * @param isEnabled 有効にする場合はtrue
     */
    void SetEnabled(bool isEnabled);

    /*
     * @brief 当たり判定が現在有効かどうかを取得します。
     * @return 有効な場合はtrue
     */
    bool IsEnabled() const;
protected:
    // 当たり判定の有効/無効フラグ
    bool m_IsEnabled;
};