#include "fall_game.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../gimmick_manager/gimmick_manager.h"
#include "../../../../camera/camera.h"
#include "../../../../object_manager/object_manager.h"
#include "../../../../object_manager/object/fall_object/mark_id.h"

CFallGame::CFallGame(void)
{
}

CFallGame::~CFallGame(void)
{
}

void CFallGame::Initialize(void)
{
	m_FallTime = 180;
	m_FallTimer = 0;


	CGame::Initialize();
	CCamera::GetInstance().Initialize();

	m_DebugText = "フォールゲーム";
	CUnitManager::GetInstance().Create(UNIT_ID::PLAYER1, CVector3(0, 0, 100));
	CUnitManager::GetInstance().Create(UNIT_ID::PLAYER2, CVector3(100, 0, 200));

	CObjectManager::GetInstance().Create(OBJECT_ID::CIRCLE_FALL_OBJECT);
	CObjectManager::GetInstance().Create(OBJECT_ID::CROSS_FALL_OBJECT);
	CObjectManager::GetInstance().Create(OBJECT_ID::MOON_FALL_OBJECT);
	CObjectManager::GetInstance().Create(OBJECT_ID::SQUARE_FALL_OBJECT);
	CObjectManager::GetInstance().Create(OBJECT_ID::SUN_FALL_OBJECT);
	CObjectManager::GetInstance().Create(OBJECT_ID::TRIANGLE_FALL_OBJECT);
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
	vivid::DrawText(30, std::to_string(m_FallTimer), vivid::Vector2(vivid::WINDOW_WIDTH - vivid::GetTextWidth(30, std::to_string(m_FallTimer)), 0));
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
	if (++m_FallTimer > m_FallTime)
	{

		m_FallTimer = 0;

		OBJECT_ID objectID = ChooseObject();


		if (objectID != OBJECT_ID::NONE)
		CObjectManager::GetInstance().SetGimmick(GIMMICK_ID::FALL_GIMMICK, objectID, 1.0f);
	}

}

void CFallGame::Finish(void)
{
	CGame::Finish();
}

OBJECT_ID CFallGame::ChooseObject(void)
{
	int object_id = (int)OBJECT_ID::NONE;
	CObjectManager::OBJECT_LIST objectList = CObjectManager::GetInstance().GetList();

	if (objectList.size() == 1)
	{
		m_FallTimer = 0;
		return OBJECT_ID::NONE;
	}

	bool flag = false;

	while (flag == false)
	{
		object_id = rand() % (int)OBJECT_ID::MAX + (int)OBJECT_ID::MOON_FALL_OBJECT;

		CObjectManager::OBJECT_LIST::iterator it = objectList.begin();

		while (it != objectList.end())
		{
			if ((*it)->GetObjectID() == (OBJECT_ID)object_id)
			{
				flag = true;
				break;
			}
			++it;
		}
	}
	return (OBJECT_ID)object_id;
}
