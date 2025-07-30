#include "game_object.h"
#include "../../components/transform_component/transform_component.h"
#include <engine/components/model_component/model_component.h>
#include <game/components/player_component/player_component.h>
#include <engine/components/collider_component/mesh_collider_component/mesh_collider_component.h>

CGameObject::CGameObject()
    : m_IsActive(true)
	, m_ID(OBJECT_ID::NONE)
	, m_Tag(GAME_OBJECT_TAG::UNTAGGED)
	, m_Category(FACTION_CATEGORY::NEUTRAL)
	, m_Components()

{
    //座標は必ず持たせる
    AddComponent<TransformComponent>();
}

CGameObject::~CGameObject()
{
    // マップの各要素（各コンポーネント型）に対してループ
    for (auto const& pair : m_Components)
    {
        // ベクターの中の各コンポーネントインスタンスに対してループ
        for (auto& component : pair.second)
        {
            component->OnDetach(this);
        }
    }
}

void CGameObject::Initialize()
{
    // GameObject 全体の初期化ロジック。
    // 各コンポーネントの OnAttach は AddComponent() で呼び出される。
    // ここでは、GameObject 自体が持つ初期化処理を記述する。
    // 必要であれば、アタッチされている全てのコンポーネントのInitializeメソッドを呼び出すこともできるが、
    // OnAttach で済ませられる場合は不要。
}

void CGameObject::Update(float delta_time)
{
    if (!m_IsActive)
    {
        return;
    }

    // アタッチされている全てのコンポーネントの Update を呼び出す
    // これはシンプルな実装であり、将来的にはシステムによる更新モデルに移行することを検討する
    for (auto const& pair : m_Components)
    {
        for (auto& component : pair.second)
        {
            component->Update(delta_time, this); // GameObject* this を渡す

        }
    }
}

void CGameObject::Draw() 
{
    if (!m_IsActive)
    {
        return;
    }
    // 描画関連のコンポーネントがあれば、そのDrawメソッドを呼び出すなど
    if (auto modelComp = GetComponent<ModelComponent>()) { modelComp->Draw(this); }
}

void CGameObject::Finalize()
{
    // GameObject 全体の終了処理。
    // コンポーネントの OnDetach はデストラクタで呼ばれるため、ここでは追加の処理を記述
}