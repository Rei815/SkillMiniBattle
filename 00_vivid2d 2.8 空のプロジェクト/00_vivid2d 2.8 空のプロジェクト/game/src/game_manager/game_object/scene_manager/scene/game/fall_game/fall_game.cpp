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
	m_FallTime = 1.0f;
	m_Timer.SetUp(0.0f);
	CGame::Initialize();
	CCamera::GetInstance().Initialize();

	m_DebugText = "�t�H�[���Q�[��";
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

		OBJECT_ID objectID = ChooseObject();


		if (objectID != OBJECT_ID::NONE)
		CObjectManager::GetInstance().SetGimmick(GIMMICK_ID::FALL_GIMMICK, objectID);
	}

}

void CFallGame::Finish(void)
{
	CGame::Finish();
}

OBJECT_ID CFallGame::ChooseObject(void)
{
	int index = (int)OBJECT_ID::NONE;
	CObjectManager::OBJECT_LIST objectList = CObjectManager::GetInstance().GetList();
	if (objectList.empty()) return OBJECT_ID::NONE;
	CObjectManager::OBJECT_LIST::iterator it = objectList.begin();
	bool flag = false;

	//�ҋ@���̃I�u�W�F�N�g�����邩����
	while (it != objectList.end())
	{
		if ((*it)->GetState() == OBJECT_STATE::WAIT)
			break;
		++it;
	}

	if (it == objectList.end())
	{
		return OBJECT_ID::NONE;
	}

	while (flag == false)
	{
		it = objectList.begin();
		index = rand() % objectList.size();

		std::advance(it, index);

		if ((*it)->GetState() == OBJECT_STATE::WAIT)
			flag = true;
	}
	return (*it)->GetObjectID();
}
