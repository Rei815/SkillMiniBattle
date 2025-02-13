#include "skill_star_effect.h"

const std::string CSkillStarEffect::m_file_name = "data\\Effects\\skill_star.efk";

CSkillStarEffect::CSkillStarEffect()
	: IEffect(m_file_name, EFFECT_ID::STRONG_WIND)
{
}

CSkillStarEffect::~CSkillStarEffect()
{
}

