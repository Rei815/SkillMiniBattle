#pragma once
#include <string>
#include "..\effect.h"
class CBarrierEffect : public IEffect
{
public:
	CBarrierEffect();
	~CBarrierEffect();
private:
	static const std::string m_file_name;
};