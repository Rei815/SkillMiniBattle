#include "gimmick.h"

CGimmick::CGimmick()
	: m_Object(nullptr)
	, m_Timer()
	, m_OperationFlag(false)
	, m_State(GIMMICK_STATE::WAIT)
	, m_ActiveFlag(true)
{
}

CGimmick::~CGimmick(void)
{
}

void CGimmick::Initialize(std::shared_ptr<IObject> object)
{
	m_Object = object;
	m_OperationFlag = false;
}

void CGimmick::Initialize(std::shared_ptr<IObject> object, float time)
{
	m_Object = object;
	m_OperationFlag = false;
	m_Timer.SetUp(time);
}

void CGimmick::Update(void)
{
	m_Timer.Update();
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

bool CGimmick::IsActive(void)
{
	return m_ActiveFlag;
}

void CGimmick::SetActive(bool active)
{
	m_ActiveFlag = active;
}

void CGimmick::SetOperationFlag(bool flag)
{
	m_OperationFlag = flag;
}

void CGimmick::SetTimer(float time)
{
	m_Timer.SetUp(time);
}

GIMMICK_STATE CGimmick::GetState(void)
{
	return m_State;
}

void CGimmick::SetState(GIMMICK_STATE state)
{
	m_State = state;
}