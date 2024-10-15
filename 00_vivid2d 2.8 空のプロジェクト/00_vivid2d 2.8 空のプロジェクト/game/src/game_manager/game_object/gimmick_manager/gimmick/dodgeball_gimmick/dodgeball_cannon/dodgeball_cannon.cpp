#include "dodgeball_cannon.h"

const std::string	CDodgeBallCannon::m_file_name			= "data\\Models\\cannon_test.mv1";
const CVector3		CDodgeBallCannon::m_spawn_pos			= CVector3(0.0f,-10.0f,0.0f);
const int			CDodgeBallCannon::m_spawn_time			= 120;
const float         CDodgeBallCannon::m_max_rotate_angle	= 30.0f;
const int           CDodgeBallCannon::m_rotate_time			= 120;


CDodgeBallCannon::CDodgeBallCannon()
	: m_Model()
	, m_Transform()
	, m_SetTransform()
	, m_NowState(CANNON_STATE::SPAWN)
	, m_SpawnTimer(0)
	, m_NowRotate(CANNON_ROTATE::RIGHT_GO)
	, m_MinRotateTime(m_rotate_time / 4)
	, m_RotateTimer(0)
{
}

CDodgeBallCannon::~CDodgeBallCannon()
{
}

void CDodgeBallCannon::Initialize(CVector3 Pos, CVector3 Rot)
{
	m_NowState = CANNON_STATE::SPAWN;
	

	//�C�̍ŏI�ʒu��Transform�������ŃZ�b�g
	m_SetTransform.position = Pos;
	m_SetTransform.rotation = Rot;

	//�C�̌��݈ʒu��Transform���X�|�[���ʒu�ŃZ�b�g
	m_Transform.position = Pos + m_spawn_pos;
	m_Transform.rotation = Rot;

	//���f���̏�����
	m_Model.Initialize(m_file_name, m_Transform.position);
}

void CDodgeBallCannon::Update(void)
{
	switch (m_NowState)
	{
	case CANNON_STATE::SPAWN:
		//�^�C�}�[���Z
		m_SpawnTimer++;

		//���W�ړ��i�X�|�[����̏o�����o�j
		m_Transform.position -= CVector3(m_spawn_pos.x / (float)m_spawn_time, m_spawn_pos.y / (float)m_spawn_time, m_spawn_pos.z / (float)m_spawn_time);

		//�o�����o�̎��Ԃ��o�߂����ꍇ
		if (m_SpawnTimer >= m_spawn_time)
		{
			//��Ԃ�MOVE�ɕύX
			m_NowState = CANNON_STATE::MOVE;

			//���W���Z�b�g
			m_Transform.position = m_SetTransform.position;
		}
		break;

	case CANNON_STATE::MOVE:
		//�^�C�}�[���Z
		m_RotateTimer++;

		switch (m_NowRotate)
		{
		//�E��]
		case CANNON_ROTATE::LEFT_RETURN:
		case CANNON_ROTATE::RIGHT_GO:
			m_Transform.rotation.y += m_max_rotate_angle / (float)m_MinRotateTime;
			break;

		//����]
		case CANNON_ROTATE::RIGHT_RETURN:
		case CANNON_ROTATE::LEFT_GO:
			m_Transform.rotation.y -= m_max_rotate_angle / (float)m_MinRotateTime;
			break;
		}


		if (m_RotateTimer > m_rotate_time / 4)
		{
			//�^�C�}�[���Z�b�g
			m_RotateTimer = 0;

			//��]��Ԃ����̒i�K�ɕύX
			int Temp = (int)m_NowRotate;
			Temp++;
			if (Temp > (int)CANNON_ROTATE::LEFT_RETURN)
				Temp = (int)CANNON_ROTATE::RIGHT_GO;
			m_NowRotate = (CANNON_ROTATE)Temp;
		}
		break;

	case CANNON_STATE::STOP:
		break;
	}

	//���f���̍X�V
	m_Model.Update(m_Transform);
}

void CDodgeBallCannon::Draw(void)
{
	//���f���̕`��
	m_Model.Draw();
}

void CDodgeBallCannon::Finalize(void)
{
	//���f���̉��
	m_Model.Finalize();
}

void CDodgeBallCannon::Shot(void)
{

}
