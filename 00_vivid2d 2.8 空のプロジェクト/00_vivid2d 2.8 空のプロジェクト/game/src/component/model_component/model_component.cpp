#include "model_component.h"
#include "../../game_manager/game_object/model/model.h" // CModelクラスの実装
#include "..\transform_component\transform_component.h"
#include "..\..\game_manager\game_object\game_object.h"
ModelComponent::ModelComponent(MODEL_ID id)
{
    //MODEL_IDからモデルを生成
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
    int modelHandle = m_Model->GetHandle(); // ハンドルを一度変数に入れると分かりやすい

    MV1SetMatrix(modelHandle, worldMatrix);
    MV1DrawModel(modelHandle);

}

int ModelComponent::GetModelHandle() const
{
    if (m_Model)
    {
        return m_Model->GetHandle();
    }
    return VIVID_DX_ERROR; // エラーケース
}