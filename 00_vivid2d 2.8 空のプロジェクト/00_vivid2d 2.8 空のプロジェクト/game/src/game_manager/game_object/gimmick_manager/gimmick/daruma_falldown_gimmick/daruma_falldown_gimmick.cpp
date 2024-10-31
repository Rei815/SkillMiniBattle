#include "daruma_falldown_gimmick.h"
#include "..\..\..\object_manager\object_manager.h"
#include <stdlib.h> rand(), srand()

CDaruma_FallDownGimmick::CDaruma_FallDownGimmick()
	: m_SeenMove(false)
	, m_Touch(false)
	, m_ReadyTime(2)
	, m_WaitTime(1)
	, m_TurnSpeed(15)
	, m_RestPlayer(0)
	, m_Transform()
	, m_OgreState(OGRE_STATE::READY)
	,m_TurnType(TURN_TYPE::FAST)
	,m_Timer(3)
	,m_TurnAngle(180)
{
}

CDaruma_FallDownGimmick::~CDaruma_FallDownGimmick(void)
{
}
void CDaruma_FallDownGimmick::Initialize(IObject* object)
{
	CGimmick::Initialize(object);
	m_Object->SetGimmick(this);
}

void CDaruma_FallDownGimmick::Update(void)
{
	m_Timer.Update();

	switch (m_OgreState)
	{
	case OGRE_STATE::READY:     Ready();       break;
	case OGRE_STATE::PLAY:      Play();        break;
	case OGRE_STATE::WAIT:      Wait();        break;
	case OGRE_STATE::FINISH:    Finish();      break;
	}

	//�N�����S�Ƀ^�b�`������
	if (m_Touch)
	{

	}

	//�v���C���[�̐���0�ɂȂ�����
	if (m_RestPlayer <= 0)
	{

	}
}

void CDaruma_FallDownGimmick::Draw(void)
{
	
}

void CDaruma_FallDownGimmick::Finalize(void)
{
}


void CDaruma_FallDownGimmick::Ready()//�U��Ԃ鏀��
{
	if(m_Timer.Finished())
	{
		m_TurnType = (TURN_TYPE)(rand() % (int)TURN_TYPE::TYPE_NUM);
		switch (m_TurnType)
		{
		case TURN_TYPE::FEINT:
			m_Timer.SetUp(0);
			Feint();
			break;
		case TURN_TYPE::SLOW:
			m_Timer.SetUp(3);
			Slow();
			break;
		case TURN_TYPE::FAST:
			m_Timer.SetUp(0.3);
			Fast();
			break;
		case TURN_TYPE::TYPE_NUM:
			break;
		default:
			break;
		}
		m_OgreState = OGRE_STATE::PLAY;
	}
}

void CDaruma_FallDownGimmick::Play()//�U��Ԃ�
{
	if (m_Object->GetRotation().y < 20)
	{
		m_Transform.rotation.y += m_TurnSpeed;

		if (20 <= m_Transform.rotation.y)
			m_Transform.rotation.y = 20;

		m_Object->SetRotation(m_Transform.rotation);
	}

	if (m_Timer.Finished())
	{
		if (m_Object->GetRotation().y < m_TurnAngle)
		{
			m_Transform.rotation.y += m_TurnSpeed;

			if (m_TurnAngle <= m_Transform.rotation.y)
				m_Transform.rotation.y = m_TurnAngle;

			m_Object->SetRotation(m_Transform.rotation);
		}
		else
		{
			m_ReadyTime = 2;
			m_Timer.SetUp(m_WaitTime);
			m_OgreState = OGRE_STATE::WAIT;
		}
	}
}

void CDaruma_FallDownGimmick::Wait()//�U��Ԃ�����Ԃőҋ@
{
	


	if (m_Timer.Finished())
		m_OgreState = OGRE_STATE::FINISH;
}

void CDaruma_FallDownGimmick::Finish()//�߂�
{
	if (m_Object->GetRotation().y >= 5)
	{
		m_Object->SetRotation(m_Transform.rotation);
		m_Transform.rotation.y -= m_TurnSpeed;
	}
	else
	{
		m_WaitTime = 1;
		m_Timer.SetUp(m_ReadyTime);
		m_OgreState = OGRE_STATE::READY;
	}
}

void CDaruma_FallDownGimmick::Feint()
{
	m_TurnAngle = 90;
	m_ReadyTime = 0.5f;
	m_WaitTime = 0.4f;
}

void CDaruma_FallDownGimmick::Fast()
{
	m_TurnAngle = 180;
}

void CDaruma_FallDownGimmick::Slow()
{
	m_TurnAngle = 180;
	vivid::controller::GetAnalogStickLeft;
}


