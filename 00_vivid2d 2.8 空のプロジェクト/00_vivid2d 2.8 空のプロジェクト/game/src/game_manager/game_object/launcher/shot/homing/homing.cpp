#include "homing.h"
const CHoming::BulletParameters CHoming::m_bullet_parameters =
//          ’e‚ÌID  ”­Ë‘¬“x UŒ‚‘¬“x ‘•“U” ”­Ë”       ‘¬“x     ƒuƒŒ       ”¼Œa     UŒ‚—Í —U“±’x‰„ŠÔ		‰Á‘¬—Í
{ BULLET_ID::HOMING,       0,      60,     1,     1,	20.0f,      0,      20.0f,     1.25,              0,       0.15f};

CHoming::CHoming()
	: CShot(m_bullet_parameters)
{
}

CHoming::~CHoming()
{
}

