#include "jump_effect.h"

const std::string CJumpEffect::m_file_name = "data\\Effects\\jump_effect.efk";

CJumpEffect::CJumpEffect()
	: IEffect(m_file_name, EFFECT_ID::JUMP)
{
}

CJumpEffect::~CJumpEffect()
{
}
