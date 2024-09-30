#pragma once
#include <string>
#include "..\effect.h"
class CEnemyBulletEffect : public IEffect
{
public:
	CEnemyBulletEffect();
	~CEnemyBulletEffect();
private:
	static const std::string m_file_name;
};