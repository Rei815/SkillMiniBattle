#pragma once
#include <string>
#include "..\effect.h"
class CGravityAreaEffect : public IEffect
{
public:
	CGravityAreaEffect();
	~CGravityAreaEffect();

	/*!
	 *  @brief      �X�V
	 */
	void Update(void);

private:
	static const std::string m_file_name;

};