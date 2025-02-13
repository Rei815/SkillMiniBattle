#include "belt_conveyor_gimmick.h"
#include "..\..\..\object_manager\object_manager.h"
#include "..\..\..\effect_manager\effect_manager.h"
#include "..\..\..\unit_manager\unit_manager.h"

const float			CBeltConveyorGimmick::m_mid_belt_speed_time = 180.0f;

const float			CBeltConveyorGimmick::m_min_belt_speed_rate =  5.0f;
const float			CBeltConveyorGimmick::m_mid_belt_speed_rate = 10.0f;
const float			CBeltConveyorGimmick::m_max_belt_speed_rate = 20.0f;

CBeltConveyorGimmick::CBeltConveyorGimmick()
	: CGimmick()
	, m_PlayerMoveSpeed(CPlayer::m_move_speed)
	, m_NowBeltSpeedRate(0.0f)
	, m_BeltConveyorForward(CVector3::FORWARD)
{
}

CBeltConveyorGimmick::~CBeltConveyorGimmick(void)
{
}

void CBeltConveyorGimmick::Initialize(IObject* object)
{
	Initialize(object, m_mid_belt_speed_time);
}

void CBeltConveyorGimmick::Initialize(IObject* object, float time)
{
	CGimmick::Initialize(object, time);

	m_Object->SetGimmick(this);
	m_BeltConveyorForward = m_Object->GetTransform().GetForwardVector();

	m_PlayerMoveSpeed = CPlayer::m_move_speed;
	m_NowBeltSpeedRate = m_min_belt_speed_rate;
	m_Timer.SetUp(m_mid_belt_speed_time);
}

void CBeltConveyorGimmick::Update(void)
{
	CGimmick::Update();

	//ベルトコンベアの速度更新
	m_NowBeltSpeedRate = m_min_belt_speed_rate + (m_mid_belt_speed_rate - m_min_belt_speed_rate) * m_Timer.GetTimer() / m_mid_belt_speed_time;
	if (m_NowBeltSpeedRate > m_max_belt_speed_rate)
		m_NowBeltSpeedRate = m_max_belt_speed_rate;

	//プレイヤーの移動（ベルトコンベアの影響）
	CUnitManager::UNIT_LIST unitList = CUnitManager::GetInstance().GetUnitList();
	CUnitManager::UNIT_LIST::iterator it = unitList.begin();
	
	while (it != unitList.end())
	{
		IUnit* unit = (*it);
		++it;

		//敗北状態ならスキップ
		if (unit->GetDefeatFlag())
			continue;

		//空中ならスキップ
		if (!unit->GetIsGround())
			continue;

		unit->SetPosition(unit->GetPosition() + m_BeltConveyorForward * (m_PlayerMoveSpeed * m_NowBeltSpeedRate));
	}
}

void CBeltConveyorGimmick::Draw(void)
{
	CGimmick::Draw();


}

void CBeltConveyorGimmick::Finalize(void)
{
	CGimmick::Finalize();


}
