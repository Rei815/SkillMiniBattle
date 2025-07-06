#include "belt_conveyor_gimmick_componet.h"
#include "../../../../engine/core/game_object/game_object.h"
#include "belt_conveyor_gimmick/belt_conveyor_gimmick.h"
BeltConveyorGimmickComponent::BeltConveyorGimmickComponent()
{
    m_GimmickLogic = std::make_unique<CBeltConveyorGimmick>();
}

BeltConveyorGimmickComponent::~BeltConveyorGimmickComponent() = default;

void BeltConveyorGimmickComponent::OnAttach(CGameObject* owner)
{
    m_GimmickLogic->Initialize(owner);
}

void BeltConveyorGimmickComponent::Update(float delta_time, CGameObject* owner)
{
    m_GimmickLogic->Update(); // 毎フレーム、元のクラスのUpdateを呼び出す
}