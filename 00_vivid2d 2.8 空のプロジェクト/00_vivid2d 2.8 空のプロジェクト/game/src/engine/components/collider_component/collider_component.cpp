#include "collider_component.h"

ColliderComponent::ColliderComponent()
    : m_IsEnabled(true)
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