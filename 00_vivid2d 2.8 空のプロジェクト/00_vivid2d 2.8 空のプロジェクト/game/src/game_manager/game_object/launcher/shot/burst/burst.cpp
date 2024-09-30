#include "burst.h"
#include "../../../bullet_manager/bullet_manager.h"
const CBurst::BulletParameters CBurst::m_bullet_parameters =
//          �e��ID   ���ˑ��x  �U�����x ���U�� ���ː�       ���x     �u��       ���a     �U���� �U�����x������  ������
{ BULLET_ID::NORMAL,       15,       30,     3,    1,      50.0f,      0,      30.0f,     0.75f,             0,      0 };

CBurst::CBurst()
	: CShot(m_bullet_parameters)
{
}

CBurst::~CBurst()
{
}