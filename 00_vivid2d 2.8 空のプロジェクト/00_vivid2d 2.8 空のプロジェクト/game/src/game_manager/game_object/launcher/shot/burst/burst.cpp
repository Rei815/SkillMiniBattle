#include "burst.h"
#include "../../../bullet_manager/bullet_manager.h"
const CBurst::BulletParameters CBurst::m_bullet_parameters =
//          ’e‚ÌID   ”­Ë‘¬“x  UŒ‚‘¬“x ‘•“U” ”­Ë”       ‘¬“x     ƒuƒŒ       ”¼Œa     UŒ‚—Í —U“±’x‰„ŠÔ  ‰Á‘¬—Í
{ BULLET_ID::NORMAL,       15,       30,     3,    1,      50.0f,      0,      30.0f,     0.75f,             0,      0 };

CBurst::CBurst()
	: CShot(m_bullet_parameters)
{
}

CBurst::~CBurst()
{
}