#pragma once
#include "../../mathematics/vector/vector3/vector3.h"

struct CollisionResult
{
    bool isHit = false;         // �Փ˂�����
    CVector3 hitPosition;       // �Փ˂������W
    CVector3 hitNormal;         // �Փ˓_�̖@���x�N�g��
    // �K�v�Ȃ�A�����ɑ��̏��i�߂荞�ݗʂȂǁj��ǉ��ł���
};