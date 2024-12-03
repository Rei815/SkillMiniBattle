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
void CTransform::RotateAround(const CVector3& point, const CVector3& axis, float angle, const CVector3& initPos)
{
	CMatrix mat = MGetRotAxis(axis, (DX_TWO_PI_F / 360.0f) * angle);

	CVector3 localPosition = VTransform(initPos, mat);
	position = localPosition + point;

}

void CTransform::RotateAround(const CVector3& point, const CVector3& axis, float rotateSpeed)
{
	CMatrix mat = MGetRotAxis(axis, (DX_TWO_PI_F / 360.0f) * rotateSpeed);

	CVector3 localPosition = VTransform(position, mat);
	position = localPosition + point;
}

CMatrix CTransform::GetRotateAroundMatrix(const CVector3& point, const CVector3& axis, CMatrix& mulMat, CMatrix& tranMat, CMatrix& rotMat, float rotateSpeed, float angle)
{

	CMatrix rotAroundAxis, selfRotation, translation, finalTransform;
	CreateRotationYXZMatrix(&rotAroundAxis, DEG_TO_RAD(axis.x * rotateSpeed), DEG_TO_RAD(axis.y * rotateSpeed), DEG_TO_RAD(axis.z * rotateSpeed));
	CreateRotationYMatrix(&selfRotation, DEG_TO_RAD(angle));
	// 単位行列
	translation = CMatrix::GetIdentity(translation);
	CreateTranslationMatrix(&translation, position.x, position.y, position.z);
	// 移動させる
	//mulMat *= tranMat;
	// 回転させる 
	//mulMat *= rotMat;

	//mulMat *= matrix;
	// 移動させる
	mulMat *= tranMat;
	// 回転させる 
	//mulMat *= rotMat;
	finalTransform = translation * rotAroundAxis * selfRotation;
	return finalTransform;
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
	CVector3 temp;
	temp.x = rotation.x / 180.0f * DX_PI_F;
	temp.y = rotation.y / 180.0f * DX_PI_F;
	temp.z = rotation.z / 180.0f * DX_PI_F;

	return temp;
}

