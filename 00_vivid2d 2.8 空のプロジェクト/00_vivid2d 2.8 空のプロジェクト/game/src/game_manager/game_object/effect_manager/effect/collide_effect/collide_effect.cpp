#include "collide_effect.h"

const std::string CCollideEffect::m_file_name = "data\\Effects\\collide_effect.efk";

CCollideEffect::CCollideEffect()
	: IEffect(m_file_name, EFFECT_ID::COLLIDE)
{
}

CCollideEffect::~CCollideEffect()
{
}
