#pragma once
#include <string>
#include "..\effect.h"
class COgreControlEffect : public IEffect
{
public:
	COgreControlEffect();
	~COgreControlEffect();
private:
	static const std::string m_file_name;
};