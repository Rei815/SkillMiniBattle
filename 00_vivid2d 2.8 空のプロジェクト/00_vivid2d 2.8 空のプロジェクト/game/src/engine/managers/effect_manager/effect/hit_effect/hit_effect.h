#pragma once
#include <string>
#include "..\effect.h"
class CHitEffect : public IEffect
{
public:
	CHitEffect();
	~CHitEffect();

private:
	static const std::string m_file_name;

};