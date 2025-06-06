#include "daruma_falldown_gimmick.h"
#include "..\..\..\object_manager\object_manager.h"
#include <stdlib.h> rand(), srand()

	const float CDaruma_FallDownGimmick::m_default_ready_time = 2.0f;
	const float CDaruma_FallDownGimmick::m_default_wait_time = 1.0f;
	const float CDaruma_FallDownGimmick::m_default_turn_angle = 180.0f;

	const float CDaruma_FallDownGimmick::m_feint_ready_time = 0.5f;
	const float CDaruma_FallDownGimmick::m_feint_wait_time = 0.4f;
	const float CDaruma_FallDownGimmick::m_feint_turn_angle = 90.0f;

	const float CDaruma_FallDownGimmick::m_turn_speed = 15.0f;

CDaruma_FallDownGimmick::CDaruma_FallDownGimmick()
	: m_ReadyTime(m_default_ready_time)
	, m_WaitTime(m_default_wait_time)
	, m_RestPlayer(0)
	, m_Transform()
	, m_OgreState(OGRE_STATE::READY)
	, m_TurnType(TURN_TYPE::FAST)
	, m_Timer(3.0f)
	, m_TurnAngle(m_default_turn_angle)
{
}

CDaruma_FallDownGimmick::~CDaruma_FallDownGimmick(void)
{
}
void CDaruma_FallDownGimmick::Initialize(std::shared_ptr<IObject> object)
{
	CGimmick::Initialize(object);
	m_Object->SetGimmick(shared_from_this());
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
}

void CDaruma_FallDownGimmick::Draw(void)
{
}

void CDaruma_FallDownGimmick::Finalize(void)
{
}


void CDaruma_FallDownGimmick::Ready()//�U��Ԃ���̐ݒ�
{
	if (m_Timer.Finished() && m_OgreState == OGRE_STATE::READY)
	{
		m_TurnType = (TURN_TYPE)(rand() % (int)TURN_TYPE::TYPE_NUM);
		switch (m_TurnType)
		{
		case TURN_TYPE::FEINT:
			m_Timer.SetUp(0);
			Feint();
			break;
		case TURN_TYPE::SLOW:
			m_Timer.SetUp(1 + (rand() % 2));
			m_TurnAngle = m_default_turn_angle;
			break;
		case TURN_TYPE::FAST:
			m_Timer.SetUp(0.3 + ((rand() % 7) * 0.1));
			m_TurnAngle = m_default_turn_angle;
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
	//���������U��Ԃ�
	if (m_Object->GetRotation().y < 40)
	{
		m_Transform.rotation.y += m_turn_speed;

		if (40 <= m_Transform.rotation.y)

			m_Transform.rotation.y = 40;

		m_Object->SetRotation(m_Transform.rotation);
	}

	//���Ԃ��o�߂�����L�����N�^�[�̕�������
	if (m_Timer.Finished())
	{
		if (m_Object->GetRotation().y < m_TurnAngle)
		{
			m_Transform.rotation.y += m_turn_speed;

			if (m_TurnAngle <= m_Transform.rotation.y)
				m_Transform.rotation.y = m_TurnAngle;

			m_Object->SetRotation(m_Transform.rotation);
		}
		else
		{
			m_ReadyTime = m_default_ready_time;
			m_Timer.SetUp(m_WaitTime);
			m_OgreState = OGRE_STATE::WAIT;

			if (m_TurnType != TURN_TYPE::FEINT)
				m_State = GIMMICK_STATE::PLAY;
			else
				m_State = GIMMICK_STATE::FINISH;
		}
	}
}

void CDaruma_FallDownGimmick::Wait()//�U��Ԃ�����Ԃőҋ@
{
	if (m_Timer.Finished())
	{
		m_State = GIMMICK_STATE::FINISH;
		m_OgreState = OGRE_STATE::FINISH;
	}
}

void CDaruma_FallDownGimmick::Finish()//�߂�
{
	if (m_Object->GetRotation().y >= 5)
	{
		m_Object->SetRotation(m_Transform.rotation);
		m_Transform.rotation.y -= m_turn_speed;
	}
	else
	{
		//�t�F�C���g�������������������50%�ŐU��Ԃ�
		if (m_TurnType == TURN_TYPE::FEINT && (rand() % 2 == 0))
		{
			m_TurnType = TURN_TYPE::FAST;
			m_TurnAngle = m_default_turn_angle;
			m_Timer.SetUp(0);
			m_OgreState = OGRE_STATE::PLAY;
		}
		else
		{
			m_WaitTime = 1;
			m_Timer.SetUp(m_ReadyTime);
			m_OgreState = OGRE_STATE::READY;
			m_State = GIMMICK_STATE::WAIT;
		}
	}
}

void CDaruma_FallDownGimmick::Feint()//�t�F�C���g�̐ݒ�
{
	m_TurnAngle = m_feint_turn_angle;
	m_ReadyTime = m_feint_ready_time;
	m_WaitTime  = m_feint_wait_time;
}


void CDaruma_FallDownGimmick::OgreControlTurn()//�X�L���A�S������g�����Ƃ��̏���
{
	m_Timer.SetUp(0.0f);
	m_TurnAngle = m_default_turn_angle;
	m_OgreState = OGRE_STATE::PLAY;
}
