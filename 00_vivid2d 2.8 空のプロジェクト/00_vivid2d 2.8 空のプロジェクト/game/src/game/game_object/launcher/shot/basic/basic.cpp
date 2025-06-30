#include "basic.h"
const CBasic::BulletParameters CBasic::m_bullet_parameters =
//          ’e‚ÌID  ”­Ë‘¬“x UŒ‚‘¬“x ‘•“U” ”­Ë”       ‘¬“x     ƒuƒŒ       ”¼Œa     UŒ‚—Í —U“±’x‰„ŠÔ  ‰Á‘¬—Í
{ BULLET_ID::NORMAL,      0,       60,     1,     1,     30.0f,      0,      45.0f,     1.0f,             0,      0 };

CBasic::CBasic()
	: CShot(m_bullet_parameters)
{
}

CBasic::~CBasic()
{
}

