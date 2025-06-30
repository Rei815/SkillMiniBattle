#include "debuff_effect.h"

const std::string CDebuffEffect::m_file_name = "data\\Effects\\debuff.efk";

CDebuffEffect::CDebuffEffect()
	: IEffect(m_file_name, EFFECT_ID::DEBUFF)
{
}

CDebuffEffect::~CDebuffEffect()
{
}
