#include "homing.h"
const CHoming::BulletParameters CHoming::m_bullet_parameters =
//          �e��ID  ���ˑ��x �U�����x ���U�� ���ː�       ���x     �u��       ���a     �U���� �U�����x������		������
{ BULLET_ID::HOMING,       0,      60,     1,     1,	20.0f,      0,      20.0f,     1.25,              0,       0.15f};

CHoming::CHoming()
	: CShot(m_bullet_parameters)
{
}

CHoming::~CHoming()
{
}

