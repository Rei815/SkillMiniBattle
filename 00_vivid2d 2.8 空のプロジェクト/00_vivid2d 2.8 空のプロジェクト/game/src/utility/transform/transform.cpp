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

	return *this;
}
