#pragma once
#include "../collider_component.h"
class CGameObject;
class MeshColliderComponent : public ColliderComponent
{
public:

	/*!
	 *  @brief      コンストラクタ
	 */
    MeshColliderComponent();

    /*!
	 *  @brief      デストラクタ
     */
    ~MeshColliderComponent() = default;

    /*!
	 *  @brief      アタッチ時の初期化
     * 
	 *  @param[in]  owner          コンポーネントをアタッチしたオーナーオブジェクト
     */
    void OnAttach(CGameObject* owner) override;

    /*!
	 *  @brief      更新
     * 
	 *  @param[in]  delta_time     前フレームからの経過時間
	 *  @param[in]  owner          コンポーネントをアタッチしたオーナーオブジェクト
     */
	void Update(float delta_time, CGameObject* owner) override;

    /*!
	 *  @brief      線分と自分が当たっているかをチェック
     * 
	 *  @param[in] startPos    線分の始点
	 *  @param[in] endPos      線分の終点
	 *  @param[out] out_result 当たり判定の結果を格納
     */
    bool CheckHitLine(const CVector3& startPos, const CVector3& endPos, CollisionResult& out_result = CollisionResult()) const override;

    /*!
	 *  @brief	  球と自分が当たっているかをチェック
     *  
	 *  @param[in] center        球の中心
	 *  @param[in] radius        球の半径
	 *  @param[out] out_result 当たり判定の結果を格納
     */
    bool CheckHitSphere(const CVector3& center, float radius, CollisionResult& out_result) const override;

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
    bool CheckHitCapsule(const CVector3& posA, const CVector3& posB, float radius, CVector3& out_hitPosition) const override;

private:

	int m_ModelHandle; //!< モデルハンドル
};