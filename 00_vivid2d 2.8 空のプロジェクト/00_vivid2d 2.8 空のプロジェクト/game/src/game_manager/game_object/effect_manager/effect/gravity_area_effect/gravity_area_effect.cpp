#include "gravity_area_effect.h"

const std::string CGravityAreaEffect::m_file_name = "data\\Effects\\gravity_area.efk";

CGravityAreaEffect::CGravityAreaEffect()
	: IEffect(m_file_name, EFFECT_ID::GRAVITY_AREA)
{
}

CGravityAreaEffect::~CGravityAreaEffect()
{
}

void CGravityAreaEffect::Update(void)
{
	IEffect::Update();
}
