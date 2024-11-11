#include "forecast_line_effect.h"

const std::string CForecastLineEffect::m_file_name = "data\\Effects\\forecast_line.efk";

CForecastLineEffect::CForecastLineEffect()
	: IEffect(m_file_name, EFFECT_ID::PLAYER_BULLET)
{
}

CForecastLineEffect::~CForecastLineEffect()
{
}

