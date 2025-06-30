#include "barrier_effect.h"

const std::string CBarrierEffect::m_file_name = "data\\Effects\\barrier.efk";

CBarrierEffect::CBarrierEffect()
	: IEffect(m_file_name, EFFECT_ID::BARRIER)
{
}

CBarrierEffect::~CBarrierEffect()
{
	IEffect::Update();
}

