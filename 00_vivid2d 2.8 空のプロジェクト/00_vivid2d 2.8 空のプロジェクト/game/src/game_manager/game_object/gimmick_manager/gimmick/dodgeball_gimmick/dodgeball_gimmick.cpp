#include "dodgeball_gimmick.h"
#include "..\..\..\object_manager\object_manager.h"

const std::string	CDodgeBallGimmick::m_file_name = "data\\Models\\cannon_test.mv1";
const CVector3		CDodgeBallGimmick::m_spawn_pos = CVector3(0.0f, -10.0f, 0.0f);
const float			CDodgeBallGimmick::m_spawn_time = 2.0f;
const float			CDodgeBallGimmick::m_max_rotate_angle = 30.0f;
const float			CDodgeBallGimmick::m_rotate_time = 4.0f;
const float			CDodgeBallGimmick::m_min_rotate_time = m_rotate_time / 4.0f;

CDodgeBallGimmick::CDodgeBallGimmick()
	: CGimmick()
	, m_SetTransform()
	, m_NowState(CANNON_STATE::SPAWN)
	, m_NowRotate(CANNON_ROTATE::RIGHT_GO)
{
}

CDodgeBallGimmick::~CDodgeBallGimmick(void)
{
}

void CDodgeBallGimmick::Initialize(CVector3 Pos, CVector3 Rot, IObject* object)
{
	CGimmick::Initialize(object, m_spawn_time);
	m_Object->SetGimmick(this);

	m_NowState = CANNON_STATE::SPAWN;


	//�C�̍ŏI�ʒu��Transform�������ŃZ�b�g
	m_SetTransform.position = Pos;
	m_SetTransform.rotation = Rot;

	//�C�̌��݈ʒu��Transform���X�|�[���ʒu�ŃZ�b�g
	m_Object->SetPosition(Pos + m_spawn_pos);
	//m_Transform.rotation = Rot;
}

void CDodgeBallGimmick::Update(void)
{
	CGimmick::Update();

	switch (m_NowState)
	{
	case CANNON_STATE::SPAWN:

		//���W�ړ��i�X�|�[����̏o�����o�j
		//m_Transform.position -= CVector3(m_spawn_pos.x / (float)m_spawn_time, m_spawn_pos.y / (float)m_spawn_time, m_spawn_pos.z / (float)m_spawn_time);

		//�o�����o�̎��Ԃ��o�߂����ꍇ
		if (m_Timer.Finished())
		{
			//��Ԃ�MOVE�ɕύX
			m_NowState = CANNON_STATE::MOVE;

			//�^�C�}�[����]�p�ɃZ�b�g���Ȃ���
			m_Timer.SetUp(m_min_rotate_time);

			//���W���Z�b�g
			//m_Transform.position = m_SetTransform.position;
		}
		break;

	case CANNON_STATE::MOVE:

		switch (m_NowRotate)
		{
			//�E��]
		case CANNON_ROTATE::LEFT_RETURN:
		case CANNON_ROTATE::RIGHT_GO:
			//m_Transform.rotation.y = m_max_rotate_angle * (m_Timer.GetTimer() / m_min_rotate_time);
			break;

			//����]
		case CANNON_ROTATE::RIGHT_RETURN:
		case CANNON_ROTATE::LEFT_GO:
			//m_Transform.rotation.y = -m_max_rotate_angle * (m_Timer.GetTimer() / m_min_rotate_time);
			break;
		}


		if (m_Timer.Finished())
		{
			//�^�C�}�[���Z�b�g
			m_Timer.Reset();

			//��]��Ԃ����̒i�K�ɕύX
			int Temp = (int)m_NowRotate;
			Temp++;
			if (Temp > (int)CANNON_ROTATE::LEFT_RETURN)
				Temp = (int)CANNON_ROTATE::RIGHT_GO;
			m_NowRotate = (CANNON_ROTATE)Temp;

			//�p�x�̂��ꂪ���������ꍇ�ɏC�������悤�ɁA���݂̉�]��Ԃɍ��킹�Ē�������
			switch (m_NowRotate)
			{
			case CANNON_ROTATE::RIGHT_GO:
			case CANNON_ROTATE::LEFT_GO:
				//m_Transform.rotation.y = 0.0f;
				break;
			case CANNON_ROTATE::RIGHT_RETURN:
				//m_Transform.rotation.y = m_max_rotate_angle;
				break;
			case CANNON_ROTATE::LEFT_RETURN:
				//m_Transform.rotation.y = -m_max_rotate_angle;
				break;
			}
		}
		break;

	case CANNON_STATE::STOP:
		break;
	}
}

void CDodgeBallGimmick::Draw(void)
{
}

void CDodgeBallGimmick::Finalize(void)
{
}

void CDodgeBallGimmick::Shot(void)
{
}