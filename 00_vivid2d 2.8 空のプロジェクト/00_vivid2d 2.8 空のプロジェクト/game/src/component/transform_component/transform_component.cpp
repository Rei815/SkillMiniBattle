#include "transform_component.h"

TransformComponent::TransformComponent()
    : m_transform()     // �f�t�H���g�R���X�g���N�^�ŏ�����
    , m_worldMatrix()   // �f�t�H���g�R���X�g���N�^�ŏ�����
    , m_isDirty(true)   // �ŏ��͕K���Čv�Z���K�v
{
}

void TransformComponent::SetTransform(const CTransform& transform)
{
    m_transform = transform;
    m_isDirty = true; // �f�[�^���ύX���ꂽ�̂Ńt���O�𗧂Ă�
}

void TransformComponent::SetPosition(const CVector3& position)
{
    m_transform.position = position;
    m_isDirty = true;
}

void TransformComponent::SetRotation(const CVector3& euler_angles)
{
    m_transform.rotation = euler_angles; // CTransform���̉�]�����o�ɑ��
    m_isDirty = true;
}

void TransformComponent::SetScale(const CVector3& scale)
{
    m_transform.scale = scale;
    m_isDirty = true;
}

const CMatrix& TransformComponent::GetWorldMatrix() const
{
    if (m_isDirty)
    {
        RecalculateWorldMatrix();
    }
    return m_worldMatrix;
}

// ������ ���������Ȃ��̃v���W�F�N�g��p�̍ŏI�łł� ������
void TransformComponent::RecalculateWorldMatrix() const
{
    // ���Ȃ���CMatrix�N���X�̐ÓI���\�b�h���g���āA�e�s��𐶐����܂��B
    CMatrix scaleMat = CMatrix::Scale(m_transform.scale);
    CMatrix rotationMat = CMatrix::Rotate(m_transform.rotation);
    CMatrix translateMat = CMatrix::Translate(m_transform.position);

    // ���[���h�s����v�Z���ăL���b�V�����܂��B
    // (CMatrix�N���X�ŉ��Z�q���I�[�o�[���[�h����Ă���̂ŁA���̂܂܊|���Z�ł��܂���)
    m_worldMatrix = scaleMat * rotationMat * translateMat;

    // �Čv�Z�����������̂ŁA�t���O���~�낵�܂��B
    m_isDirty = false;
}