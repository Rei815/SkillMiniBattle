#include "daruma_fall_down_gimmick_component.h"
#include "daruma_fall_down_gimmick/daruma_fall_down_gimmick.h" // 元のクラスのヘッダー

DarumaFallDownGimmickComponent::DarumaFallDownGimmickComponent()
{
    // コンストラクタで、元のロジッククラスを生成
    m_GimmickLogic = std::make_unique<CDarumaFallDownGimmick>();
}

DarumaFallDownGimmickComponent::~DarumaFallDownGimmickComponent() = default;

void DarumaFallDownGimmickComponent::OnAttach(CGameObject* owner)
{
    // 元のクラスに、自分が誰にアタッチされたか教える
    m_GimmickLogic->Initialize(owner);
}

void DarumaFallDownGimmickComponent::Update(float delta_time, CGameObject* owner)
{
    // 毎フレーム、元のクラスのUpdateを呼び出すだけ
    m_GimmickLogic->Update();
}

void DarumaFallDownGimmickComponent::OgreControlTurn()
{
	// 元のクラスのメソッドを呼び出す
	m_GimmickLogic->OgreControlTurn();
}
