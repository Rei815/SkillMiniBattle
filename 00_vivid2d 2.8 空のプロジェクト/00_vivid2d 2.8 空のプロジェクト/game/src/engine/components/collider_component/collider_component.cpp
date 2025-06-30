#include "collider_component.h"

ColliderComponent::ColliderComponent()
    : m_IsEnabled(true) // �R���X�g���N�^�ŁA�f�t�H���g�͗L��(true)�ɏ�����
{
}

void ColliderComponent::SetEnabled(bool isEnabled)
{
    m_IsEnabled = isEnabled;
}

bool ColliderComponent::IsEnabled() const
{
    return m_IsEnabled;
}