#pragma once
#include "../../core/component/component.h"
#include "../../managers/model_manager/model_id.h" // MODEL_ID を使うため
#include "DxLib.h"
// 前方宣言
class TransformComponent;

class ModelComponent : public IComponent
{
private:
    int m_ModelHandle; // CModelのshared_ptrの代わりに、ハンドル(int)を直接保持
    float m_Alpha;     // 透明度

public:
    ModelComponent(MODEL_ID id);
    ~ModelComponent() override = default;
    // --- 更新処理 ---
    void Update(float delta_time, CGameObject* owner) override {}
    void Draw(const CGameObject* owner) const;

    // このコンポーネントが保持しているハンドルを返す
    int GetHandle() const;
    void SetMaterialColor(int material_index, const DxLib::COLOR_F& color);
    DxLib::COLOR_F GetMaterialColor(int material_index);
    void SetAlpha(float alpha);
};