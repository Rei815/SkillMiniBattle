#include "gimmick.h"

IGimmick::IGimmick()
{
}

IGimmick::IGimmick(GIMMICK_ID gimmick_id)
{
}

IGimmick::~IGimmick(void)
{
}

void IGimmick::Initialize(const CVector3& position)
{
}

void IGimmick::Update(void)
{
}

void IGimmick::Draw(void)
{
}

void IGimmick::Finalize(void)
{
}

GIMMICK_ID IGimmick::GetGimmickID(void)
{
	return GIMMICK_ID();
}

bool IGimmick::GetActive(void)
{
	return false;
}

void IGimmick::SetActive(bool active)
{
}
