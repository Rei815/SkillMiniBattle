#pragma once
#include <string>
#include "..\effect.h"
class CFloatingEffect : public IEffect
{
public:
	CFloatingEffect();
	~CFloatingEffect();

	/*!
	 *  @brief      çXêV
	 */
	void Update(void);

private:
	static const std::string m_file_name;

};