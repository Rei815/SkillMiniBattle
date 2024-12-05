#include "floating_effect.h"

const std::string CFloatingEffect::m_file_name = "data\\Effects\\floating_effect.efk";

CFloatingEffect::CFloatingEffect()
	: IEffect(m_file_name, EFFECT_ID::FLOATING)
{
}

CFloatingEffect::~CFloatingEffect()
{
}

void CFloatingEffect::Update(void)
{
	if (m_ParentPos)
		m_Transform.position = *m_ParentPos;
}
