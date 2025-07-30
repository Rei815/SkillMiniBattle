#include "transform_component.h"

TransformComponent::TransformComponent()
    : m_Transform()     // 各値をデフォルトで初期化
    , m_WorldMatrix()   // 単位行列で初期化
    , m_IsDirty(true)   // 生成直後は必ず一度ワールド行列を計算させるため、trueに設定
{
}

void TransformComponent::SetTransform(const CTransform& transform)
{
    m_Transform = transform;
    m_IsDirty = true; // Transformデータが変更されたため、再計算を要求する
}

void TransformComponent::SetPosition(const CVector3& position)
{
    m_Transform.position = position;
    m_IsDirty = true; // Transformデータが変更されたため、再計算を要求する
}

void TransformComponent::SetRotation(const CVector3& euler_angles)
{
    m_Transform.rotation = euler_angles;
    m_IsDirty = true; // Transformデータが変更されたため、再計算を要求する
}

void TransformComponent::SetScale(const CVector3& scale)
{
    m_Transform.scale = scale;
    m_IsDirty = true; // Transformデータが変更されたため、再計算を要求する
}

void TransformComponent::SetScale(float scale)
{
    m_Transform.scale = CVector3(scale, scale, scale);
    m_IsDirty = true; // Transformデータが変更されたため、再計算を要求する
}

void TransformComponent::Translate(const CVector3& offset)
{
    m_Transform.position += offset;
    m_IsDirty = true; // 位置が変更されたため、再計算を要求する
}

const CMatrix& TransformComponent::GetWorldMatrix() const
{
    // ダーティフラグが立っている場合（＝前回の取得から値が変更された場合）のみ再計算を実行
    if (m_IsDirty)
    {
        RecalculateWorldMatrix();
    }
    // 変更がなければ、キャッシュ済みの行列をそのまま返す
    return m_WorldMatrix;
}

float TransformComponent::GetLength() const
{
	// ワールド座標系での位置ベクトルの長さを計算して返す
    return CVector3::Length(m_Transform.position);
}

void TransformComponent::RecalculateWorldMatrix() const
{
    // 各Transform要素から行列を生成
    CMatrix scaleMat = CMatrix::Scale(m_Transform.scale);
    CMatrix rotationMat = CMatrix::Rotate(m_Transform.rotation);
    CMatrix translateMat = CMatrix::Translate(m_Transform.position);

    // ワールド行列を計算してキャッシュ
    m_WorldMatrix = scaleMat * rotationMat * translateMat;

    // 再計算が完了したので、フラグを降ろす。
    // これにより、次にGetWorldMatrixが呼ばれても値が変更されていなければ再計算は走らない。
    m_IsDirty = false;
}