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


	//砲の最終位置のTransformを引数でセット
	m_SetTransform.position = Pos;
	m_SetTransform.rotation = Rot;

	//砲の現在位置のTransformをスポーン位置でセット
	m_Object->SetPosition(Pos + m_spawn_pos);
	//m_Transform.rotation = Rot;
}

void CDodgeBallGimmick::Update(void)
{
	CGimmick::Update();

	switch (m_NowState)
	{
	case CANNON_STATE::SPAWN:

		//座標移動（スポーン後の出現演出）
		//m_Transform.position -= CVector3(m_spawn_pos.x / (float)m_spawn_time, m_spawn_pos.y / (float)m_spawn_time, m_spawn_pos.z / (float)m_spawn_time);

		//出現演出の時間が経過した場合
		if (m_Timer.Finished())
		{
			//状態をMOVEに変更
			m_NowState = CANNON_STATE::MOVE;

			//タイマーを回転用にセットしなおす
			m_Timer.SetUp(m_min_rotate_time);

			//座標をセット
			//m_Transform.position = m_SetTransform.position;
		}
		break;

	case CANNON_STATE::MOVE:

		switch (m_NowRotate)
		{
			//右回転
		case CANNON_ROTATE::LEFT_RETURN:
		case CANNON_ROTATE::RIGHT_GO:
			//m_Transform.rotation.y = m_max_rotate_angle * (m_Timer.GetTimer() / m_min_rotate_time);
			break;

			//左回転
		case CANNON_ROTATE::RIGHT_RETURN:
		case CANNON_ROTATE::LEFT_GO:
			//m_Transform.rotation.y = -m_max_rotate_angle * (m_Timer.GetTimer() / m_min_rotate_time);
			break;
		}


		if (m_Timer.Finished())
		{
			//タイマーリセット
			m_Timer.Reset();

			//回転状態を次の段階に変更
			int Temp = (int)m_NowRotate;
			Temp++;
			if (Temp > (int)CANNON_ROTATE::LEFT_RETURN)
				Temp = (int)CANNON_ROTATE::RIGHT_GO;
			m_NowRotate = (CANNON_ROTATE)Temp;

			//角度のずれが発生した場合に修正されるように、現在の回転状態に合わせて調整する
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