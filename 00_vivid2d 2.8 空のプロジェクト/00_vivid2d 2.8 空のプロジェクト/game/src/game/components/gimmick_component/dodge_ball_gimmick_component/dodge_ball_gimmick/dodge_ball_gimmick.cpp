#include "dodge_ball_gimmick.h"
#include "../../../../../engine/components/transform_component/transform_component.h"
#include "../../../../../engine/managers/effect_manager/effect_manager.h"
#include "../../../../../engine/managers/launcher/launcher.h"
const CVector3		CDodgeBallGimmick::m_spawn_pos = CVector3(0.0f, -1000.0f, 0.0f);
const float			CDodgeBallGimmick::m_spawn_time = 2.0f;
const float			CDodgeBallGimmick::m_max_rotate_angle = 20.0f;
const float			CDodgeBallGimmick::m_rotate_time = 4.0f;
const float			CDodgeBallGimmick::m_min_rotate_time = m_rotate_time / 4.0f;
const float			CDodgeBallGimmick::m_shot_time = 0.5f;
const float	        CDodgeBallGimmick::m_effect_speed = 15000.0f;

CDodgeBallGimmick::CDodgeBallGimmick()
	: m_SetTransform()
	, m_NowState(CANNON_STATE::SPAWN)
	, m_NowRotate(CANNON_ROTATE::RIGHT_GO)
	, m_Shot()
	, m_MoveTimer()
	, m_ShotTimer()
	, m_Effect(nullptr)
	, m_OperationFlag(false)
{
}

CDodgeBallGimmick::~CDodgeBallGimmick(void)
{
}

void CDodgeBallGimmick::Initialize(CGameObject* object)
{
	m_Object = object;
	m_Timer.SetUp(m_spawn_time);

	m_NowState = CANNON_STATE::SPAWN;

	m_MoveTimer.SetUp(m_min_rotate_time);
	m_ShotTimer.SetUp(m_shot_time);


	//�C�̍ŏI�ʒu��Transform�������ŃZ�b�g
	m_SetTransform.position = m_Object->GetComponent<TransformComponent>()->GetPosition();
	m_SetTransform.rotation = m_Object->GetComponent<TransformComponent>()->GetRotation();

	//�C�̌��݈ʒu��Transform���X�|�[���ʒu�ŃZ�b�g
	m_Object->GetComponent<TransformComponent>()->SetPosition(m_SetTransform.position + m_spawn_pos);

	m_Shot = CLauncher::GetInstance().Create(SHOT_ID::DODGE_BALL);
}

void CDodgeBallGimmick::Update(void)
{
	m_Timer.Update();
	switch (m_NowState)
	{
	case CANNON_STATE::SPAWN:
		Spawn();
		break;

	case CANNON_STATE::MOVE:
		Move();
		break;

	case CANNON_STATE::SHOT:
		Shot();
		break;

	case CANNON_STATE::STOP:
		Stop();
		break;
	}
}

void CDodgeBallGimmick::Draw(void)
{
}

void CDodgeBallGimmick::Finalize(void)
{
	if (m_Effect != nullptr)
		m_Effect->Delete();
}

void CDodgeBallGimmick::Spawn()
{
	//�o�����o�̎��Ԃ��o�߂����ꍇ
	if (m_Timer.Finished())
	{
		//��Ԃ�MOVE�ɕύX
		m_NowState = CANNON_STATE::MOVE;

		//���W���Z�b�g
		m_Object->GetComponent<TransformComponent>()->SetPosition(m_SetTransform.position);
	}
	//�o�����o�̎��Ԃ��o�߂��Ă��Ȃ��i�o�����o�̓r���j�ꍇ
	else
	{
		//���W���ړ�
		float TempMove = 1.0f - (m_Timer.GetTimer() / m_spawn_time);
		m_Object->GetComponent<TransformComponent>()->SetPosition(m_SetTransform.position + (m_spawn_pos * TempMove));
	}
}

void CDodgeBallGimmick::Move()
{
	m_MoveTimer.Update();

	//�p�x�����p�̃��[�J���ϐ�
	CVector3 TempRotation;

	//��]�̃Z�b�g
	switch (m_NowRotate)
	{
	case CANNON_ROTATE::LEFT_RETURN:	//�����O
		TempRotation.y = m_SetTransform.rotation.y - m_max_rotate_angle * ((m_min_rotate_time - m_MoveTimer.GetTimer()) / m_min_rotate_time);
		break;

	case CANNON_ROTATE::RIGHT_GO:		//�O���E
		TempRotation.y = m_SetTransform.rotation.y + m_max_rotate_angle * (m_MoveTimer.GetTimer() / m_min_rotate_time);
		break;

	case CANNON_ROTATE::RIGHT_RETURN:	//�E���O
		TempRotation.y = m_SetTransform.rotation.y + m_max_rotate_angle * ((m_min_rotate_time - m_MoveTimer.GetTimer()) / m_min_rotate_time);
		break;

	case CANNON_ROTATE::LEFT_GO:		//�O����
		TempRotation.y = m_SetTransform.rotation.y - m_max_rotate_angle * (m_MoveTimer.GetTimer() / m_min_rotate_time);
		break;
	}


	if (m_MoveTimer.Finished())
	{
		//�^�C�}�[���Z�b�g
		m_MoveTimer.Reset();

		//��]��Ԃ����̒i�K�ɕύX
		switch (m_NowRotate)
		{
		case CANNON_ROTATE::RIGHT_GO:
			m_NowRotate = CANNON_ROTATE::RIGHT_RETURN;
			break;
		case CANNON_ROTATE::RIGHT_RETURN:
			m_NowRotate = CANNON_ROTATE::LEFT_GO;
			break;
		case CANNON_ROTATE::LEFT_GO:
			m_NowRotate = CANNON_ROTATE::LEFT_RETURN;
			break;
		case CANNON_ROTATE::LEFT_RETURN:
			m_NowRotate = CANNON_ROTATE::RIGHT_GO;
			break;
		}

		//�p�x�ɂ��ꂪ�������Ȃ��悤�ɁA���݂̉�]��Ԃɍ��킹�ďC������
		switch (m_NowRotate)
		{
		case CANNON_ROTATE::RIGHT_GO:
		case CANNON_ROTATE::LEFT_GO:
			TempRotation.y = m_SetTransform.rotation.y;
			break;
		case CANNON_ROTATE::RIGHT_RETURN:
			TempRotation.y = m_SetTransform.rotation.y + m_max_rotate_angle;
			break;
		case CANNON_ROTATE::LEFT_RETURN:
			TempRotation.y = m_SetTransform.rotation.y - m_max_rotate_angle;
			break;
		}
	}

	//�I�u�W�F�N�g�̉�]
	m_Object->GetComponent<TransformComponent>()->SetRotation(TempRotation);

	//�C�̔���
	if (m_OperationFlag)
	{
		m_OperationFlag = false;

		//��]�̊p�x�����W�A���ɕϊ�����
		TempRotation = CVector3(DEG_TO_RAD(TempRotation.x), DEG_TO_RAD(TempRotation.y), DEG_TO_RAD(TempRotation.z));

		m_Effect = CEffectManager::GetInstance().Create(EFFECT_ID::FORECAST_LINE, m_Object->GetComponent<TransformComponent>()->GetPosition(), TempRotation);
		m_NowState = CANNON_STATE::SHOT;
	}
}

void CDodgeBallGimmick::Shot()
{
	m_ShotTimer.Update();

	if (m_Effect != nullptr)
		m_Effect->SetPosition(m_Object->GetComponent<TransformComponent>()->GetPosition() + m_Object->GetComponent<TransformComponent>()->GetTransform().GetForwardVector() * m_effect_speed * m_ShotTimer.GetTimer());

	if (m_ShotTimer.Finished())
	{
		//���ˍ��W����є��˕����̎擾
		CVector3 ShotPos = m_Object->GetComponent<TransformComponent>()->GetPosition();
		CVector3 ShotDir = m_Object->GetComponent<TransformComponent>()->GetTransform().GetForwardVector();

		//���ˍ��W�̒���
		ShotPos += ShotDir.Normalize() * 20.0f;

		//���ˁi�e�̐����j
		m_Shot->Shot(FACTION_CATEGORY::ENEMY, ShotPos, ShotDir);

		m_ShotTimer.Reset();
		m_NowState = CANNON_STATE::MOVE;
	}

}

void CDodgeBallGimmick::Stop()
{

}

CANNON_STATE CDodgeBallGimmick::GetNowState()
{
	return m_NowState;
}

bool CDodgeBallGimmick::GetShotFlag()
{
	return m_Shot->GetShotFlag();
}

bool CDodgeBallGimmick::GetOperatingFlag()
{
	return m_OperationFlag;
}

void CDodgeBallGimmick::SetOperationFlag(bool flag)
{
	m_OperationFlag = flag;
}
