#include "fall_game.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../gimmick_manager/gimmick_manager.h"
#include "../../../../camera/camera.h"
#include "../../../../object_manager/object_manager.h"
#include "../../../../ui_manager/ui_manager.h"
#include "../../../../object_manager/object/fall_object/mark_id.h"
#include "../../../../data_manager/data_manager.h"
#include "../../../../skill_manager/skill_manager.h"

const CTransform CFallGame::m_object_transform_list[] = 
{CTransform(CVector3(450,-100,-300)),CTransform(CVector3(-450,-100,250)), CTransform(CVector3(0,-100,450)),
CTransform(CVector3(-450,-100,-300)), CTransform(CVector3(0,-100,-500)), CTransform(CVector3(450,-100,250)) };

const float		CFallGame::m_time_accelerator = 0.1f;
const float		CFallGame::m_min_time = 1.0f;
const float		CFallGame::m_initial_time = 1.0f;
const float		CFallGame::m_defeat_height = -500.0f;
const float		CFallGame::m_object_delay_time = 1.0f;
const CVector3	CFallGame::m_camera_position = CVector3(0, 1000.0f, -1000.0f);
const CVector3	CFallGame::m_camera_direction = CVector3(0.0f, -1.0f, 1.0f);
CFallGame::CFallGame(void)
{
}

CFallGame::~CFallGame(void)
{
}

void CFallGame::Initialize(SCENE_ID scene_id)
{
	m_FallTime = m_initial_time;
	m_ChooseObjectTimer.SetUp(m_FallTime);
	CGame::Initialize(scene_id);
	CStage::GetInstance().Initialize();
	CCamera::GetInstance().Initialize();
	CCamera::GetInstance().SetPosition(m_camera_position);
	CCamera::GetInstance().SetDirection(m_camera_direction);
	m_DebugText = "フォールゲーム";
	CVector3 playerPos[] = { m_object_transform_list[(int)MARK_ID::CIRCLE].position, m_object_transform_list[(int)MARK_ID::CROSS].position,
	m_object_transform_list[(int)MARK_ID::MOON].position,m_object_transform_list[(int)MARK_ID::SQUARE].position };

	for (int i = 0; i < CDataManager::GetInstance().GetCurrentPlayer(); i++)
	{
		playerPos[i].y += 200.0f;
		IUnit* unit = CUnitManager::GetInstance().Create((UNIT_ID)i, playerPos[i]);
		m_EntryList.push_back(unit);
	}

	CSkillManager::GetInstance().SetSkill();
	CObjectManager& om = CObjectManager::GetInstance();
	CGimmickManager& gm = CGimmickManager::GetInstance();

	IObject* object = nullptr;
	object = om.Create(OBJECT_ID::CIRCLE_FALL_OBJECT,m_object_transform_list[(int)MARK_ID::CIRCLE]);
	gm.Create(GIMMICK_ID::FALL_GIMMICK, object);

	object = om.Create(OBJECT_ID::CROSS_FALL_OBJECT,m_object_transform_list[(int)MARK_ID::CROSS]);
	gm.Create(GIMMICK_ID::FALL_GIMMICK, object);

	object = om.Create(OBJECT_ID::MOON_FALL_OBJECT,m_object_transform_list[(int)MARK_ID::MOON]);
	gm.Create(GIMMICK_ID::FALL_GIMMICK, object);

	object = om.Create(OBJECT_ID::SQUARE_FALL_OBJECT,m_object_transform_list[(int)MARK_ID::SQUARE]);
	gm.Create(GIMMICK_ID::FALL_GIMMICK, object);

	object = om.Create(OBJECT_ID::SUN_FALL_OBJECT,m_object_transform_list[(int)MARK_ID::SUN]);
	gm.Create(GIMMICK_ID::FALL_GIMMICK, object);

	object = om.Create(OBJECT_ID::TRIANGLE_FALL_OBJECT,m_object_transform_list[(int)MARK_ID::TRIANGLE]);
	gm.Create(GIMMICK_ID::FALL_GIMMICK, object);

}

void CFallGame::Update(void)
{
	CStage::GetInstance().Update();
	CGame::Update();

	CCamera::GetInstance().Update();

}

void CFallGame::Draw(void)
{
	//CStage::GetInstance().Draw();
	CGame::Draw();

#ifdef VIVID_DEBUG
	vivid::DrawText(30, std::to_string(m_ChooseObjectTimer.GetTimer()),
		vivid::Vector2(vivid::WINDOW_WIDTH - vivid::GetTextWidth(30, std::to_string(m_ChooseObjectTimer.GetTimer())), 0));
#endif // VIVID_DEBUG
}

void CFallGame::Finalize(void)
{
	CGame::Finalize();
	CStage::GetInstance().Finalize();

	CCamera::GetInstance().Finalize();
}

void CFallGame::Start(void)
{
	CGame::Start();
}

void CFallGame::Play(void)
{
	CGame::Play();

	m_ChooseObjectTimer.Update();
	if (m_ChooseObjectTimer.Finished())
	{
		m_ChooseObjectTimer.Reset();

		FALL_INFO fallInfo = ChooseObject();

		if (fallInfo.object == nullptr) return;
		if (fallInfo.object->GetObjectID() != OBJECT_ID::NONE)
		{
			fallInfo.object->GetGimmick()->SetTimer(m_object_delay_time);
			fallInfo.object->GetGimmick()->SetSwitch(true);

			m_FallTime -= m_time_accelerator;
			m_ChooseObjectTimer.SetUp(m_FallTime);
			if (m_FallTime < m_min_time)
				m_FallTime = m_min_time;
			CUIManager::GetInstance().Create(fallInfo.uiID);
		}
	}
}

void CFallGame::Finish(void)
{
	if (m_ResultList.size() == 1)
		CDataManager::GetInstance().PlayerWin((*m_ResultList.begin())->GetUnitID());

	CGame::Finish();
}

void CFallGame::CheckFinish()
{
	CUnitManager::UNIT_LIST unitList = CUnitManager::GetInstance().GetUnitList();
	CUnitManager::UNIT_LIST::iterator it = unitList.begin();
	while (it != unitList.end())
	{
		IUnit* unit = (*it);
		if (unit->GetDefeatFlag() == true)
		{
			++it;
			continue;
		}

		if (unit->GetPosition().y < m_defeat_height)
		{
			AddRanking(unit->GetUnitID());
			unit->SetDefeatFlag(true);

		}
		++it;
	}
	if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentPlayer())
		CGame::SetGameState(GAME_STATE::FINISH);
}

CFallGame::FALL_INFO CFallGame::ChooseObject(void)
{
	FALL_INFO fallInfo = FALL_INFO();

	int index = (int)OBJECT_ID::NONE;

	CObjectManager::OBJECT_LIST objectList = CObjectManager::GetInstance().GetList();

	if (objectList.empty()) return fallInfo;

	CObjectManager::OBJECT_LIST waitObjectList;
	CObjectManager::OBJECT_LIST::iterator it;

	//待機中のオブジェクトがあるか調査
	for (it = objectList.begin(); it != objectList.end(); it++)
	{
		if ((*it)->GetGimmick()->GetState() == GIMMICK_STATE::WAIT)
		{
			waitObjectList.push_back((*it));
		}
	}

	if (waitObjectList.size() < 2)
	{
		return fallInfo;
	}

	it = waitObjectList.begin();
	index = rand() % waitObjectList.size();

	std::advance(it, index);


	fallInfo.object = (*it);
	switch ((*it)->GetObjectID())
	{
	case OBJECT_ID::MOON_FALL_OBJECT:		fallInfo.uiID = UI_ID::FALL_MOON;		break;
	case OBJECT_ID::CIRCLE_FALL_OBJECT:		fallInfo.uiID = UI_ID::FALL_CIRCLE;		break;
	case OBJECT_ID::CROSS_FALL_OBJECT:		fallInfo.uiID = UI_ID::FALL_CROSS;		break;
	case OBJECT_ID::SQUARE_FALL_OBJECT:		fallInfo.uiID = UI_ID::FALL_SQUARE;		break;
	case OBJECT_ID::SUN_FALL_OBJECT:		fallInfo.uiID = UI_ID::FALL_SUN;		break;
	case OBJECT_ID::TRIANGLE_FALL_OBJECT:	fallInfo.uiID = UI_ID::FALL_TRIANGLE;	break;
	}
	return fallInfo;
}
