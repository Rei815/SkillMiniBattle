#include "strong_wind_effect.h"

const std::string CStrongWindEffect::m_file_name = "data\\Effects\\strong_wind.efk";

CStrongWindEffect::CStrongWindEffect()
	: IEffect(m_file_name, EFFECT_ID::STRONG_WIND)
{
}

CStrongWindEffect::~CStrongWindEffect()
{
}

