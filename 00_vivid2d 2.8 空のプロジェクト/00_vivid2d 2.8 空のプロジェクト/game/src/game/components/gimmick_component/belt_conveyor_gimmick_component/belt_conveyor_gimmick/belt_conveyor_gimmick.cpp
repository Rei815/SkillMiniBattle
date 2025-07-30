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

const float			CBeltConveyorGimmick::m_obstruction_object_fall_speed = 600.0f;

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
	m_Timer.Update();
	float deltaTime = vivid::GetDeltaTime();
	auto TransformComp = m_Object->GetComponent<TransformComponent>();
	//ベルトコンベアの速度更新
	m_NowBeltSpeedRate = m_min_belt_speed_rate + (m_mid_belt_speed_rate - m_min_belt_speed_rate) * m_Timer.GetTimer() / m_mid_belt_speed_time;
	if (m_NowBeltSpeedRate > m_max_belt_speed_rate)
		m_NowBeltSpeedRate = m_max_belt_speed_rate;

	//障害物のスポーン頻度更新
	m_ObstructionSpawnTimer.SetLimitTime(m_default_obstruction_spawn_time / m_NowBeltSpeedRate);

	//障害物のスポーン
	m_ObstructionSpawnTimer.Update();
	if (m_ObstructionSpawnTimer.Finished())
	{
		m_ObstructionSpawnTimer.Reset();

		CTransform SpawnTr;
		CVector3 SpawnRelativePos = m_obstruction_spawn_relative_pos;
		SpawnTr.position = CVector3(9999, 9999, 9999);
		SpawnTr.rotation = TransformComp->GetRotation();
		SpawnTr.scale = CVector3(m_obstruction_object_scale, m_obstruction_object_scale, m_obstruction_object_scale);

		int obstruction_id = rand() % 6 + (int)OBJECT_ID::BELT_CONVEYOR_OBSTRUCTION_1;
		std::shared_ptr<CGameObject> SpawnObj = CObjectManager::GetInstance().Create((OBJECT_ID)obstruction_id, SpawnTr);

		SpawnObj->GetComponent<TransformComponent>()->SetPosition(TransformComp->GetPosition() + SpawnRelativePos.RotateAroundCoordinatesAxis(COORDINATES_AXIS::Y, TransformComp->GetRotation().y));

		m_ObstructionObjectList.push_back(SpawnObj);
	}

	CVector3 move_vector = m_BeltConveyorForward * (m_default_belt_move_speed * m_NowBeltSpeedRate);

	//障害物の移動
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

			//ベルトコンベアの上にいる場合
			if (m_Object->GetComponent<MeshColliderComponent>()->CheckHitLine(ObjPos, CheckLineEndPos))
			{
				//ベルトコンベアの速さに合わせて水平方向の移動
				TransformComp->Translate(move_vector * deltaTime);
			}
			//ベルトコンベアの上にいない場合（落下中）
			else
			{
				CVector3 horizontal_move = m_BeltConveyorForward * (m_default_belt_move_speed * m_NowBeltSpeedRate * 0.5f);
				CVector3 vertical_move = CVector3::DOWN * m_obstruction_object_fall_speed;
				//ベルトコンベアの速さの半分の速さで水平方向の移動 ＋ 落下速度で垂直方向の移動（ゲームプレイ中にあまり見ない部分の演出のため、厳密にリアルの動きを再現する必要はなさそうなので、それっぽく見える程度に）
				//TransformComp->Translate(move_vector * 0.5f + CVector3::DOWN * m_obstruction_object_fall_speed * deltaTime);
				TransformComp->Translate((horizontal_move + vertical_move) * deltaTime);

				//少し回転させる（ベルトコンベアの端が丸くなっている影響で、落下時に回転が加わるほうが自然に見える）
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


	//プレイヤーの移動（ベルトコンベアの影響）

	auto& objManager = CObjectManager::GetInstance();
	auto playerObjects = objManager.GetObjectsWithComponent<PlayerComponent>();

	for (auto& playerObject : playerObjects)
	{
		auto playerComp = playerObject->GetComponent<PlayerComponent>();
		if (playerComp && !playerComp->IsDefeated() && playerComp->IsGround())
		{
			// playerTransform->Translate(...) をやめる
			CVector3 conveyor_force = m_BeltConveyorForward * (m_default_belt_move_speed * m_NowBeltSpeedRate);

			// プレイヤーコンポーネントに「外部からの力」として速度を渡す
			playerComp->AddAffectedVelocity(conveyor_force);
		}
	}
}