#include "dodge_ball.h"


const CDodgeBall::BulletParameters CDodgeBall::m_bullet_parameters =
//          eÌID  ­Ë¬x U¬x U ­Ë       ¬x     u       ¼a        UÍ    U±xÔ  Á¬Í
{ BULLET_ID::CANNON,      0,       60,     1,     1,     3000.0f,      0,      45.0f,     1.0f,             0,      0 };

CDodgeBall::CDodgeBall()
	: CShot(m_bullet_parameters)
{
}

CDodgeBall::~CDodgeBall()
{
}

