#pragma once
#include <string>
#include "..\effect.h"
class CForecastLineEffect : public IEffect
{
public:
	CForecastLineEffect();
	~CForecastLineEffect();
private:
	static const std::string m_file_name;
};