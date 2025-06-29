#include "dodgeball_gimmick.h"
#include "..\..\..\object_manager\object_manager.h"
#include "..\..\..\bullet_manager\bullet_manager.h"
#include "../../../effect_manager/effect_manager.h"

const CVector3		CDodgeBallGimmick::m_spawn_pos = CVector3(0.0f, -1000.0f, 0.0f);
const float			CDodgeBallGimmick::m_spawn_time = 2.0f;
const float			CDodgeBallGimmick::m_max_rotate_angle = 20.0f;
const float			CDodgeBallGimmick::m_rotate_time = 4.0f;
const float			CDodgeBallGimmick::m_min_rotate_time = m_rotate_time / 4.0f;
const float			CDodgeBallGimmick::m_shot_time = 0.5f;
const float	        CDodgeBallGimmick::m_effect_speed = 15000.0f;

CDodgeBallGimmick::CDodgeBallGimmick()
	: CGimmick()
	, m_SetTransform()
	, m_NowState(CANNON_STATE::SPAWN)
	, m_NowRotate(CANNON_ROTATE::RIGHT_GO)
	, m_Shot()
	, m_MoveTimer()
	, m_ShotTimer()
	, m_Effect(nullptr)
{
}

CDodgeBallGimmick::~CDodgeBallGimmick(void)
{
}

void CDodgeBallGimmick::Initialize(std::shared_ptr<IObject> object)
{
	CGimmick::Initialize(object, m_spawn_time);
	m_Object->SetGimmick(shared_from_this());

	m_NowState = CANNON_STATE::SPAWN;

	m_MoveTimer.SetUp(m_min_rotate_time);
	m_ShotTimer.SetUp(m_shot_time);


	//砲の最終位置のTransformを引数でセット
	m_SetTransform.position = m_Object->GetPosition();
	m_SetTransform.rotation = m_Object->GetRotation();

	//砲の現在位置のTransformをスポーン位置でセット
	m_Object->SetPosition(m_SetTransform.position + m_spawn_pos);

	m_Shot = CLauncher::GetInstance().Create(SHOT_ID::DODGE_BALL);
}

void CDodgeBallGimmick::Initialize(std::shared_ptr<IObject> object, float time)
{
	CGimmick::Initialize(object, time);
	m_Object->SetGimmick(shared_from_this());

	m_NowState = CANNON_STATE::SPAWN;

	m_MoveTimer.SetUp(m_min_rotate_time);
	m_ShotTimer.SetUp(m_shot_time);


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
	CGimmick::Draw();
}

void CDodgeBallGimmick::Finalize(void)
{
	CGimmick::Finalize();

	if (m_Effect != nullptr)
		m_Effect->Delete(false);
}

void CDodgeBallGimmick::Spawn()
{
	//出現演出の時間が経過した場合
	if (m_Timer.Finished())
	{
		//状態をMOVEに変更
		m_NowState = CANNON_STATE::MOVE;

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
}

void CDodgeBallGimmick::Move()
{
	m_MoveTimer.Update();

	//角度調整用のローカル変数
	CVector3 TempRotation;

	//回転のセット
	switch (m_NowRotate)
	{
	case CANNON_ROTATE::LEFT_RETURN:	//左→前
		TempRotation.y = m_SetTransform.rotation.y - m_max_rotate_angle * ((m_min_rotate_time - m_MoveTimer.GetTimer()) / m_min_rotate_time);
		break;

	case CANNON_ROTATE::RIGHT_GO:		//前→右
		TempRotation.y = m_SetTransform.rotation.y + m_max_rotate_angle * (m_MoveTimer.GetTimer() / m_min_rotate_time);
		break;

	case CANNON_ROTATE::RIGHT_RETURN:	//右→前
		TempRotation.y = m_SetTransform.rotation.y + m_max_rotate_angle * ((m_min_rotate_time - m_MoveTimer.GetTimer()) / m_min_rotate_time);
		break;

	case CANNON_ROTATE::LEFT_GO:		//前→左
		TempRotation.y = m_SetTransform.rotation.y - m_max_rotate_angle * (m_MoveTimer.GetTimer() / m_min_rotate_time);
		break;
	}


	if (m_MoveTimer.Finished())
	{
		//タイマーリセット
		m_MoveTimer.Reset();

		//回転状態を次の段階に変更
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
	if (m_OperationFlag)
	{
		m_OperationFlag = false;

		//回転の角度をラジアンに変換する
		TempRotation = CVector3(DEG_TO_RAD(TempRotation.x), DEG_TO_RAD(TempRotation.y), DEG_TO_RAD(TempRotation.z));

		m_Effect = CEffectManager::GetInstance().Create(EFFECT_ID::FORECAST_LINE, m_Object->GetPosition(), TempRotation);
		m_NowState = CANNON_STATE::SHOT;
	}
}

void CDodgeBallGimmick::Shot()
{
	m_ShotTimer.Update();

	if (m_Effect != nullptr)
		m_Effect->SetPosition(m_Object->GetPosition() + m_Object->GetTransform().GetForwardVector() * m_effect_speed * m_ShotTimer.GetTimer());

	if (m_ShotTimer.Finished())
	{
		//発射座標および発射方向の取得
		CVector3 ShotPos = m_Object->GetPosition();
		CVector3 ShotDir = m_Object->GetTransform().GetForwardVector();

		//発射座標の調整
		ShotPos += ShotDir.Normalize() * 20.0f;

		//発射（弾の生成）
		m_Shot->Shot(UNIT_CATEGORY::ENEMY, ShotPos, ShotDir);

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