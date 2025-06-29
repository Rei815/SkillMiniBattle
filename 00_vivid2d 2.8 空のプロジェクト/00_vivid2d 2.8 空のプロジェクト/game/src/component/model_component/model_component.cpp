#include "model_component.h"
#include "../../game_manager/game_object/model/model.h" // CModel�N���X�̎���
#include "..\transform_component\transform_component.h"
#include "..\..\game_manager\game_object\game_object.h"
ModelComponent::ModelComponent(MODEL_ID id)
{
    //MODEL_ID���烂�f���𐶐�
    m_Model = std::make_shared<CModel>(id);
}

void ModelComponent::OnAttach(CGameObject* owner)
{
    m_Owner = owner;
}

void ModelComponent::Draw()
{
    if (!m_Owner || !m_Model)
    {
        return;
    }

    auto transform_comp = m_Owner->GetComponent<TransformComponent>();
    if (!transform_comp)
    {
        return;
    }

    const CMatrix& worldMatrix = transform_comp->GetWorldMatrix();
    int modelHandle = m_Model->GetHandle(); // �n���h������x�ϐ��ɓ����ƕ�����₷��

    MV1SetMatrix(modelHandle, worldMatrix);
    MV1DrawModel(modelHandle);

}

int ModelComponent::GetModelHandle() const
{
    if (m_Model)
    {
        return m_Model->GetHandle();
    }
    return VIVID_DX_ERROR; // �G���[�P�[�X
}