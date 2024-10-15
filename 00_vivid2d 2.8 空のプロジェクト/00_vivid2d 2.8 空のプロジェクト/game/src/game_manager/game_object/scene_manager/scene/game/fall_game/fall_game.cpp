#include "fall_game.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../gimmick_manager/gimmick_manager.h"
#include "../../../../camera/camera.h"
#include "../../../../object_manager/object_manager.h"
#include "../../../../ui_manager/ui_manager.h"
#include "../../../../object_manager/object/fall_object/mark_id.h"

const CTransform CFallGame::m_object_transform_list[] = 
{CTransform(CVector3(0,-100,0)),CTransform(CVector3(100,-100,0)), CTransform(CVector3(200,-100,0)),
CTransform(CVector3(-100,-100,0)), CTransform(CVector3(-200,-100,0)), CTransform(CVector3(-300,-100,0)) };

const float		CFallGame::m_time_accelerator = 0.1f;
const float		CFallGame::m_min_time = 1.0f;
const float		CFallGame::m_initial_time = 3.0f;
CFallGame::CFallGame(void)
{
}

CFallGame::~CFallGame(void)
{
}

void CFallGame::Initialize(void)
{
	m_FallTime = m_initial_time;
	m_Timer.SetUp(m_FallTime);
	CGame::Initialize();
	CCamera::GetInstance().Initialize();

	m_DebugText = "フォールゲーム";
	CUnitManager::GetInstance().Create(UNIT_ID::PLAYER1, CVector3(0, 0, 100));
	CUnitManager::GetInstance().Create(UNIT_ID::PLAYER2, CVector3(100, 0, 200));

	CObjectManager& om = CObjectManager::GetInstance();
	CGimmickManager& gm = CGimmickManager::GetInstance();

	IObject* object = nullptr;
	object = om.Create(OBJECT_ID::CIRCLE_FALL_OBJECT,m_object_transform_list[(int)MARK_ID::CIRCLE]);
	gm.Create(GIMMICK_ID::FALL_GIMMICK, object);

	object = om.Create(OBJECT_ID::MOON_FALL_OBJECT,m_object_transform_list[(int)MARK_ID::MOON]);
	gm.Create(GIMMICK_ID::FALL_GIMMICK, object);

	object = om.Create(OBJECT_ID::CROSS_FALL_OBJECT,m_object_transform_list[(int)MARK_ID::CROSS]);
	gm.Create(GIMMICK_ID::FALL_GIMMICK, object);

	object = om.Create(OBJECT_ID::SUN_FALL_OBJECT,m_object_transform_list[(int)MARK_ID::SUN]);
	gm.Create(GIMMICK_ID::FALL_GIMMICK, object);

	object = om.Create(OBJECT_ID::SQUARE_FALL_OBJECT,m_object_transform_list[(int)MARK_ID::SQUARE]);
	gm.Create(GIMMICK_ID::FALL_GIMMICK, object);


	object = om.Create(OBJECT_ID::TRIANGLE_FALL_OBJECT,m_object_transform_list[(int)MARK_ID::TRIANGLE]);
	gm.Create(GIMMICK_ID::FALL_GIMMICK, object);
}

void CFallGame::Update(void)
{
	CGame::Update();
	CCamera::GetInstance().Update();

}

void CFallGame::Draw(void)
{
	CGame::Draw();
#ifdef VIVID_DEBUG
	vivid::DrawText(30, std::to_string(m_Timer.GetTimer()),
		vivid::Vector2(vivid::WINDOW_WIDTH - vivid::GetTextWidth(30, std::to_string(m_Timer.GetTimer())), 0));
#endif // VIVID_DEBUG

}

void CFallGame::Finalize(void)
{
	CGame::Finalize();
	CCamera::GetInstance().Finalize();

}

void CFallGame::Start(void)
{
	CGame::Start();
}

void CFallGame::Play(void)
{
	CGame::Play();

	m_Timer.Update();
	if (m_Timer.Finished())
	{

		m_Timer.Reset();

		FALL_INFO fallInfo = ChooseObject();

		if (fallInfo.object == nullptr) return;
		if (fallInfo.object->GetObjectID() != OBJECT_ID::NONE)
		{
			fallInfo.object->GetGimmick()->SetTimer(1.0f);
			fallInfo.object->GetGimmick()->SetSwitch(true);

			m_FallTime -= m_time_accelerator;
			m_Timer.SetUp(m_FallTime);
			if (m_FallTime < m_min_time)
				m_FallTime = m_min_time;
			CUIManager::GetInstance().Create(fallInfo.uiID);
		}
	}

}

void CFallGame::Finish(void)
{
	CGame::Finish();
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
		if ((*it)->GetState() == OBJECT_STATE::WAIT)
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
	case OBJECT_ID::MOON_FALL_OBJECT: fallInfo.uiID = UI_ID::FALL_MOON; break;
	case OBJECT_ID::CIRCLE_FALL_OBJECT: fallInfo.uiID = UI_ID::FALL_CIRCLE; break;
	case OBJECT_ID::CROSS_FALL_OBJECT: fallInfo.uiID = UI_ID::FALL_CROSS; break;
	case OBJECT_ID::SQUARE_FALL_OBJECT: fallInfo.uiID = UI_ID::FALL_SQUARE; break;
	case OBJECT_ID::SUN_FALL_OBJECT: fallInfo.uiID = UI_ID::FALL_SUN; break;
	case OBJECT_ID::TRIANGLE_FALL_OBJECT: fallInfo.uiID = UI_ID::FALL_TRIANGLE; break;
	}
	return fallInfo;
}
