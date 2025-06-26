#include "model_component.h"
#include "../../game_manager/game_object/model/model.h" // CModelクラスの実装
#include "..\transform_component\transform_component.h"
#include "..\..\game_manager\game_object\game_object.h"
// ★変更点：コンストラクタの実装
ModelComponent::ModelComponent(MODEL_ID id)
{
    // あなたのプロジェクトの作法に合わせて、MODEL_IDからモデルを生成
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
    int modelHandle = m_model->GetHandle(); // ハンドルを一度変数に入れると分かりやすい

    MV1SetMatrix(modelHandle, worldMatrix);
    MV1DrawModel(modelHandle);
}