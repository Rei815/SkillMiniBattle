#include "homing_shotgun_delay.h"
#include "../../../bullet_manager/bullet_manager.h"
#include <random>
const CHomingShotgunDelay::BulletParameters CHomingShotgunDelay::m_bullet_parameters =
//          ’e‚ÌID  ”­Ë‘¬“x UŒ‚‘¬“x ‘•“U” ”­Ë”       ‘¬“x     ƒuƒŒ       ”¼Œa     UŒ‚—Í —U“±’x‰„ŠÔ  ‰Á‘¬—Í
{ BULLET_ID::HOMING,      0,      60,     1,     5,      1.0f,  0.15f,      25.0f,      1.0,            60,     0.15f };

CHomingShotgunDelay::CHomingShotgunDelay()
    : CShot(m_bullet_parameters)
{
}

CHomingShotgunDelay::~CHomingShotgunDelay()
{
}
