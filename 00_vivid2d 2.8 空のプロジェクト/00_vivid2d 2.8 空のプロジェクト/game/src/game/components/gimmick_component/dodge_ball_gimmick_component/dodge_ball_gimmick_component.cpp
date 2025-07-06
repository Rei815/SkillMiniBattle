#include "dodge_ball_gimmick_component.h"
#include "dodge_ball_gimmick/dodge_ball_gimmick.h" // 元のクラスのヘッダー

DodgeBallGimmickComponent::DodgeBallGimmickComponent()
{
    // コンストラクタで、元のロジッククラスを生成
    m_GimmickLogic = std::make_unique<CDodgeBallGimmick>();
}

DodgeBallGimmickComponent::~DodgeBallGimmickComponent() = default;

void DodgeBallGimmickComponent::OnAttach(CGameObject* owner)
{
    // 元のクラスに、自分が誰にアタッチされたか教える
    m_GimmickLogic->Initialize(owner);
}

void DodgeBallGimmickComponent::Update(float delta_time, CGameObject* owner)
{
    // 毎フレーム、元のクラスのUpdateを呼び出すだけ
    m_GimmickLogic->Update();
}

void DodgeBallGimmickComponent::SetOperationFlag(bool flag)
{
    m_GimmickLogic->SetOperationFlag(flag);
}

CANNON_STATE DodgeBallGimmickComponent::GetNowState()
{
    return m_GimmickLogic->GetNowState();
}

bool DodgeBallGimmickComponent::GetShotFlag()
{
    return m_GimmickLogic->GetShotFlag();
}