#pragma once
#include <string>
#include "..\effect.h"
class CFloatingEffect : public IEffect
{
public:
	CFloatingEffect();
	~CFloatingEffect();


private:
	static const std::string m_file_name;
	static const float m_offset;

};