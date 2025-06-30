#pragma once
#include "../gimmick_component.h" // �e�N���X�ł���GimmickComponent���C���N���[�h
#include "../../../../engine/utility/timer/timer.h"

class FallGimmickComponent : public GimmickComponent
{
public:
    FallGimmickComponent();
    ~FallGimmickComponent() = default;

    // --- IComponent����̃I�[�o�[���C�h ---
    void OnAttach(CGameObject* owner) override;
    void Update(float delta_time, CGameObject* owner) override;

    // --- ���̃N���X�ŗL�̃��\�b�h ---
    void AddReturnTime(float time);

private:
    static const float  m_fall_speed;       //!< �����鑬�x
    static const float  m_return_height;    //!< ���ɖ߂鍂��
    static const float  m_return_time;      //!< ���ɖ߂�܂ł̎���

    float               m_StartHeight;      //!< �����̍���
    float               m_ReturnTime;       //!< ���ɖ߂�܂ł̎���
    CTimer              m_ReturnTimer;      //!< �߂�܂ł̃^�C�}�[
};