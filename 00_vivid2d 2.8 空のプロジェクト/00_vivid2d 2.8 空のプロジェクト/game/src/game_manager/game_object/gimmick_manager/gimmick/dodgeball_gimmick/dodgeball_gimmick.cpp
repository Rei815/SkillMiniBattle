#include "dodgeball_gimmick.h"
#include "..\..\..\object_manager\object_manager.h"
#include "..\..\..\bullet_manager\bullet_manager.h"
#include "../../../effect_manager/effect_manager.h"

const std::string	CDodgeBallGimmick::m_file_name = "data\\Models\\cannon_test.mv1";
const CVector3		CDodgeBallGimmick::m_spawn_pos = CVector3(0.0f, -1000.0f, 0.0f);
const float			CDodgeBallGimmick::m_spawn_time = 2.0f;
const float			CDodgeBallGimmick::m_max_rotate_angle = 20.0f;
const float			CDodgeBallGimmick::m_rotate_time = 4.0f;
const float			CDodgeBallGimmick::m_min_rotate_time = m_rotate_time / 4.0f;

CDodgeBallGimmick::CDodgeBallGimmick()
	: CGimmick()
	, m_SetTransform()
	, m_NowState(CANNON_STATE::SPAWN)
	, m_NowRotate(CANNON_ROTATE::RIGHT_GO)
	, m_Shot()
{
}

CDodgeBallGimmick::~CDodgeBallGimmick(void)
{
}

void CDodgeBallGimmick::Initialize(IObject* object)
{
	CGimmick::Initialize(object, m_spawn_time);
	m_Object->SetGimmick(this);

	m_NowState = CANNON_STATE::SPAWN;


	//�C�̍ŏI�ʒu��Transform�������ŃZ�b�g
	m_SetTransform.position = m_Object->GetPosition();
	m_SetTransform.rotation = m_Object->GetRotation();

	//�C�̌��݈ʒu��Transform���X�|�[���ʒu�ŃZ�b�g
	m_Object->SetPosition(m_SetTransform.position + m_spawn_pos);

	m_Shot = CLauncher::GetInstance().Create(SHOT_ID::DODGE_BALL);
}

void CDodgeBallGimmick::Initialize(IObject* object, float time)
{
	CGimmick::Initialize(object, time);
	m_Object->SetGimmick(this);

	m_NowState = CANNON_STATE::SPAWN;


	//�C�̍ŏI�ʒu��Transform�������ŃZ�b�g
	m_SetTransform.position = m_Object->GetPosition();
	m_SetTransform.rotation = m_Object->GetRotation();

	//�C�̌��݈ʒu��Transform���X�|�[���ʒu�ŃZ�b�g
	m_Object->SetPosition(m_SetTransform.position + m_spawn_pos);
}

void CDodgeBallGimmick::Update(void)
{
	CGimmick::Update();

	switch (m_NowState)
	{
	case CANNON_STATE::SPAWN:

		//�o�����o�̎��Ԃ��o�߂����ꍇ
		if (m_Timer.Finished())
		{
			//��Ԃ�MOVE�ɕύX
			m_NowState = CANNON_STATE::MOVE;

			//�^�C�}�[����]�p�ɃZ�b�g���Ȃ���
			m_Timer.SetUp(m_min_rotate_time);

			//���W���Z�b�g
			m_Object->SetPosition(m_SetTransform.position);
		}
		//�o�����o�̎��Ԃ��o�߂��Ă��Ȃ��i�o�����o�̓r���j�ꍇ
		else
		{
			//���W���ړ�
			float TempMove = 1.0f - (m_Timer.GetTimer() / m_spawn_time);
			m_Object->SetPosition(m_SetTransform.position + (m_spawn_pos * TempMove));
		}
		break;

	case CANNON_STATE::MOVE:
	{
		//�p�x�����p�̃��[�J���ϐ�
		CVector3 TempRotation;

		//��]�̃Z�b�g
		switch (m_NowRotate)
		{
		case CANNON_ROTATE::LEFT_RETURN:	//�����O
			TempRotation.y = m_SetTransform.rotation.y - m_max_rotate_angle * ((m_min_rotate_time - m_Timer.GetTimer()) / m_min_rotate_time);
			break;

		case CANNON_ROTATE::RIGHT_GO:		//�O���E
			TempRotation.y = m_SetTransform.rotation.y + m_max_rotate_angle * (m_Timer.GetTimer() / m_min_rotate_time);
			break;

		case CANNON_ROTATE::RIGHT_RETURN:	//�E���O
			TempRotation.y = m_SetTransform.rotation.y + m_max_rotate_angle * ((m_min_rotate_time - m_Timer.GetTimer()) / m_min_rotate_time);
			break;

		case CANNON_ROTATE::LEFT_GO:		//�O����
			TempRotation.y = m_SetTransform.rotation.y - m_max_rotate_angle * (m_Timer.GetTimer() / m_min_rotate_time);
			break;
		}


		if (m_Timer.Finished())
		{
			//�^�C�}�[���Z�b�g
			m_Timer.Reset();

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
		m_Object->SetRotation(TempRotation);

		//�C�̔���
		if (m_Switch)
		{
			m_Switch = false;

			//���ˍ��W����є��˕����̎擾
			CVector3 ShotPos = m_Object->GetPosition();
			CVector3 ShotDir = m_Object->GetTransform().GetForwardVector();

			//���ˍ��W�̒���
			ShotPos += ShotDir.Normalize() * 20.0f;

			//���ˁi�e�̐����j
			m_Shot->Shot(UNIT_CATEGORY::ENEMY, ShotPos, ShotDir);
		}
	}
		break;

	case CANNON_STATE::STOP:
		break;
	}
}

void CDodgeBallGimmick::Draw(void)
{
	CGimmick::Draw();
}

void CDodgeBallGimmick::Finalize(void)
{
	CGimmick::Finalize();
}


CANNON_STATE CDodgeBallGimmick::GetNowState()
{
	return m_NowState;
}

bool CDodgeBallGimmick::GetShotFlag()
{
	return m_Shot->GetShotFlag();
}