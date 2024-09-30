#pragma once

#include "collider_attribute.h"
#include "../mathematics/mathematics.h"

class ICollider
{
public:
	ICollider();
	~ICollider();

    /*!
     *  @brief      à íuê›íË
     *
     *  @param[in]  position    à íu
     */
    void            SetPosition(const CVector3& position);

private:
	CVector3		m_Position;
};
