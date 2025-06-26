#pragma once
#include "../component.h"
#include "../../mathematics/mathematics.h" // CTransform, CMatrix �ȂǁA���Ȃ��̃v���W�F�N�g�̌^�ɍ��킹�Ă�������
#include "../../utility/transform/transform.h"

class TransformComponent : public IComponent
{
private:
    // ���Ȃ��̃v���W�F�N�g�Ɋ����́A���W�E��]�E�X�P�[�����܂Ƃ߂��\���́iCTransform�Ȃǁj�����̂܂܎g���܂��B
    CTransform m_transform;

    // �œK���̂��߂̃f�[�^
    mutable CMatrix m_worldMatrix;
    mutable bool    m_isDirty;

public:
    // --- �R���X�g���N�^ ---
    TransformComponent();
    ~TransformComponent() override = default;

    // --- �X�V���� ---
    void Update(float delta_time, CGameObject* owner) override {}

    // --- �Q�b�^�[ / �Z�b�^�[ ---
    const CTransform& GetTransform() const { return m_transform; }
    void SetTransform(const CTransform& transform);

    // ���g���₷�����邽�߂֗̕��ȃ��\�b�h
    void SetPosition(const CVector3& position);
    void SetRotation(const CVector3& euler_angles);
    void SetScale(const CVector3& scale);

    // --- �s��擾 ---
    const CMatrix& GetWorldMatrix() const;

private:
    // --- �������� ---
    void RecalculateWorldMatrix() const;
};