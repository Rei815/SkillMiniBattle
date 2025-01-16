#include "animation.h"

IAnimation::IAnimation()
{
}

IAnimation::~IAnimation()
{

}

void IAnimation::Initialize(void* object_pointer)
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
