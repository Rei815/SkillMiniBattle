#include "dodgeball_gimmick.h"
#include "..\..\..\object_manager\object_manager.h"

const std::string	CDodgeBallGimmick::m_file_name = "data\\Models\\cannon_test.mv1";
const CVector3		CDodgeBallGimmick::m_spawn_pos = CVector3(0.0f, -1000.0f, 0.0f);
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

void CDodgeBallGimmick::Initialize(IObject* object)
{
	CGimmick::Initialize(object, m_spawn_time);
	m_Object->SetGimmick(this);

	m_NowState = CANNON_STATE::SPAWN;


	//砲の最終位置のTransformを引数でセット
	m_SetTransform.position = m_Object->GetPosition();
	m_SetTransform.rotation = m_Object->GetRotation();

	//砲の現在位置のTransformをスポーン位置でセット
	m_Object->SetPosition(m_SetTransform.position + m_spawn_pos);
}

void CDodgeBallGimmick::Initialize(IObject* object, float time)
{
	CGimmick::Initialize(object, time);
	m_Object->SetGimmick(this);

	m_NowState = CANNON_STATE::SPAWN;


	//砲の最終位置のTransformを引数でセット
	m_SetTransform.position = m_Object->GetPosition();
	m_SetTransform.rotation = m_Object->GetRotation();

	//砲の現在位置のTransformをスポーン位置でセット
	m_Object->SetPosition(m_SetTransform.position + m_spawn_pos);
}

void CDodgeBallGimmick::Update(void)
{
	CGimmick::Update();

	switch (m_NowState)
	{
	case CANNON_STATE::SPAWN:

		//出現演出の時間が経過した場合
		if (m_Timer.Finished())
		{
			//状態をMOVEに変更
			m_NowState = CANNON_STATE::MOVE;

			//タイマーを回転用にセットしなおす
			m_Timer.SetUp(m_min_rotate_time);

			//座標をセット
			m_Object->SetPosition(m_SetTransform.position);
		}
		//出現演出の時間が経過していない（出現演出の途中）場合
		else
		{
			//座標を移動
			float TempMove = 1.0f - (m_Timer.GetTimer() / m_spawn_time);
			m_Object->SetPosition(m_SetTransform.position + (m_spawn_pos * TempMove));
		}
		break;

	case CANNON_STATE::MOVE:
	{
		//角度調整用のローカル変数
		CVector3 TempRotation;

		//回転のセット
		switch (m_NowRotate)
		{
			//右回転
		case CANNON_ROTATE::LEFT_RETURN:
		case CANNON_ROTATE::RIGHT_GO:
			TempRotation.y = m_SetTransform.rotation.y + m_max_rotate_angle * (m_Timer.GetTimer() / m_min_rotate_time);
			break;

			//左回転
		case CANNON_ROTATE::RIGHT_RETURN:
		case CANNON_ROTATE::LEFT_GO:
			TempRotation.y = m_SetTransform.rotation.y - m_max_rotate_angle * (m_Timer.GetTimer() / m_min_rotate_time);
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

			//角度にずれが発生しないように、現在の回転状態に合わせて修正する
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

		//オブジェクトの回転
		m_Object->SetRotation(TempRotation);

		//砲の発射
		if (m_Switch)
		{
			m_Switch = false;
			Shot();
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

void CDodgeBallGimmick::Shot(void)
{

}