#pragma once
#include "../../core/component/component.h"
#include "../../mathematics/mathematics.h"
#include "../../utility/transform/transform.h"

class TransformComponent : public IComponent
{
public:

    /*!
	 *  @brief      コンストラクタ
     */
    TransformComponent();

    /*!
     *  @brief      デストラクタ
     */
    ~TransformComponent() override = default;

    /*!
	 *  @brief      更新
     * 
	 *  @param[in] delta_time 前フレームからの経過時間
	 *  @param[in] owner      コンポーネントをアタッチしたオーナーオブジェクト
     */
    void Update(float delta_time, CGameObject* owner) override {}

    // --- ゲッター / セッター ---
    const CTransform& GetTransform() const { return m_Transform; }
    void SetTransform(const CTransform& transform);

    const CVector3& GetPosition() const { return m_Transform.position; }
    const CVector3& GetRotation() const { return m_Transform.rotation; }
    const CVector3& GetScale() const { return m_Transform.scale; }
    void SetPosition(const CVector3& position);
    void SetRotation(const CVector3& euler_angles);
    void SetScale(const CVector3& scale);
    void SetScale(float scale);

    /*!
	 *  @brief      オフセットを加えて位置を変更
     *  
	 *  @param[in] offset 位置を変更するためのオフセット
     */
    void Translate(const CVector3& offset);

	/*!
	 *  @brief      ワールド行列を取得
	 *
	 *  @return     ワールド行列
	 */
    const CMatrix&  GetWorldMatrix() const;

    /*!
	 *  @brief      ワールド座標系での長さを取得
     */
    float GetLength() const;
private:
    // --- 内部処理 ---
    void RecalculateWorldMatrix() const;

private:
	CTransform m_Transform;         //!< トランスフォーム

	mutable CMatrix m_WorldMatrix;  //!< ワールド行列
	mutable bool    m_IsDirty;      //!< ワールド行列が再計算が必要かどうかのフラグ
};