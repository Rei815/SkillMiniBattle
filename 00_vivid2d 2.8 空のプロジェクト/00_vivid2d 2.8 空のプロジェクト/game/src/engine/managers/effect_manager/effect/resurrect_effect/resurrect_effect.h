#pragma once
#include <string>
#include "..\effect.h"
class CResurrectEffect : public IEffect
{
public:
	CResurrectEffect();
	~CResurrectEffect();
private:
	static const std::string m_file_name;
};