#pragma once
#include <string>
#include "..\effect.h"
class CJumpEffect : public IEffect
{
public:
	CJumpEffect();
	~CJumpEffect();

private:
	static const std::string m_file_name;

};