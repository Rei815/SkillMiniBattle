#pragma once
#include <string>
#include "..\effect.h"
class CDebuffEffect : public IEffect
{
public:
	CDebuffEffect();
	~CDebuffEffect();

private:
	static const std::string m_file_name;

};