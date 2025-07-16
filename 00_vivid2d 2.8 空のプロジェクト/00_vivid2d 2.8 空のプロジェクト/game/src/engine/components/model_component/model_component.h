#pragma once
#include "../../core/component/component.h"
#include "../../managers/model_manager/model_id.h" // MODEL_ID を使うため
#include "DxLib.h"
// 前方宣言
class TransformComponent;

class ModelComponent : public IComponent
{

public:
    ModelComponent(MODEL_ID id = MODEL_ID::MAX, bool IsDuplicate = false);
    ~ModelComponent() override = default;
    void OnDetach(CGameObject* owner) override;
    // --- 更新処理 ---
    void Update(float delta_time, CGameObject* owner) override {}
    void Draw(const CGameObject* owner) const;

    void SetModelHandle(int handle);
    // このコンポーネントが保持しているハンドルを返す
    int GetHandle() const;
    void SetMaterialColor(int material_index, const DxLib::COLOR_F& color);
    DxLib::COLOR_F GetMaterialColor(int material_index);
    void SetAlpha(float alpha);
private:
    int m_ModelHandle;
    float m_Alpha;     // 透明度
    bool m_IsDuplicated;
};