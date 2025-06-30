#pragma once
#include "../../core/component/component.h"
#include "../../managers/model_manager/model_id.h" // MODEL_ID ���g������

// �O���錾
class TransformComponent;

class ModelComponent : public IComponent
{
private:
    int m_ModelHandle; // CModel��shared_ptr�̑���ɁA�n���h��(int)�𒼐ڕێ�
    float m_Alpha;     // �����x

public:
    ModelComponent(MODEL_ID id);
    ~ModelComponent() override = default;

    void Draw(const CGameObject* owner) const;

    // ���̃R���|�[�l���g���ێ����Ă���n���h����Ԃ�
    int GetHandle() const;

    void SetAlpha(float alpha);
};