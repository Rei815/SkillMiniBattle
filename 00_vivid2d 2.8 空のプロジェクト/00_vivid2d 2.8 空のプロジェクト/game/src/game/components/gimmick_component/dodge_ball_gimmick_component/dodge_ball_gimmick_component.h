#pragma once
#include "../../../../engine/core/component/component.h"
#include <memory>
#include "dodge_ball_gimmick/dodge_ball_gimmick.h"

// ���̃N���X��O���錾
class CDodgeBallGimmick;

class DodgeBallGimmickComponent : public IComponent
{
public:
    DodgeBallGimmickComponent();
    ~DodgeBallGimmickComponent();

    void OnAttach(CGameObject* owner) override;
    void Update(float delta_time, CGameObject* owner) override;

    void SetOperationFlag(bool flag);

    CANNON_STATE    GetNowState();

    bool            GetShotFlag();

private:
    // ���̃M�~�b�N�̃��W�b�N�����C���X�^���X
    std::unique_ptr<CDodgeBallGimmick> m_GimmickLogic;
};