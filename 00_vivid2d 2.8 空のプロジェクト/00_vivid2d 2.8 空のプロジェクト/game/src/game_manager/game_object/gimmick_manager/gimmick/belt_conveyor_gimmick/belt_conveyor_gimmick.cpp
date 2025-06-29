#include "belt_conveyor_gimmick.h"
#include "..\..\..\object_manager\object_manager.h"
#include "..\..\..\effect_manager\effect_manager.h"
#include "..\..\..\unit_manager\unit_manager.h"

const float			CBeltConveyorGimmick::m_mid_belt_speed_time = 60.0f;

const float			CBeltConveyorGimmick::m_default_belt_move_speed	= 5.0f;
const float			CBeltConveyorGimmick::m_min_belt_speed_rate		= 1.0f;
const float			CBeltConveyorGimmick::m_mid_belt_speed_rate		= 3.0f;
const float			CBeltConveyorGimmick::m_max_belt_speed_rate		= 5.0f;

const float			CBeltConveyorGimmick::m_default_obstruction_spawn_time	= 3.0f;

const float			CBeltConveyorGimmick::m_obstruction_object_scale		= 0.5f;
const CVector3		CBeltConveyorGimmick::m_obstruction_spawn_relative_pos	= CVector3(0.0f, 50.0f, -1000.0f);
const float			CBeltConveyorGimmick::m_obstruction_delete_height		= -1000.0f;

const float			CBeltConveyorGimmick::m_obstruction_object_fall_speed = 10.0f;

CBeltConveyorGimmick::CBeltConveyorGimmick()
	: CGimmick()
	, m_NowBeltSpeedRate(0)
	, m_ObstructionSpawnTimer()
	, m_BeltConveyorForward(CVector3::FORWARD)
	, m_ObstructionObjectList()
{
}

CBeltConveyorGimmick::~CBeltConveyorGimmick(void)
{
}

void CBeltConveyorGimmick::Initialize(std::shared_ptr<IObject> object)
{
	Initialize(object, m_mid_belt_speed_time);
}

void CBeltConveyorGimmick::Initialize(std::shared_ptr<IObject> object, float time)
{
	CGimmick::Initialize(object, time);

	m_Object->SetGimmick(shared_from_this());
	m_BeltConveyorForward = m_Object->GetTransform().GetForwardVector();

	m_NowBeltSpeedRate = m_min_belt_speed_rate;
	m_Timer.SetUp(m_mid_belt_speed_time);
	m_ObstructionSpawnTimer.SetUp(m_default_obstruction_spawn_time);
}

void CBeltConveyorGimmick::Update(void)
{
	CGimmick::Update();

	//�x���g�R���x�A�̑��x�X�V
	m_NowBeltSpeedRate = m_min_belt_speed_rate + (m_mid_belt_speed_rate - m_min_belt_speed_rate) * m_Timer.GetTimer() / m_mid_belt_speed_time;
	if (m_NowBeltSpeedRate > m_max_belt_speed_rate)
		m_NowBeltSpeedRate = m_max_belt_speed_rate;

	//��Q���̃X�|�[���p�x�X�V
	m_ObstructionSpawnTimer.SetLimitTime(m_default_obstruction_spawn_time / m_NowBeltSpeedRate);

	//��Q���̃X�|�[��
	m_ObstructionSpawnTimer.Update();
	if (m_ObstructionSpawnTimer.Finished())
	{
		m_ObstructionSpawnTimer.Reset();

		CTransform SpawnTr;
		CVector3 SpawnRelativePos = m_obstruction_spawn_relative_pos;
		SpawnTr.position = CVector3(9999,9999,9999);
		SpawnTr.rotation = m_Object->GetRotation();
		SpawnTr.scale = CVector3(m_obstruction_object_scale, m_obstruction_object_scale, m_obstruction_object_scale);

		std::shared_ptr<IObject> SpawnObj = CObjectManager::GetInstance().Create(OBJECT_ID::BELT_CONVEYOR_OBSTRUCTION_OBJECT, SpawnTr);
	
		SpawnObj->SetPosition(m_Object->GetPosition() + SpawnRelativePos.RotateAroundCoordinatesAxis(COORDINATES_AXIS::Y, m_Object->GetRotation().y));

		m_ObstructionObjectList.push_back(SpawnObj);
	}
	
	//��Q���̈ړ�
	if (!m_ObstructionObjectList.empty())
	{
		std::list<std::shared_ptr<IObject>>::iterator it = m_ObstructionObjectList.begin();
		std::list<std::shared_ptr<IObject>> DeleteObjList;

		while (it != m_ObstructionObjectList.end())
		{
			CVector3 ObjPos = (*it)->GetPosition();
			
			if ((*it)->GetPosition().y < m_obstruction_delete_height)
			{
				DeleteObjList.push_back(*it);
				it++;
				continue;
			}

			CVector3 CheckLineEndPos = ObjPos + CVector3(0.0f, 50.0f, 0.0f);

			//�x���g�R���x�A�̏�ɂ���ꍇ
			if (m_Object->GetModelHandle().CheckHitLine( ObjPos, CheckLineEndPos))
			{
				//�x���g�R���x�A�̑����ɍ��킹�Đ��������̈ړ�
				(*it)->SetPosition(ObjPos + m_BeltConveyorForward * (m_default_belt_move_speed * m_NowBeltSpeedRate));
			}
			//�x���g�R���x�A�̏�ɂ��Ȃ��ꍇ�i�������j
			else
			{
				//�x���g�R���x�A�̑����̔����̑����Ő��������̈ړ� �{ �������x�Ő��������̈ړ��i�Q�[���v���C���ɂ��܂茩�Ȃ������̉��o�̂��߁A�����Ƀ��A���̓������Č�����K�v�͂Ȃ������Ȃ̂ŁA������ۂ���������x�Ɂj
				(*it)->SetPosition(ObjPos + m_BeltConveyorForward * (m_default_belt_move_speed * m_NowBeltSpeedRate * 0.5f) + CVector3::DOWN * m_obstruction_object_fall_speed);
				
				//������]������i�x���g�R���x�A�̒[���ۂ��Ȃ��Ă���e���ŁA�������ɉ�]�������ق������R�Ɍ�����j
				(*it)->SetRotation((*it)->GetRotation() + CVector3(0.2f, 0.0f, 0.0f));
			}

			it++;
		}

		it = DeleteObjList.begin();
		while (it != DeleteObjList.end())
		{
			m_ObstructionObjectList.remove((*it));
			(*it)->Delete(false);
			it++;
		}
	}


	//�v���C���[�̈ړ��i�x���g�R���x�A�̉e���j
	CUnitManager::UNIT_LIST unitList = CUnitManager::GetInstance().GetUnitList();
	CUnitManager::UNIT_LIST::iterator it = unitList.begin();
	while (it != unitList.end())
	{
		std::shared_ptr<IUnit> unit = *it;
		++it;

		//�s�k��ԂȂ�X�L�b�v
		if (unit->GetDefeatFlag())
			continue;

		//�󒆂Ȃ�X�L�b�v
		if (!unit->IsGround())
			continue;

		unit->SetPosition(unit->GetPosition() + m_BeltConveyorForward * (m_default_belt_move_speed * m_NowBeltSpeedRate));
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
