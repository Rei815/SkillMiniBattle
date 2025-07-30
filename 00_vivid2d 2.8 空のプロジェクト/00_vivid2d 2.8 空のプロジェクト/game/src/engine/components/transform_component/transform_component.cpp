#include "transform_component.h"

TransformComponent::TransformComponent()
    : m_Transform()     // デフォルトコンストラクタで初期化
    , m_WorldMatrix()   // デフォルトコンストラクタで初期化
    , m_IsDirty(true)   // 最初は必ず再計算が必要
{
}

void TransformComponent::SetTransform(const CTransform& transform)
{
    m_Transform = transform;
    m_IsDirty = true; // データが変更されたのでフラグを立てる
}

void TransformComponent::SetPosition(const CVector3& position)
{
    m_Transform.position = position;
    m_IsDirty = true;
}

void TransformComponent::SetRotation(const CVector3& euler_angles)
{
    m_Transform.rotation = euler_angles;
    m_IsDirty = true;
}

void TransformComponent::SetScale(const CVector3& scale)
{
    m_Transform.scale = scale;
    m_IsDirty = true;
}

void TransformComponent::SetScale(float scale)
{
    m_Transform.scale.x = scale;
    m_Transform.scale.y = scale;
    m_Transform.scale.z = scale;
    m_IsDirty = true;

}

void TransformComponent::Translate(const CVector3& offset)
{
    // 現在位置に、オフセット（移動量）を加算する
    m_Transform.position += offset;

    // 位置が変更されたので、忘れずにダーティフラグを立てる
    m_IsDirty = true;
}
const CMatrix& TransformComponent::GetWorldMatrix() const
{
    if (m_IsDirty)
    {
        RecalculateWorldMatrix();
    }
    return m_WorldMatrix;
}

float TransformComponent::GetLength() const
{
    return CVector3::Length(m_Transform.position);
}

void TransformComponent::RecalculateWorldMatrix() const
{
    // あなたのCMatrixクラスの静的メソッドを使って、各行列を生成します。
    CMatrix scaleMat = CMatrix::Scale(m_Transform.scale);
    CMatrix rotationMat = CMatrix::Rotate(m_Transform.rotation);
    CMatrix translateMat = CMatrix::Translate(m_Transform.position);

    // ワールド行列を計算してキャッシュします。
    m_WorldMatrix = scaleMat * rotationMat * translateMat;

    // 再計算が完了したので、フラグを降ろします。
    m_IsDirty = false;
}