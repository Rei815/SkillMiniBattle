#pragma once
#include <string>
#include "..\effect.h"
class CDestroyEffect : public IEffect
{
public:
	CDestroyEffect();
	~CDestroyEffect();

private:
	static const std::string m_file_name;

};