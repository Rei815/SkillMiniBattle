#pragma once
#include "../../../../engine/core/component/component.h"
#include <memory>

class CBeltConveyorGimmick; // ���̃N���X��O���錾

class BeltConveyorGimmickComponent : public IComponent
{
public:
    BeltConveyorGimmickComponent();
    ~BeltConveyorGimmickComponent();

    void OnAttach(CGameObject* owner) override;
    void Update(float delta_time, CGameObject* owner) override;

    void SetState()
private:
    std::unique_ptr<CBeltConveyorGimmick> m_GimmickLogic;
};