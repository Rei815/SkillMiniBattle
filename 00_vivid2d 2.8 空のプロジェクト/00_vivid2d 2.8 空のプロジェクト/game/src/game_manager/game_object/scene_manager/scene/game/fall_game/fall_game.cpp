#include "fall_game.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../gimmick_manager/gimmick_manager.h"
#include "../../../../camera/camera.h"
#include "../../../../object_manager/object_manager.h"
#include "../../../../ui_manager/ui_manager.h"
#include "../../../../object_manager/object/fall_object/mark_id.h"
#include "../../../../data_manager/data_manager.h"
#include "../../../../skill_manager/skill_manager.h"
#include "../../../../bullet_manager/bullet_manager.h"
#include "../../../../ui_manager/ui/fallout_topic/fallout_topic.h"

const CTransform CFallGame::m_object_transform_list[] = 
{CTransform(CVector3(450,-100,-300)),CTransform(CVector3(-450,-100,250)), CTransform(CVector3(0,-100,450)),
CTransform(CVector3(-450,-100,-300)), CTransform(CVector3(0,-100,-500)), CTransform(CVector3(450,-100,250)) };

const vivid::Vector2    CFallGame::m_topic_positionList[] = { vivid::Vector2(0, 0),vivid::Vector2(250, 0),vivid::Vector2(500, 0),
vivid::Vector2(750, 0),vivid::Vector2(1000, 0),vivid::Vector2(1250, 0) };

const float		CFallGame::m_time_accelerator = 0.1f;
const float		CFallGame::m_min_time = 1.5f;
const float		CFallGame::m_fall_time = 3.0f;
const float		CFallGame::m_defeat_height = -500.0f;
const float		CFallGame::m_object_delay_time = 1.0f;
const float		CFallGame::m_add_topic_time = 10.0f;
const float		CFallGame::m_reset_topic_time = 0.5f;
const int		CFallGame::m_max_topic_num = 5;
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
	m_FallTime = m_fall_time;
	for (int i = 0; i < m_max_topic_num; i++)
	{
		m_ChooseObjectTimer[i].SetUp(m_FallTime);
		m_ChooseObjectTimer[i].SetActive(false);
	}
	m_AddTopicTimer.SetUp(m_add_topic_time);
	m_ResetTopicTimer.SetUp(m_reset_topic_time);
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
		CPlayer* Player = dynamic_cast<CPlayer*>(unit);
		if (Player != nullptr)
			Player->SetActionFlag(false);
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

	CUI* ui = CUIManager::GetInstance().Create(UI_ID::FALLOUT_TOPIC, m_topic_positionList[m_TopicList.size()]);

	m_TopicList.push_back((CFallOutTopic*)ui);
	m_ChooseObjectTimer[m_TopicList.size() - 1].SetActive(true);
}

void CFallGame::Update(void)
{
	CBulletManager::GetInstance().Update();

	CStage::GetInstance().Update();
	CGame::Update();

	CCamera::GetInstance().Update();

}

void CFallGame::Draw(void)
{
	CGame::Draw();
	CBulletManager::GetInstance().Draw();

#ifdef VIVID_DEBUG

	for (int i = 0; i < m_max_topic_num; i++)
	{
		vivid::DrawText(30, std::to_string(m_ChooseObjectTimer[i].GetTimer()), vivid::Vector2(vivid::WINDOW_WIDTH - vivid::GetTextWidth(30, std::to_string(m_ChooseObjectTimer[i].GetTimer())), 10 * i));

	}
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

	for (int i = 0; i < m_max_topic_num; i++)
		m_ChooseObjectTimer[i].Update();

	m_AddTopicTimer.Update();

	CFallOutTopic* topic = nullptr;

	//出ているお題ごとに抽選する
	for (int i = 0; i < m_max_topic_num; i++)
	{
		//抽選する時間になったら
		if (m_ChooseObjectTimer[i].Finished())
		{
			m_ChooseObjectTimer[i].Reset();

			//タイマーの停止
			m_ChooseObjectTimer[i].SetActive(false);
			TOPIC_LIST::iterator it = m_TopicList.begin();


			bool chooseFlag = false;
			while (it != m_TopicList.end())
			{
				topic = (*it);

				//取得に失敗したら早期リターン
				if (!topic)
				{
					++it;
					continue;
				}

				//切り替わっている時のみにお題の指定
				if (topic->GetState() == CFallOutTopic::STATE::SWITCHING)
				{
					chooseFlag = true;
					break;
				}
				++it;
			}

			if (!chooseFlag) return;
			
			//抽選する
			FALL_INFO fallInfo = ChooseObject();

			if (fallInfo.object == nullptr) return;

			if (fallInfo.object->GetObjectID() != OBJECT_ID::NONE)
			{
				fallInfo.object->GetGimmick()->SetTimer(m_object_delay_time);
				fallInfo.object->GetGimmick()->SetState(GIMMICK_STATE::PLAY);

				//m_FallTime -= m_time_accelerator;
				//if (m_FallTime < m_min_time)
				//	m_FallTime = m_min_time;
				//m_FallTime = m_fall_time;
				//m_FallTime += i * 1.0f;
				//m_ChooseObjectTimer[i].SetUp(m_FallTime);


				topic->SetMarkID(fallInfo.markID);
				topic->SetTimer(m_FallTime);
				
			}
		}
	}

	//お題の追加
	if (m_AddTopicTimer.Finished())
	{
		m_AddTopicTimer.Reset();
		if (m_TopicList.size() >= m_max_topic_num) return;

		CUI* ui = CUIManager::GetInstance().Create(UI_ID::FALLOUT_TOPIC, m_topic_positionList[m_TopicList.size()]);

		m_TopicList.push_back((CFallOutTopic*)ui);
		m_ChooseObjectTimer[m_TopicList.size()].SetActive(true);
		m_ChooseObjectTimer[m_TopicList.size()].SetUp(m_ChooseObjectTimer[m_TopicList.size() - 1].GetTimer() + 1.0f);
	}


	//現在出ている最後のお題が抽選され,オブジェクトがすべて待機中なら全てのお題を再抽選
	CObjectManager::OBJECT_LIST objectList = CObjectManager::GetInstance().GetList();
	CObjectManager::OBJECT_LIST::iterator it = objectList.begin();

	while (it != objectList.end())
	{
		GIMMICK_STATE state = (*it)->GetGimmick()->GetState();

		if (state == GIMMICK_STATE::PLAY || state == GIMMICK_STATE::FINISH)
			break;

		++it;
	}

	if (m_ChooseObjectTimer[m_TopicList.size() - 1].GetActive() == true || it != objectList.end()) return;

	m_ResetTopicTimer.Update();

	if (m_ResetTopicTimer.Finished())
	{
		m_ResetTopicTimer.Reset();
		for (int i = 0; i < m_TopicList.size(); i++)
		{
			m_ChooseObjectTimer[i].SetActive(true);
			m_ChooseObjectTimer[i].SetUp(m_ChooseObjectTimer[0].GetLimitTime() + i * 1.0f);

		}
		TOPIC_LIST::iterator it = m_TopicList.begin();

		while (it != m_TopicList.end())
		{
			topic = (*it);

			if (!topic)
			{
				++it;
				continue;
			}
			topic->SetState(CFallOutTopic::STATE::SWITCHING);
			++it;
		}
	}

}

void CFallGame::Finish(void)
{
	//一人生き残った場合(二人以上)
	if (m_EntryList.size() == 1)
	{
		//生き残った一人を勝ちにする
		CDataManager::GetInstance().PlayerWin((*m_EntryList.begin())->GetUnitID());
		CDataManager::GetInstance().AddLastGameRanking((*m_EntryList.begin())->GetUnitID());
	}
	else //一人の場合
	{
		//やられているためリザルトリストから勝ちにする
		CDataManager::GetInstance().PlayerWin((*m_ResultList.begin())->GetUnitID());
		CDataManager::GetInstance().AddLastGameRanking((*m_ResultList.begin())->GetUnitID());
	}
	CGame::Finish();
}

/*
 終了判定
*/
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
			CPlayer* player = (CPlayer*)unit;

			CSkill* skill = player->GetSkill();
			if (skill->GetSkillCategory() == SKILL_CATEGORY::RESURRECT && skill->GetState() != SKILL_STATE::COOLDOWN)
			{
				skill->SetState(SKILL_STATE::ACTIVE);
				return;
			}
			AddRanking(unit->GetUnitID());
			unit->SetDefeatFlag(true);

			CDataManager::GetInstance().AddLastGameRanking(player->GetUnitID());
		}
		++it;
	}

	//二人以上の場合
	if (CDataManager::GetInstance().GetCurrentPlayer() > 1)
	{
		//一人が生き残った時に終了
		if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentPlayer() - 1)
			CGame::SetGameState(GAME_STATE::FINISH);
	}
	else //一人の場合
	{
		//やられたら終了
		if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentPlayer())
			CGame::SetGameState(GAME_STATE::FINISH);
	}
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
	case OBJECT_ID::MOON_FALL_OBJECT:		fallInfo.markID = MARK_ID::MOON;		break;
	case OBJECT_ID::CIRCLE_FALL_OBJECT:		fallInfo.markID = MARK_ID::CIRCLE;		break;
	case OBJECT_ID::CROSS_FALL_OBJECT:		fallInfo.markID = MARK_ID::CROSS;		break;
	case OBJECT_ID::SQUARE_FALL_OBJECT:		fallInfo.markID = MARK_ID::SQUARE;		break;
	case OBJECT_ID::SUN_FALL_OBJECT:		fallInfo.markID = MARK_ID::SUN;			break;
	case OBJECT_ID::TRIANGLE_FALL_OBJECT:	fallInfo.markID = MARK_ID::TRIANGLE;	break;
	}
	return fallInfo;
}
