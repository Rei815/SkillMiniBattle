#include "enemy_bullet_effect.h"

const std::string CEnemyBulletEffect::m_file_name = "data\\Effects\\enemy_bullet_effect.efk";

CEnemyBulletEffect::CEnemyBulletEffect()
	: IEffect(m_file_name, EFFECT_ID::PLAYER_BULLET)
{
}

CEnemyBulletEffect::~CEnemyBulletEffect()
{
}

