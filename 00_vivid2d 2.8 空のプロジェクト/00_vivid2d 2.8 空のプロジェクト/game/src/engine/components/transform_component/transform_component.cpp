#include "transform_component.h"

TransformComponent::TransformComponent()
    : m_Transform()     // �e�l���f�t�H���g�ŏ�����
    , m_WorldMatrix()   // �P�ʍs��ŏ�����
    , m_IsDirty(true)   // ��������͕K����x���[���h�s����v�Z�����邽�߁Atrue�ɐݒ�
{
}

void TransformComponent::SetTransform(const CTransform& transform)
{
    m_Transform = transform;
    m_IsDirty = true; // Transform�f�[�^���ύX���ꂽ���߁A�Čv�Z��v������
}

void TransformComponent::SetPosition(const CVector3& position)
{
    m_Transform.position = position;
    m_IsDirty = true; // Transform�f�[�^���ύX���ꂽ���߁A�Čv�Z��v������
}

void TransformComponent::SetRotation(const CVector3& euler_angles)
{
    m_Transform.rotation = euler_angles;
    m_IsDirty = true; // Transform�f�[�^���ύX���ꂽ���߁A�Čv�Z��v������
}

void TransformComponent::SetScale(const CVector3& scale)
{
    m_Transform.scale = scale;
    m_IsDirty = true; // Transform�f�[�^���ύX���ꂽ���߁A�Čv�Z��v������
}

void TransformComponent::SetScale(float scale)
{
    m_Transform.scale = CVector3(scale, scale, scale);
    m_IsDirty = true; // Transform�f�[�^���ύX���ꂽ���߁A�Čv�Z��v������
}

void TransformComponent::Translate(const CVector3& offset)
{
    m_Transform.position += offset;
    m_IsDirty = true; // �ʒu���ύX���ꂽ���߁A�Čv�Z��v������
}

const CMatrix& TransformComponent::GetWorldMatrix() const
{
    // �_�[�e�B�t���O�������Ă���ꍇ�i���O��̎擾����l���ύX���ꂽ�ꍇ�j�̂ݍČv�Z�����s
    if (m_IsDirty)
    {
        RecalculateWorldMatrix();
    }
    // �ύX���Ȃ���΁A�L���b�V���ς݂̍s������̂܂ܕԂ�
    return m_WorldMatrix;
}

float TransformComponent::GetLength() const
{
	// ���[���h���W�n�ł̈ʒu�x�N�g���̒������v�Z���ĕԂ�
    return CVector3::Length(m_Transform.position);
}

void TransformComponent::RecalculateWorldMatrix() const
{
    // �eTransform�v�f����s��𐶐�
    CMatrix scaleMat = CMatrix::Scale(m_Transform.scale);
    CMatrix rotationMat = CMatrix::Rotate(m_Transform.rotation);
    CMatrix translateMat = CMatrix::Translate(m_Transform.position);

    // ���[���h�s����v�Z���ăL���b�V��
    m_WorldMatrix = scaleMat * rotationMat * translateMat;

    // �Čv�Z�����������̂ŁA�t���O���~�낷�B
    // ����ɂ��A����GetWorldMatrix���Ă΂�Ă��l���ύX����Ă��Ȃ���΍Čv�Z�͑���Ȃ��B
    m_IsDirty = false;
}