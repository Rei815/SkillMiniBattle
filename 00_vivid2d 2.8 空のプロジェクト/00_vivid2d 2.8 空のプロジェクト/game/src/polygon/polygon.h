#pragma once
#include "vivid.h"
#include "..\mathematics\mathematics.h"
namespace polygon
{
	void Draw3DRot(int handle, const CVector3& position, int width, int height, const CVector3& rot);
	void Draw3DRot(int handle, const CVector3& position, const CVector3& point, int width, int height, const CVector3& rot);

}