#pragma once
#include "../component.h"
#include "../../mathematics/mathematics.h" // CTransform, CMatrix など、あなたのプロジェクトの型に合わせてください
#include "../../utility/transform/transform.h"

class TransformComponent : public IComponent
{
private:
    // あなたのプロジェクトに既存の、座標・回転・スケールをまとめた構造体（CTransformなど）をそのまま使います。
    CTransform m_transform;

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
    const CTransform& GetTransform() const { return m_transform; }
    void SetTransform(const CTransform& transform);

    // より使いやすくするための便利なメソッド
    void SetPosition(const CVector3& position);
    void SetRotation(const CVector3& euler_angles);
    void SetScale(const CVector3& scale);

    // --- 行列取得 ---
    const CMatrix& GetWorldMatrix() const;

private:
    // --- 内部処理 ---
    void RecalculateWorldMatrix() const;
};