#include "hit_effect.h"

const std::string CHitEffect::m_file_name = "data\\Effects\\hit_effect.efk";

CHitEffect::CHitEffect()
	: IEffect(m_file_name, EFFECT_ID::HIT)
{
}

CHitEffect::~CHitEffect()
{
}
