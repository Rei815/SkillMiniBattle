#include "collider.h"

ICollider::ICollider()
{
}

ICollider::~ICollider()
{
}

/*
 *  �ʒu�ݒ�
 */
void
ICollider::SetPosition(const CVector3& positioin)
{
    m_Position = positioin;
}
