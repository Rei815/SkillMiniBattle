#include "transform.h"

CTransform::CTransform()
	:position(0,0,0)
{
}

CTransform& CTransform::operator=(const CTransform& t)
{
	position = t.position;

	return *this;
}
