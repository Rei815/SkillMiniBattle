#include "daruma_fall_down_gimmick.h"
#include <stdlib.h> rand(), srand()
#include "../../../../../engine/components/transform_component/transform_component.h"

const float CDarumaFallDownGimmick::m_default_ready_time = 2.0f;
const float CDarumaFallDownGimmick::m_default_wait_time = 1.0f;
const float CDarumaFallDownGimmick::m_default_turn_angle = 180.0f;

const float CDarumaFallDownGimmick::m_feint_ready_time = 0.5f;
const float CDarumaFallDownGimmick::m_feint_wait_time = 0.4f;
const float CDarumaFallDownGimmick::m_feint_turn_angle = 90.0f;

const float CDarumaFallDownGimmick::m_turn_speed = 15.0f;

CDarumaFallDownGimmick::CDarumaFallDownGimmick()
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

CDarumaFallDownGimmick::~CDarumaFallDownGimmick(void)
{
}
void CDarumaFallDownGimmick::Initialize(CGameObject* object)
{
}

void CDarumaFallDownGimmick::Update(void)
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

void CDarumaFallDownGimmick::Draw(void)
{
}

void CDarumaFallDownGimmick::Finalize(void)
{
}


void CDarumaFallDownGimmick::Ready()//振り返り方の設定
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

void CDarumaFallDownGimmick::Play()//振り返る
{
	//少しだけ振り返る
	if (m_Object->GetComponent<TransformComponent>()->GetRotation().y < 40)
	{
		m_Transform.rotation.y += m_turn_speed;

		if (40 <= m_Transform.rotation.y)

			m_Transform.rotation.y = 40;

		m_Object->GetComponent<TransformComponent>()->SetRotation(m_Transform.rotation);
	}

	//時間が経過したらキャラクターの方を見る
	if (m_Timer.Finished())
	{
		if (m_Object->GetComponent<TransformComponent>()->GetRotation().y < m_TurnAngle)
		{
			m_Transform.rotation.y += m_turn_speed;

			if (m_TurnAngle <= m_Transform.rotation.y)
				m_Transform.rotation.y = m_TurnAngle;

			m_Object->GetComponent<TransformComponent>()->SetRotation(m_Transform.rotation);
		}
		else
		{
			m_ReadyTime = m_default_ready_time;
			m_Timer.SetUp(m_WaitTime);
			m_OgreState = OGRE_STATE::WAIT;
		}
	}
}

void CDarumaFallDownGimmick::Wait()//振り返った状態で待機
{
	if (m_Timer.Finished())
	{
		m_OgreState = OGRE_STATE::FINISH;
	}
}

void CDarumaFallDownGimmick::Finish()//戻る
{
	if (m_Object->GetComponent<TransformComponent>()->GetRotation().y >= 5)
	{
		m_Object->GetComponent<TransformComponent>()->SetRotation(m_Transform.rotation);
		m_Transform.rotation.y -= m_turn_speed;
	}
	else
	{
		//フェイントだったら後ろを向いた後50%で振り返る
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
		}
	}
}

void CDarumaFallDownGimmick::Feint()//フェイントの設定
{
	m_TurnAngle = m_feint_turn_angle;
	m_ReadyTime = m_feint_ready_time;
	m_WaitTime = m_feint_wait_time;
}


void CDarumaFallDownGimmick::OgreControlTurn()//スキル、鬼操作を使ったときの処理
{
	m_Timer.SetUp(0.0f);
	m_TurnAngle = m_default_turn_angle;
	m_OgreState = OGRE_STATE::PLAY;
}
