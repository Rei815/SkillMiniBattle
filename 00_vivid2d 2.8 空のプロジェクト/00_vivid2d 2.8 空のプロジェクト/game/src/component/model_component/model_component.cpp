#include "model_component.h"
#include "../../game_manager/game_object/model/model.h" // CModel�N���X�̎���
#include "..\transform_component\transform_component.h"
#include "..\..\game_manager\game_object\game_object.h"
// ���ύX�_�F�R���X�g���N�^�̎���
ModelComponent::ModelComponent(MODEL_ID id)
{
    // ���Ȃ��̃v���W�F�N�g�̍�@�ɍ��킹�āAMODEL_ID���烂�f���𐶐�
    m_model = std::make_shared<CModel>(id);
}

void ModelComponent::OnAttach(CGameObject* owner)
{
    m_owner = owner;
}

void ModelComponent::Draw()
{
    if (!m_owner || !m_model)
    {
        return;
    }

    auto transform_comp = m_owner->GetComponent<TransformComponent>();
    if (!transform_comp)
    {
        return;
    }

    const CMatrix& worldMatrix = transform_comp->GetWorldMatrix();
    int modelHandle = m_model->GetHandle(); // �n���h������x�ϐ��ɓ����ƕ�����₷��

    MV1SetMatrix(modelHandle, worldMatrix);
    MV1DrawModel(modelHandle);
}