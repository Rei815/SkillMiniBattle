#include "model_component.h"
#include "../transform_component/transform_component.h"
#include "../../managers/model_manager/model_manager.h" // ModelManagerを使う
#include "../../core/game_object/game_object.h"

ModelComponent::ModelComponent(MODEL_ID id, bool IsDuplicate)
    : m_ModelHandle(-1)
    , m_Alpha(1.0f) 
    , m_IsDuplicated(IsDuplicate)// ハンドルを-1で、透明度を1.0で初期化
{
    // ModelManagerから、元となる共有モデルのハンドルを取得
    int sourceHandle = CModelManager::GetInstance().GetModelHandle(id);
    if (sourceHandle == -1) return;

    if (m_IsDuplicated)
    {
        // ★複製フラグがtrueなら、モデルを複製してそのハンドルを保持
        m_ModelHandle = MV1DuplicateModel(sourceHandle);
    }
    else
    {
        // ★フラグがfalseなら、今まで通り共有ハンドルを保持
        m_ModelHandle = sourceHandle;
    }
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

    // 透明度を設定
    DxLib::MV1SetOpacityRate(m_ModelHandle, m_Alpha);

    // 行列を設定して描画
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

    // 変換処理は不要になり、受け取ったcolorをそのまま渡すだけ！
    DxLib::MV1SetMaterialDifColor(m_ModelHandle, material_index, color);
}
COLOR_F ModelComponent::GetMaterialColor(int material_index)
{
    return DxLib::MV1GetMaterialDifColor(m_ModelHandle, material_index);
}
void ModelComponent::SetAlpha(float alpha)
{
    // コンポーネントが自身の状態として透明度を保持
    m_Alpha = alpha;
}