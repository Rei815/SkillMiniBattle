#pragma once
#include <string>
#include "..\effect.h"
class CPlayerBulletEffect : public IEffect
{
public:
	CPlayerBulletEffect();
	~CPlayerBulletEffect();
private:
	static const std::string m_file_name;
};