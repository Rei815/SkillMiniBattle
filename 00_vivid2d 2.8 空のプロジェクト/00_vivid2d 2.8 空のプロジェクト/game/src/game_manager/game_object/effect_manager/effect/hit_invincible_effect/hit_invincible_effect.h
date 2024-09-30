#pragma once
#include <string>
#include "..\effect.h"
class CHitInvincibleEffect : public IEffect
{
public:
	CHitInvincibleEffect();
	~CHitInvincibleEffect();

private:
	static const std::string m_file_name;

};