#pragma once
#include "..\animation.h"
class CUI;
class CKeyScale : public IAnimation
{
public:
	CKeyScale();
	~CKeyScale();

private:
	CUI* m_keyPointer;
};