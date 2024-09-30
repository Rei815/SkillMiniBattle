#include "shotgun.h"
#include "../../../bullet_manager/bullet_manager.h"
#include <random>
const CShotgun::BulletParameters CShotgun::m_bullet_parameters =
//          ’e‚ÌID  ”­Ë‘¬“x UŒ‚‘¬“x ‘•“U” ”­Ë”       ‘¬“x     ƒuƒŒ       ”¼Œa     UŒ‚—Í —U“±’x‰„ŠÔ  ‰Á‘¬—Í
{ BULLET_ID::NORMAL,      0,      60,     1,     5,      20.0f,  0.15f,      25.0f,      1.0,             0,     0};

CShotgun::CShotgun()
	: CShot(m_bullet_parameters)
{
}

CShotgun::~CShotgun()
{
}