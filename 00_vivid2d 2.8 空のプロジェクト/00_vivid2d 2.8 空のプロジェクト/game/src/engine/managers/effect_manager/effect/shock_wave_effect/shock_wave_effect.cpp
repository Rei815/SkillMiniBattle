#include "shock_wave_effect.h"

const std::string CShockWaveEffect::m_file_name = "data\\Effects\\shock_wave_effect.efk";
const float CShockWaveEffect::m_speed = 0.5f;

 CShockWaveEffect:: CShockWaveEffect()
	: IEffect(m_file_name, EFFECT_ID::SHOCK_WAVE, m_speed)
{
}

 CShockWaveEffect::~ CShockWaveEffect()
{
	 IEffect::Update();
}
