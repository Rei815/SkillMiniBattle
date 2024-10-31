#include "transform.h"
#include "vivid.h"

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


CVector3 CTransform::GetForwardVector(void)
{
	return GetRotateVector(CVector3().FORWARD);
}

CVector3 CTransform::GetRightVector(void)
{
	return GetRotateVector(CVector3().RIGHT);
}

CVector3 CTransform::GetUpVector(void)
{
	return GetRotateVector(CVector3().UP);
}

/*
 *  指定の軸を中心に回転(フレーム)
 */
void CTransform::RotateAround(int handle, int frameIndex, const CVector3& point, const CVector3& axis, float angle)
{
	MV1SetFrameUserLocalMatrix(handle, frameIndex, MGetTranslate(VTransform(point, MGetRotAxis(axis, (DX_TWO_PI_F / 360.0f) * angle))));
}

/*
 *  指定の軸を中心に回転
 */
void CTransform::RotateAround(const CVector3& point, const CVector3& axis, float angle)
{
	MATRIX mat = MGetRotAxis(axis, (DX_TWO_PI_F / 360.0f) * angle);

	CVector3 localPosition = VTransform(position, mat);
	//position = VAdd(point, localPosition);
	position = localPosition + point;
}

CVector3 CTransform::GetRotateVector(CVector3 vector)
{
	VECTOR TempVector = VGet(vector.x, vector.y, vector.z);
	CVector3 TempRotation = GetRadianRotation();
	TempVector = VTransformSR(TempVector, MGetRotX(TempRotation.x));
	TempVector = VTransformSR(TempVector, MGetRotY(TempRotation.y));
	TempVector = VTransformSR(TempVector, MGetRotZ(TempRotation.z));
	return CVector3(TempVector.x, TempVector.y, TempVector.z);
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

