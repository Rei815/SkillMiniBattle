#include "homing_shotgun.h"
#include "../../../bullet_manager/bullet_manager.h"
#include <random>
const CHomingShotgun::BulletParameters CHomingShotgun::m_bullet_parameters =
//          ’e‚ÌID  ”­Ë‘¬“x UŒ‚‘¬“x ‘•“U” ”­Ë”       ‘¬“x     ƒuƒŒ       ”¼Œa     UŒ‚—Í —U“±’x‰„ŠÔ  ‰Á‘¬—Í
{ BULLET_ID::HOMING,      0,      60,     1,     5,      15.0f,  10.0f,      25.0f,      1.0,             0,     };

CHomingShotgun::CHomingShotgun()
    : CShot(m_bullet_parameters)
{
}

CHomingShotgun::~CHomingShotgun()
{
}