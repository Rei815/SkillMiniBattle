#pragma once
#include "../../../../engine/core/component/component.h"
#include "../gimmick_component.h"
#include <memory>

// ���̃N���X��O���錾
class CDarumaFallDownGimmick;

class DarumaFallDownGimmickComponent : public GimmickComponent
{
public:
    DarumaFallDownGimmickComponent();
    ~DarumaFallDownGimmickComponent();

    void OnAttach(CGameObject* owner) override;
    void Update(float delta_time, CGameObject* owner) override;

    void OgreControlTurn();
private:
    // ���̃M�~�b�N�̃��W�b�N�����C���X�^���X
    std::unique_ptr<CDarumaFallDownGimmick> m_GimmickLogic;
};