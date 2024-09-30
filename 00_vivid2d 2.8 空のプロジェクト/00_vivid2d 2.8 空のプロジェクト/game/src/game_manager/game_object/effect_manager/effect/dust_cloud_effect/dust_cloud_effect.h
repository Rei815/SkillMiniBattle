#pragma once
#include <string>
#include "..\effect.h"
class CDustCloudEffect : public IEffect
{
public:
	CDustCloudEffect();
	~CDustCloudEffect();

private:
	static const std::string m_file_name;

};