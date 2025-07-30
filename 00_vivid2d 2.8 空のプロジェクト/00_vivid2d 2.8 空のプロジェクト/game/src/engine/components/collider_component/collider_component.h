#pragma once
#include "../../core/component/component.h"
#include "../../mathematics/mathematics.h"
#include "collision_result.h"
class ColliderComponent : public IComponent
{
public:
    ColliderComponent();
    virtual ~ColliderComponent() = default;

    /*!
     * @brief 指定されたラインとの当たり判定をチェック
     * 
     * @param[in] startPos ラインの開始座標
     * @param[in] endPos ラインの終了座標
     * @param[out] out_hitPosition 衝突した位置を格納
     * 
     * @return 衝突した場合は true
     */
    virtual bool CheckHitLine( const CVector3& startPos, const CVector3& endPos, CollisionResult& out_result = CollisionResult()) const = 0;

    /*!
	 *  @brief 指定された位置と半径の球との当たり判定をチェック
     * 
	 *  @param[in] center 球の中心座標
	 *  @param[in] radius 球の半径
	 *  @param[out] out_result 衝突結果を格納
     */
    virtual bool CheckHitSphere(const CVector3& center, float radius, CollisionResult& out_result) const = 0;

	/*!
	 * @brief 指定された位置と半径の球との当たり判定をチェック
	 *
	 * @param[in] posA カプセルの一端の位置
	 * @param[in] posB カプセルのもう一端の位置
	 * @param[in] radius カプセルの半径
	 * @param[out] out_hitPosition 衝突した位置を格納
	 *
	 * @return 衝突した場合は true
	 */
    virtual bool CheckHitCapsule(const CVector3& posA, const CVector3& posB, float radius, CVector3& out_hitPosition) const = 0;

    /*!
     * @brief 当たり判定が有効かどうかを設定
     * 
	 * @param[in] isEnabled 有効かどうかのフラグ
     */
    void SetEnabled(bool isEnabled);

    /*!
     * @brief 当たり判定が現在有効かどうかを取得
     * 
	 * @return true : 有効, false : 無効
     */
    bool IsEnabled() const;
protected:
	bool m_IsEnabled;   //!< 当たり判定が有効かどうか
};