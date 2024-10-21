#include "transform.h"


CTransform::CTransform()
	: position()
	, rotation()
	, scale()
{
}

CTransform::CTransform(const CVector3& pos)
	: position(pos)
{
}

CTransform::CTransform(const CVector3& pos, const CVector3& rot)
	: position(pos)
	, rotation(rot)
{
}

CTransform& CTransform::operator=(const CTransform& t)
{
	position = t.position;
	rotation = t.rotation;
	scale = t.scale;

	return *this;
}


CVector3 CTransform::GetRadianRotation(void)
{
	const float math_pi = 3.1415926535897931;

	CVector3 temp;
	temp.x = rotation.x / 180.0f * math_pi;
	temp.y = rotation.y / 180.0f * math_pi;
	temp.z = rotation.z / 180.0f * math_pi;

	return temp;
}