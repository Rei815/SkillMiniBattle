#include "animation.h"

IAnimation::IAnimation()
	: m_ActiveFlag(true)
{
}

IAnimation::~IAnimation()
{

}

void IAnimation::Update(void)
{

}

void IAnimation::Finalize(void)
{

}

bool IAnimation::IsActive(void)
{
	return m_ActiveFlag;
}

void IAnimation::Delete()
{
	m_ActiveFlag = false;
}