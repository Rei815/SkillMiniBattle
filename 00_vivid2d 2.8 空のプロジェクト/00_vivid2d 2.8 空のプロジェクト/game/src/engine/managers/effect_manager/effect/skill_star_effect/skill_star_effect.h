#pragma once
#include <string>
#include "..\effect.h"
class CSkillStarEffect : public IEffect
{
public:
	CSkillStarEffect();
	~CSkillStarEffect();
private:
	static const std::string m_file_name;
};