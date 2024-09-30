#include "homing_burst.h"
#include "../../../bullet_manager/bullet_manager.h"
const CHomingBurst::BulletParameters CHomingBurst::m_bullet_parameters =
//          �e��ID   ���ˑ��x  �U�����x ���U�� ���ː�       ���x     �u��       ���a     �U���� �U�����x������  ������
{ BULLET_ID::HOMING,       15,       30,     3,    1,      50.0f,      0,      30.0f,     0.75f,             0,     0.15f};

CHomingBurst::CHomingBurst()
	: CShot(m_bullet_parameters)
{
}

CHomingBurst::~CHomingBurst()
{
}