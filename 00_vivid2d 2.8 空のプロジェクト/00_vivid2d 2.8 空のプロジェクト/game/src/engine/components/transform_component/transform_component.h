#pragma once
#include "../../core/component/component.h"
#include "../../mathematics/mathematics.h" // CTransform, CMatrix など、あなたのプロジェクトの型に合わせてください
#include "../../utility/transform/transform.h"

class TransformComponent : public IComponent
{
private:
    // あなたのプロジェクトに既存の、座標・回転・スケールをまとめた構造体（CTransformなど）をそのまま使います。
    CTransform m_Transform;

    // 最適化のためのデータ
    mutable CMatrix m_worldMatrix;
    mutable bool    m_isDirty;

public:
    // --- コンストラクタ ---
    TransformComponent();
    ~TransformComponent() override = default;

    // --- 更新処理 ---
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

    // 現在位置から、指定されたオフセット分だけ移動させる
    void Translate(const CVector3& offset);
    // --- 行列取得 ---
    const CMatrix& GetWorldMatrix() const;

private:
    // --- 内部処理 ---
    void RecalculateWorldMatrix() const;
};