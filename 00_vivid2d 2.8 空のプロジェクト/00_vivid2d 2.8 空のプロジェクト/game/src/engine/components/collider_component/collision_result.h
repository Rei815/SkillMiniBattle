#pragma once
#include "../../mathematics/vector/vector3/vector3.h"

struct CollisionResult
{
    bool isHit = false;         //!< �Փ˂�����
    CVector3 hitPosition;       //!< �Փ˂������W
    CVector3 hitNormal;         //!< �Փ˓_�̖@���x�N�g��
};