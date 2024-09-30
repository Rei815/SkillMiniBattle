#include "hit_invincible_effect.h"

const std::string CHitInvincibleEffect::m_file_name = "data\\Effects\\hit_invincible_effect.efk";

CHitInvincibleEffect::CHitInvincibleEffect()
	: IEffect(m_file_name, EFFECT_ID::HIT_INVINCBLE)
{
}

CHitInvincibleEffect::~CHitInvincibleEffect()
{
}
