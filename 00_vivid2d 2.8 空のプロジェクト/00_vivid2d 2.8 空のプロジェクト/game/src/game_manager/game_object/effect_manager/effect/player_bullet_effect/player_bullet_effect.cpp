#include "player_bullet_effect.h"

const std::string CPlayerBulletEffect::m_file_name = "data\\Effects\\player_bullet_effect_2.efk";

CPlayerBulletEffect::CPlayerBulletEffect()
	: IEffect(m_file_name, EFFECT_ID::PLAYER_BULLET)
{
}

CPlayerBulletEffect::~CPlayerBulletEffect()
{
}

