#pragma once
#include <string>
#include "..\effect.h"
class CSkillBarrierEffect : public IEffect
{
public:
	CSkillBarrierEffect();
	~CSkillBarrierEffect();
private:
	static const std::string m_file_name;
};