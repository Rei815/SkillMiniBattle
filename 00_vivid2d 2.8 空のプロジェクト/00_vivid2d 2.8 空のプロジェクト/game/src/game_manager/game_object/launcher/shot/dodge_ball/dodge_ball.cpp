#include "dodge_ball.h"


const CDodgeBall::BulletParameters CDodgeBall::m_bullet_parameters =
//          ’e‚ÌID  ”­Ë‘¬“x UŒ‚‘¬“x ‘•“U” ”­Ë”       ‘¬“x     ƒuƒŒ       ”¼Œa        UŒ‚—Í    —U“±’x‰„ŠÔ  ‰Á‘¬—Í
{ BULLET_ID::NORMAL,      0,       60,     1,     1,     10.0f,      0,      45.0f,     1.0f,             0,      0 };

CDodgeBall::CDodgeBall()
	: CShot(m_bullet_parameters)
{
}

CDodgeBall::~CDodgeBall()
{
}

