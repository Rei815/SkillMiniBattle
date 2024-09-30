#include "destroy_effect.h"

const std::string CDestroyEffect::m_file_name = "data\\Effects\\destroy_effect.efk";

CDestroyEffect::CDestroyEffect()
	: IEffect(m_file_name, EFFECT_ID::DESTROY)
{
}

CDestroyEffect::~CDestroyEffect()
{
}
