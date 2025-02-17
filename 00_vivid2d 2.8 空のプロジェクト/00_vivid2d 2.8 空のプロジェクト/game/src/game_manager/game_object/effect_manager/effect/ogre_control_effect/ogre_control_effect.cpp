#include "ogre_control_effect.h"

const std::string COgreControlEffect::m_file_name = "data\\Effects\\ogre_control.efk";

COgreControlEffect::COgreControlEffect()
	: IEffect(m_file_name, EFFECT_ID::OGRE_CONTROL)
{
}

COgreControlEffect::~COgreControlEffect()
{
}

