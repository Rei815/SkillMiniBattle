#include "gimmick.h"

CGimmick::CGimmick()
{
}

CGimmick::~CGimmick(void)
{
}

void CGimmick::Initialize()
{
}

void CGimmick::Update(void)
{
}

void CGimmick::Draw(void)
{
}

void CGimmick::Finalize(void)
{
}

GIMMICK_ID CGimmick::GetGimmickID(void)
{
	return GIMMICK_ID();
}

bool CGimmick::GetActive(void)
{
	return m_ActiveFlag;
}

void CGimmick::SetActive(bool active)
{
	m_ActiveFlag = active;
}
