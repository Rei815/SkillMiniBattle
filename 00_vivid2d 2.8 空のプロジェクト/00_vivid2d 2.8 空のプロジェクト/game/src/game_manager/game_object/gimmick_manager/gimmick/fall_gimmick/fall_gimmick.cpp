#include "fall_gimmick.h"
#include "..\..\..\object_manager\object_manager.h"
CFallGimmick::CFallGimmick()
{
}

CFallGimmick::~CFallGimmick(void)
{
}

void CFallGimmick::Initialize()
{
	m_CreateTime = 180;
	m_CreateTimer = 0;
}

void CFallGimmick::Update(void)
{
	if (++m_CreateTimer > m_CreateTime)
	{
		m_CreateTimer = 0;
		CObjectManager::GetInstance().Create(OBJECT_ID::FALL_OBJECT, CVector3(0,100,0));
	}
}

void CFallGimmick::Draw(void)
{
}

void CFallGimmick::Finalize(void)
{
}