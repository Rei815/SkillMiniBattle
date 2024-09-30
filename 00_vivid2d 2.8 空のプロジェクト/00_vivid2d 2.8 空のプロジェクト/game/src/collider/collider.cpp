#include "collider.h"

ICollider::ICollider()
{
}

ICollider::~ICollider()
{
}

/*
 *  à íuê›íË
 */
void
ICollider::SetPosition(const CVector3& positioin)
{
    m_Position = positioin;
}
