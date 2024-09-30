#include "shock_wave_effect.h"

const std::string CShockWaveEffect::m_file_name = "data\\Effects\\shock_wave_effect.efk";

 CShockWaveEffect:: CShockWaveEffect()
	: IEffect(m_file_name, EFFECT_ID::SHOCK_WAVE)
{
}

 CShockWaveEffect::~ CShockWaveEffect()
{
}
