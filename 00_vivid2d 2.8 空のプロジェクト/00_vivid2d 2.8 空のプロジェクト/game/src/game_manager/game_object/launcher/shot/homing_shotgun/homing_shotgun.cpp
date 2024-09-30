#include "homing_shotgun.h"
#include "../../../bullet_manager/bullet_manager.h"
#include <random>
const CHomingShotgun::BulletParameters CHomingShotgun::m_bullet_parameters =
//          �e��ID  ���ˑ��x �U�����x ���U�� ���ː�       ���x     �u��       ���a     �U���� �U�����x������  ������
{ BULLET_ID::HOMING,      0,      60,     1,     5,      15.0f,  10.0f,      25.0f,      1.0,             0,     };

CHomingShotgun::CHomingShotgun()
    : CShot(m_bullet_parameters)
{
}

CHomingShotgun::~CHomingShotgun()
{
}