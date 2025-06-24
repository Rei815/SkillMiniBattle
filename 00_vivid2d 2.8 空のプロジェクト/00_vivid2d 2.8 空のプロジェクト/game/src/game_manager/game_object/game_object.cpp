#include "game_object.h"

CGameObject::CGameObject()
    : m_Position(0.0f, 0.0f, 0.0f),
    m_Transform(),
    m_IsActive(true)
{
    // 必要であれば、ここに共通の初期化処理を記述
}

CGameObject::~CGameObject()
{
    // デストラクタで、アタッチされているコンポーネントの OnDetach を呼び出す
    // マップは自動的に解放される
    for (auto const& pair : m_Components)
    {
        // pair.second は shared_ptr なので、null チェックは不要
        pair.second.front()->OnDetach(this);
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
        pair.second.front()->Update(delta_time, this); // GameObject* this を渡す
    }
}

void CGameObject::Draw() 
{
    if (!m_IsActive)
    {
        return;
    }
    // 描画関連のコンポーネントがあれば、そのDrawメソッドを呼び出すなど
    // 例: if (auto renderComp = GetComponent<RenderComponent>()) { renderComp->Draw(this); }
}

void CGameObject::Finalize()
{
    // GameObject 全体の終了処理。
    // コンポーネントの OnDetach はデストラクタで呼ばれるため、ここでは追加の処理を記述
}