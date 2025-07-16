#pragma once
#include "../../core/component/component.h"
#include "../../managers/model_manager/model_id.h" // MODEL_ID ���g������
#include "DxLib.h"
// �O���錾
class TransformComponent;

class ModelComponent : public IComponent
{

public:
    ModelComponent(MODEL_ID id = MODEL_ID::MAX, bool IsDuplicate = false);
    ~ModelComponent() override = default;
    void OnDetach(CGameObject* owner) override;
    // --- �X�V���� ---
    void Update(float delta_time, CGameObject* owner) override {}
    void Draw(const CGameObject* owner) const;

    void SetModelHandle(int handle);
    // ���̃R���|�[�l���g���ێ����Ă���n���h����Ԃ�
    int GetHandle() const;
    void SetMaterialColor(int material_index, const DxLib::COLOR_F& color);
    DxLib::COLOR_F GetMaterialColor(int material_index);
    void SetAlpha(float alpha);
private:
    int m_ModelHandle;
    float m_Alpha;     // �����x
    bool m_IsDuplicated;
};