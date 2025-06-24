#pragma once
#include "../component.h"      // IComponent �̊��N���X
#include "../../utility/transform/transform.h"
class TransformComponent : public IComponent
{
public:
    // ���̃R���|�[�l���g���ێ�����f�[�^
    CTransform transform;

public:
    // �R���X�g���N�^
    TransformComponent() = default;

    // �f�X�g���N�^
    ~TransformComponent() override = default;

    // ���̃R���|�[�l���g�́A�������g�ŉ������X�V����K�v�͂Ȃ��̂ŁA
    // Update�̒��g�͋��OK�ł��B
    // ���̃R���|�[�l���g���A����TransformComponent�̏����Q�Ƃ��ē��삵�܂��B
    void Update(float delta_time, CGameObject* owner) override
    {
        // �������Ȃ�
    }
};