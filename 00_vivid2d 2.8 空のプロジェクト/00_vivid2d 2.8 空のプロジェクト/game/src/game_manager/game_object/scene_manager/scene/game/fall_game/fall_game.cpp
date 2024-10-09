#include "fall_game.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../gimmick_manager/gimmick_manager.h"
#include "../../../../camera/camera.h"
#include "../../../../object_manager/object_manager.h"
#include "../../../../object_manager/object/fall_object/mark_id.h"

const CVector3 CFallGame::m_object_position_list[] =
{ CVector3(0,100,0),CVector3(50,100,0),CVector3(100,100,0),CVector3(150,100,0),CVector3(200,100,0),CVector3(250,100,0) };
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

	CObjectManager::GetInstance().GetList().push_back(CObjectManager::GetInstance().Create(OBJECT_ID::CIRCLE_FALL_OBJECT, m_object_position_list[(int)MARK_ID::CIRCLE]));
	CObjectManager::GetInstance().GetList().push_back(CObjectManager::GetInstance().Create(OBJECT_ID::CROSS_FALL_OBJECT, m_object_position_list[(int)MARK_ID::CROSS]));
	CObjectManager::GetInstance().GetList().push_back(CObjectManager::GetInstance().Create(OBJECT_ID::MOON_FALL_OBJECT, m_object_position_list[(int)MARK_ID::MOON]));
	CObjectManager::GetInstance().GetList().push_back(CObjectManager::GetInstance().Create(OBJECT_ID::SQUARE_FALL_OBJECT, m_object_position_list[(int)MARK_ID::SQUARE]));
	CObjectManager::GetInstance().GetList().push_back(CObjectManager::GetInstance().Create(OBJECT_ID::SUN_FALL_OBJECT, m_object_position_list[(int)MARK_ID::SUN]));
	CObjectManager::GetInstance().GetList().push_back(CObjectManager::GetInstance().Create(OBJECT_ID::TRIANGLE_FALL_OBJECT, m_object_position_list[(int)MARK_ID::TRIANGLE]));
}

void CFallGame::Update(void)
{
	CGame::Update();
	CCamera::GetInstance().Update();

}

void CFallGame::Draw(void)
{
	CGame::Draw();

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
		int object_id = 0;
		CObjectManager::OBJECT_LIST objectList = CObjectManager::GetInstance().GetList();
		CObjectManager::OBJECT_LIST::iterator it = objectList.begin();
		bool flag = false;
		while (flag == false)
		{
			object_id = rand() % (int)OBJECT_ID::MAX;
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
			m_FallTimer = 0;
		CObjectManager::GetInstance().SetGimmick(GIMMICK_ID::FALL_GIMMICK, (OBJECT_ID)object_id);
	}

}

void CFallGame::Finish(void)
{
	CGame::Finish();
}
