#include "collider_component.h"

ColliderComponent::ColliderComponent()
    : m_IsEnabled(true) // コンストラクタで、デフォルトは有効(true)に初期化
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