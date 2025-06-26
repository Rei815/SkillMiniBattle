#include "transform_component.h"

TransformComponent::TransformComponent()
    : m_transform()     // デフォルトコンストラクタで初期化
    , m_worldMatrix()   // デフォルトコンストラクタで初期化
    , m_isDirty(true)   // 最初は必ず再計算が必要
{
}

void TransformComponent::SetTransform(const CTransform& transform)
{
    m_transform = transform;
    m_isDirty = true; // データが変更されたのでフラグを立てる
}

void TransformComponent::SetPosition(const CVector3& position)
{
    m_transform.position = position;
    m_isDirty = true;
}

void TransformComponent::SetRotation(const CVector3& euler_angles)
{
    m_transform.rotation = euler_angles; // CTransform内の回転メンバに代入
    m_isDirty = true;
}

void TransformComponent::SetScale(const CVector3& scale)
{
    m_transform.scale = scale;
    m_isDirty = true;
}

const CMatrix& TransformComponent::GetWorldMatrix() const
{
    if (m_isDirty)
    {
        RecalculateWorldMatrix();
    }
    return m_worldMatrix;
}

// ★★★ ここがあなたのプロジェクト専用の最終版です ★★★
void TransformComponent::RecalculateWorldMatrix() const
{
    // あなたのCMatrixクラスの静的メソッドを使って、各行列を生成します。
    CMatrix scaleMat = CMatrix::Scale(m_transform.scale);
    CMatrix rotationMat = CMatrix::Rotate(m_transform.rotation);
    CMatrix translateMat = CMatrix::Translate(m_transform.position);

    // ワールド行列を計算してキャッシュします。
    // (CMatrixクラスで演算子がオーバーロードされているので、このまま掛け算できますね)
    m_worldMatrix = scaleMat * rotationMat * translateMat;

    // 再計算が完了したので、フラグを降ろします。
    m_isDirty = false;
}