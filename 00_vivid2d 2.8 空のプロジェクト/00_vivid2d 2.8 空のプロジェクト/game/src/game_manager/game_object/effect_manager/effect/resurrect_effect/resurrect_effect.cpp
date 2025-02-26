#include "resurrect_effect.h"

const std::string CResurrectEffect::m_file_name = "data\\Effects\\resurect_effect.efk";
const float CResurrectEffect::m_speed = 0.5f;

CResurrectEffect::CResurrectEffect()
	: IEffect(m_file_name, EFFECT_ID::RESURRECT)
{
}

CResurrectEffect::~CResurrectEffect()
{
	IEffect::Update();
}
