#include "dodge_ball.h"


const CDodgeBall::BulletParameters CDodgeBall::m_bullet_parameters =
//          �e��ID  ���ˑ��x �U�����x ���U�� ���ː�       ���x     �u��       ���a        �U����    �U�����x������  ������
{ BULLET_ID::CANNON,      0,       60,     1,     1,     30.0f,      0,      45.0f,     1.0f,             0,      0 };

CDodgeBall::CDodgeBall()
	: CShot(m_bullet_parameters)
{
}

CDodgeBall::~CDodgeBall()
{
}

