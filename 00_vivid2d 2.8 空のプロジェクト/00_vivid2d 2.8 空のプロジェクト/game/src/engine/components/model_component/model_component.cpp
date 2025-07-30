#include "model_component.h"
#include "../transform_component/transform_component.h"
#include "../../managers/model_manager/model_manager.h" // ModelManager���g��
#include "../../core/game_object/game_object.h"

ModelComponent::ModelComponent(MODEL_ID id, bool IsDuplicate)
    : m_ModelHandle(-1)
    , m_Alpha(1.0f) 
    , m_IsDuplicated(IsDuplicate)
{
    // ModelManager����A���ƂȂ鋤�L���f���̃n���h�����擾
    int sourceHandle = CModelManager::GetInstance().GetModelHandle(id);
    if (sourceHandle == -1) return;

    if (m_IsDuplicated)
    {
		// ���f���𕡐����āAm_ModelHandle�ɐݒ�
        m_ModelHandle = MV1DuplicateModel(sourceHandle);
    }
    else
    {
		// �������Ȃ��ꍇ�́A���̃��f���̃n���h�������̂܂܎g�p
        m_ModelHandle = sourceHandle;
    }
}

void ModelComponent::OnDetach(CGameObject* owner)
{
	if (m_ModelHandle != -1)
	{
		// ���f���n���h�����L���Ȃ�A���f�����폜
		if (m_IsDuplicated)
		{
			DxLib::MV1DeleteModel(m_ModelHandle);
		}
		m_ModelHandle = -1; // �n���h���𖳌��ɂ���
	}
}

void ModelComponent::Draw(const CGameObject* owner) const
{
	// �I�[�i�[��nullptr�܂��̓��f���n���h���������ȏꍇ�͉������Ȃ�
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

void ModelComponent::SetModelHandle(int handle)
{
    m_ModelHandle = handle;
}

int ModelComponent::GetHandle() const
{
    return m_ModelHandle;
}

void ModelComponent::SetMaterialColor(int material_index, const DxLib::COLOR_F& color)
{
    if (m_ModelHandle == -1) return;

    // �ϊ������͕s�v�ɂȂ�A�󂯎����color�����̂܂ܓn�������I
    DxLib::MV1SetMaterialDifColor(m_ModelHandle, material_index, color);
}
COLOR_F ModelComponent::GetMaterialColor(int material_index)
{
    return DxLib::MV1GetMaterialDifColor(m_ModelHandle, material_index);
}
void ModelComponent::SetAlpha(float alpha)
{
    // �R���|�[�l���g�����g�̏�ԂƂ��ē����x��ێ�
    m_Alpha = alpha;
}