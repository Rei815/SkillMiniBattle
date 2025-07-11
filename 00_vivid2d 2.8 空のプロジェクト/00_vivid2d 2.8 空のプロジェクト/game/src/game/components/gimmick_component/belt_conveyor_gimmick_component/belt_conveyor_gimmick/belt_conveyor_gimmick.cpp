#include "belt_conveyor_gimmick.h"
#include "engine/components/transform_component/transform_component.h"
#include "engine/managers/object_manager/object_manager.h"
#include "../../../player_component/player_component.h"
#include "engine/components/collider_component/mesh_collider_component/mesh_collider_component.h"

const float			CBeltConveyorGimmick::m_mid_belt_speed_time = 60.0f;

const float			CBeltConveyorGimmick::m_default_belt_move_speed = 300.0f;
const float			CBeltConveyorGimmick::m_min_belt_speed_rate = 1.0f;
const float			CBeltConveyorGimmick::m_mid_belt_speed_rate = 3.0f;
const float			CBeltConveyorGimmick::m_max_belt_speed_rate = 5.0f;

const float			CBeltConveyorGimmick::m_default_obstruction_spawn_time = 3.0f;

const float			CBeltConveyorGimmick::m_obstruction_object_scale = 0.5f;
const CVector3		CBeltConveyorGimmick::m_obstruction_spawn_relative_pos = CVector3(0.0f, 50.0f, -1000.0f);
const float			CBeltConveyorGimmick::m_obstruction_delete_height = -1000.0f;

const float			CBeltConveyorGimmick::m_obstruction_object_fall_speed = 10.0f;

CBeltConveyorGimmick::CBeltConveyorGimmick()
	: m_NowBeltSpeedRate(0)
	, m_ObstructionSpawnTimer()
	, m_BeltConveyorForward(CVector3::FORWARD)
	, m_ObstructionObjectList()
{
}

CBeltConveyorGimmick::~CBeltConveyorGimmick(void)
{
}

void CBeltConveyorGimmick::Initialize(CGameObject* object)
{
	m_Object = object;
	m_Timer.SetUp(m_mid_belt_speed_time);
	m_BeltConveyorForward = m_Object->GetComponent<TransformComponent>()->GetTransform().GetForwardVector();

	m_NowBeltSpeedRate = m_min_belt_speed_rate;
	m_Timer.SetUp(m_mid_belt_speed_time);
	m_ObstructionSpawnTimer.SetUp(m_default_obstruction_spawn_time);

}

void CBeltConveyorGimmick::Update(void)
{
	auto TransformComp = m_Object->GetComponent<TransformComponent>();
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
		SpawnTr.position = CVector3(9999, 9999, 9999);
		SpawnTr.rotation = TransformComp->GetRotation();
		SpawnTr.scale = CVector3(m_obstruction_object_scale, m_obstruction_object_scale, m_obstruction_object_scale);

		std::shared_ptr<CGameObject> SpawnObj = CObjectManager::GetInstance().Create(OBJECT_ID::BELT_CONVEYOR, SpawnTr);

		SpawnObj->GetComponent<TransformComponent>()->SetPosition(TransformComp->GetPosition() + SpawnRelativePos.RotateAroundCoordinatesAxis(COORDINATES_AXIS::Y, TransformComp->GetRotation().y));

		m_ObstructionObjectList.push_back(SpawnObj);
	}

	//��Q���̈ړ�
	if (!m_ObstructionObjectList.empty())
	{
		std::list<std::shared_ptr<CGameObject>>::iterator it = m_ObstructionObjectList.begin();
		std::list<std::shared_ptr<CGameObject>> DeleteObjList;

		while (it != m_ObstructionObjectList.end())
		{
			auto TransformComp = (*it)->GetComponent<TransformComponent>();
			CVector3 ObjPos = TransformComp->GetPosition();
			if (ObjPos.y < m_obstruction_delete_height)
			{
				DeleteObjList.push_back(*it);
				it++;
				continue;
			}

			CVector3 CheckLineEndPos = ObjPos + CVector3(0.0f, 50.0f, 0.0f);

			//�x���g�R���x�A�̏�ɂ���ꍇ
			if (m_Object->GetComponent<MeshColliderComponent>()->CheckHitLine(ObjPos, CheckLineEndPos))
			{
				//�x���g�R���x�A�̑����ɍ��킹�Đ��������̈ړ�
				TransformComp->SetPosition(ObjPos + m_BeltConveyorForward * (m_default_belt_move_speed * m_NowBeltSpeedRate));
			}
			//�x���g�R���x�A�̏�ɂ��Ȃ��ꍇ�i�������j
			else
			{
				//�x���g�R���x�A�̑����̔����̑����Ő��������̈ړ� �{ �������x�Ő��������̈ړ��i�Q�[���v���C���ɂ��܂茩�Ȃ������̉��o�̂��߁A�����Ƀ��A���̓������Č�����K�v�͂Ȃ������Ȃ̂ŁA������ۂ���������x�Ɂj
				TransformComp->SetPosition(ObjPos + m_BeltConveyorForward * (m_default_belt_move_speed * m_NowBeltSpeedRate * 0.5f) + CVector3::DOWN * m_obstruction_object_fall_speed);

				//������]������i�x���g�R���x�A�̒[���ۂ��Ȃ��Ă���e���ŁA�������ɉ�]�������ق������R�Ɍ�����j
				TransformComp->SetRotation(TransformComp->GetRotation() + CVector3(0.2f, 0.0f, 0.0f));
			}

			it++;
		}

		it = DeleteObjList.begin();
		while (it != DeleteObjList.end())
		{
			m_ObstructionObjectList.remove((*it));
			(*it)->Delete();
			it++;
		}
	}


	//�v���C���[�̈ړ��i�x���g�R���x�A�̉e���j

		// 1. ObjectManager�ɁAPlayerComponent�����S�ẴI�u�W�F�N�g��₢���킹��
	auto& objManager = CObjectManager::GetInstance();
	auto playerObjects = objManager.GetObjectsWithComponent<PlayerComponent>();

	// 2. �擾�����S�v���C���[�I�u�W�F�N�g�����[�v
	for (auto& playerObject : playerObjects)
	{
		// 3. PlayerComponent���擾���āA��Ԃ��`�F�b�N
		auto playerComp = playerObject->GetComponent<PlayerComponent>();
		if (playerComp && !playerComp->IsDefeated() && playerComp->IsGround())
		{
			// 4. TransformComponent���擾���āA�x���g�R���x�A�̗͂�������
			auto playerTransform = playerObject->GetComponent<TransformComponent>();
			if (playerTransform)
			{
				CVector3 move_vector = m_BeltConveyorForward * (m_default_belt_move_speed * m_NowBeltSpeedRate);

				// �t���[�����[�g�Ɉˑ����Ȃ��悤�� delta_time ���|����
				// (���̏�����delta_time���󂯎��Update���ɂ���͂�)
				playerTransform->Translate(move_vector * vivid::GetDeltaTime());
			}
		}
	}
}

void CBeltConveyorGimmick::Draw(void)
{

}

void CBeltConveyorGimmick::Finalize(void)
{
}
