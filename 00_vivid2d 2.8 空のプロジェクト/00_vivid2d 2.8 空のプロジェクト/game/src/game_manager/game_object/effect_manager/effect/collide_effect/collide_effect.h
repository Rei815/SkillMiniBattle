#pragma once
#include <string>
#include "..\effect.h"
class CCollideEffect : public IEffect
{
public:
	CCollideEffect();
	~CCollideEffect();

private:
	static const std::string m_file_name;

};