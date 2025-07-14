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
	OGRE_STATE state = m_GimmickLogic->GetOgreState();
    switch (state)
    {
    case OGRE_STATE::WAIT:
        if(m_GimmickLogic->GetTurnState() != TURN_TYPE::FEINT)
            m_State = GIMMICK_STATE::PLAY;
        break;
    case OGRE_STATE::PLAY:  m_State = GIMMICK_STATE::WAIT; break;
    case OGRE_STATE::READY: m_State = GIMMICK_STATE::WAIT; break;
    case OGRE_STATE::FINISH:m_State = GIMMICK_STATE::WAIT; break;

    }
}

void DarumaFallDownGimmickComponent::OgreControlTurn()
{
	// 元のクラスのメソッドを呼び出す
	m_GimmickLogic->OgreControlTurn();
}
