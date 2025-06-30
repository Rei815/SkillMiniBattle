#include "model_component.h"
#include "../../game_object/game_object.h"
#include "../transform_component/transform_component.h"
#include "../../managers/model_manager/model_manager.h" // ModelManager���g��
#include "../../core/game_object/game_object.h"

ModelComponent::ModelComponent(MODEL_ID id)
    : m_ModelHandle(-1), m_Alpha(1.0f) // �n���h����-1�ŁA�����x��1.0�ŏ�����
{
    // CModel��new����̂ł͂Ȃ��AModelManager����n���h�����擾���ă����o�ϐ��ɕێ�����
    m_ModelHandle = CModelManager::GetInstance().GetModelHandle(id);
}

void ModelComponent::Draw(const CGameObject* owner) const
{
    if (m_ModelHandle == -1 || !owner)
    {
        return;
    }

    auto transform_comp = owner->GetComponent<TransformComponent>();
    if (!transform_comp)
    {
        return;
    }

    // �����x��ݒ�
    DxLib::MV1SetOpacityRate(m_ModelHandle, m_Alpha);

    // �s���ݒ肵�ĕ`��
    const CMatrix& worldMatrix = transform_comp->GetWorldMatrix();
    DxLib::MV1SetMatrix(m_ModelHandle, worldMatrix);
    DxLib::MV1DrawModel(m_ModelHandle);
}

int ModelComponent::GetHandle() const
{
    return m_ModelHandle;
}

void ModelComponent::SetAlpha(float alpha)
{
    // �R���|�[�l���g�����g�̏�ԂƂ��ē����x��ێ�
    m_Alpha = alpha;
}