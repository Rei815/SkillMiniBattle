#include "skill_barrier_effect.h"

const std::string CSkillBarrierEffect::m_file_name = "data\\Effects\\skill_barrier.efk";

CSkillBarrierEffect::CSkillBarrierEffect()
	: IEffect(m_file_name, EFFECT_ID::PLAYER_BULLET)
{
}

CSkillBarrierEffect::~CSkillBarrierEffect()
{
	IEffect::Update();
}

