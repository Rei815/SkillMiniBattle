#pragma once
#include "../../core/component/component.h"
#include "../../managers/model_manager/model_id.h" // MODEL_ID ���g������
#include "DxLib.h"
// �O���錾
class TransformComponent;

class ModelComponent : public IComponent
{
private:
    int m_ModelHandle; // CModel��shared_ptr�̑���ɁA�n���h��(int)�𒼐ڕێ�
    float m_Alpha;     // �����x

public:
    ModelComponent(MODEL_ID id = MODEL_ID::MAX);
    ~ModelComponent() override = default;
    // --- �X�V���� ---
    void Update(float delta_time, CGameObject* owner) override {}
    void Draw(const CGameObject* owner) const;

    // ���̃R���|�[�l���g���ێ����Ă���n���h����Ԃ�
    int GetHandle() const;
    void SetMaterialColor(int material_index, const DxLib::COLOR_F& color);
    DxLib::COLOR_F GetMaterialColor(int material_index);
    void SetAlpha(float alpha);
};