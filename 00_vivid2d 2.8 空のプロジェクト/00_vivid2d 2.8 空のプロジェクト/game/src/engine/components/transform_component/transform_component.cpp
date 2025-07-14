#include "transform_component.h"

TransformComponent::TransformComponent()
    : m_Transform()     // �f�t�H���g�R���X�g���N�^�ŏ�����
    , m_worldMatrix()   // �f�t�H���g�R���X�g���N�^�ŏ�����
    , m_isDirty(true)   // �ŏ��͕K���Čv�Z���K�v
{
}

void TransformComponent::SetTransform(const CTransform& transform)
{
    m_Transform = transform;
    m_isDirty = true; // �f�[�^���ύX���ꂽ�̂Ńt���O�𗧂Ă�
}

void TransformComponent::SetPosition(const CVector3& position)
{
    m_Transform.position = position;
    m_isDirty = true;
}

void TransformComponent::SetRotation(const CVector3& euler_angles)
{
    m_Transform.rotation = euler_angles;
    m_isDirty = true;
}

void TransformComponent::SetScale(const CVector3& scale)
{
    m_Transform.scale = scale;
    m_isDirty = true;
}

void TransformComponent::SetScale(float scale)
{
    m_Transform.scale.x = scale;
    m_Transform.scale.y = scale;
    m_Transform.scale.z = scale;
    m_isDirty = true;

}

void TransformComponent::Translate(const CVector3& offset)
{
    // ���݈ʒu�ɁA�I�t�Z�b�g�i�ړ��ʁj�����Z����
    m_Transform.position += offset;

    // �ʒu���ύX���ꂽ�̂ŁA�Y�ꂸ�Ƀ_�[�e�B�t���O�𗧂Ă�
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

float TransformComponent::GetLength() const
{
    return CVector3::Length(m_Transform.position);
}

void TransformComponent::RecalculateWorldMatrix() const
{
    // ���Ȃ���CMatrix�N���X�̐ÓI���\�b�h���g���āA�e�s��𐶐����܂��B
    CMatrix scaleMat = CMatrix::Scale(m_Transform.scale);
    CMatrix rotationMat = CMatrix::Rotate(m_Transform.rotation);
    CMatrix translateMat = CMatrix::Translate(m_Transform.position);

    // ���[���h�s����v�Z���ăL���b�V�����܂��B
    m_worldMatrix = scaleMat * rotationMat * translateMat;

    // �Čv�Z�����������̂ŁA�t���O���~�낵�܂��B
    m_isDirty = false;
}