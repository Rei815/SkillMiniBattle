#include "transform.h"
#include "vivid.h"
#include "../utility.h"

CTransform::CTransform()
	: position()
	, rotation()
	, scale(CVector3(1.0f, 1.0f, 1.0f))
{
}

CTransform::CTransform(const CVector3& pos)
	: position(pos)
	, rotation()
	, scale(CVector3(1.0f, 1.0f, 1.0f))
{
}

CTransform::CTransform(const CVector3& pos, const CVector3& rot)
	: position(pos)
	, rotation(rot)
	, scale(CVector3(1.0f, 1.0f, 1.0f))
{
}

CTransform& CTransform::operator=(const CTransform& t)
{
	position = t.position;
	rotation = t.rotation;
	scale = t.scale;

	return *this;
}


CVector3 CTransform::GetForwardVector(void) const
{
	return GetRotateVector(CVector3::FORWARD);
}

CVector3 CTransform::GetRightVector(void) const
{
	return GetRotateVector(CVector3::RIGHT);
}

CVector3 CTransform::GetUpVector(void) const
{
	return GetRotateVector(CVector3::UP);
}

CVector3 CTransform::GetRotateVector(CVector3 vector) const
{
	VECTOR TempVector = VGet(vector.x, vector.y, vector.z);
	CVector3 TempRotation = GetRadianRotation();
	TempVector = VTransformSR(TempVector, MGetRotX(TempRotation.x));
	TempVector = VTransformSR(TempVector, MGetRotY(TempRotation.y));
	TempVector = VTransformSR(TempVector, MGetRotZ(TempRotation.z));
	return CVector3(TempVector.x, TempVector.y, TempVector.z);
}

CVector3 CTransform::GetRadianRotation(void) const
{
	CVector3 temp;
	temp.x = rotation.x / 180.0f * DX_PI_F;
	temp.y = rotation.y / 180.0f * DX_PI_F;
	temp.z = rotation.z / 180.0f * DX_PI_F;

	return temp;
}

