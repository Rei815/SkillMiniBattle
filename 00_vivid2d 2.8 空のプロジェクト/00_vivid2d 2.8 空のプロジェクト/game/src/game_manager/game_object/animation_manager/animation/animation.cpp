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

bool IAnimation::GetActive(void)
{
	return m_ActiveFlag;
}

void IAnimation::SetActive(bool active)
{
	m_ActiveFlag = active;
}