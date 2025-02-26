#include "resurrect_effect.h"

const std::string CResurrectEffect::m_file_name = "data\\Effects\\resurrect.efk";

CResurrectEffect::CResurrectEffect()
	: IEffect(m_file_name, EFFECT_ID::RESURRECT)
{
}

CResurrectEffect::~CResurrectEffect()
{
}

