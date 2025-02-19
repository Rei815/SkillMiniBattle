#include "fallout_game.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../gimmick_manager/gimmick_manager.h"
#include "../../../../camera/camera.h"
#include "../../../../object_manager/object_manager.h"
#include "../../../../ui_manager/ui_manager.h"
#include "../../../../object_manager/object/fall_object/mark_id.h"
#include "../../../../data_manager/data_manager.h"
#include "../../../../skill_manager/skill_manager.h"
#include "../../../../ui_manager/ui/fallout_topic/fallout_topic.h"
#include "../../../../gimmick_manager/gimmick/fall_gimmick/fall_gimmick.h"
#include "../../../../sound_manager/sound_manager.h"
#include "../../../../bullet_manager/bullet_manager.h"


const CTransform CFallOutGame::m_object_transform_list[] = 
{CTransform(CVector3(475,-100,-275)),CTransform(CVector3(-475,-100,275)), CTransform(CVector3(0,-100,475)),
CTransform(CVector3(-475,-100,-275)), CTransform(CVector3(0,-100,-475)), CTransform(CVector3(475,-100,275)) };
//const CTransform CFallOutGame::m_object_transform_list[] = 
//{CTransform(CVector3(450,-100,-300)),CTransform(CVector3(-450,-100,250)), CTransform(CVector3(0,-100,450)),
//CTransform(CVector3(-450,-100,-300)), CTransform(CVector3(0,-100,-500)), CTransform(CVector3(450,-100,250)) };

const vivid::Vector2    CFallOutGame::m_topic_positionList[] = { vivid::Vector2(0, -200),vivid::Vector2(250, -200),vivid::Vector2(500, -200),
vivid::Vector2(750, -200),vivid::Vector2(1000, -200),vivid::Vector2(1250, -200) };

const float		CFallOutGame::m_time_accelerator = 0.1f;
const float		CFallOutGame::m_min_time = 1.5f;
const float		CFallOutGame::m_fall_time = 3.0f;
const float		CFallOutGame::m_defeat_height = -500.0f;
const float		CFallOutGame::m_object_delay_time = 1.0f;
const float		CFallOutGame::m_add_topic_time = 10.0f;
const float		CFallOutGame::m_reset_topic_time = 0.5f;
const float		CFallOutGame::m_extend_return_time = 180.0f;
const float		CFallOutGame::m_topic_interval_time = 1.0f;
const int		CFallOutGame::m_max_topic_num = 5;
const CVector3  CFallOutGame::m_player_default_forward = CVector3(0.0f,0.0f,-1.0f);
const CVector3  CFallOutGame::m_floor_offset = CVector3(475.0f, -100.0f, 275.0f);
const CVector3	CFallOutGame::m_camera_position = CVector3(0, 1000.0f, -1000.0f);
const CVector3	CFallOutGame::m_camera_direction = CVector3(0.0f, -1.0f, 1.0f);

CFallOutGame::CFallOutGame(void)
	: m_FallTime(m_fall_time)
	, m_ChooseObjectTimer()
	, m_AddTopicTimer(m_add_topic_time)
	, m_ResetTopicTimer(m_reset_topic_time)
	, m_ExtendTimer(m_extend_return_time)
	, m_TopicList()
{
}

CFallOutGame::~CFallOutGame(void)
{
}

void CFallOutGame::Initialize(SCENE_ID scene_id)
{
	CGame::Initialize(scene_id);
	CCamera::GetInstance().Initialize();
	m_BackGround.Initialize("data\\Textures\\fall_out_bg.png");
	m_FallTime = m_fall_time;
	for (int i = 0; i < m_max_topic_num; i++)
	{
		m_ChooseObjectTimer[i].SetUp(m_FallTime);
		m_ChooseObjectTimer[i].SetActive(false);
	}
	m_AddTopicTimer.SetUp(m_add_topic_time);
	m_ResetTopicTimer.SetUp(m_reset_topic_time);
	m_ExtendTimer.SetUp(m_extend_return_time);
	CCamera::GetInstance().SetPosition(m_camera_position);
	CCamera::GetInstance().SetDirection(m_camera_direction);

	//BGM再生
	CSoundManager::GetInstance().Play_BGM(BGM_ID::MAIN_BGM, true);

	m_DebugText = "フォールゲーム";
	CVector3 playerPos[] = { m_object_transform_list[(int)MARK_ID::CIRCLE].position, m_object_transform_list[(int)MARK_ID::CROSS].position,
	m_object_transform_list[(int)MARK_ID::MOON].position,m_object_transform_list[(int)MARK_ID::SQUARE].position };

	for (int i = 0; i < CDataManager::GetInstance().GetCurrentPlayer(); i++)
	{
		playerPos[i].y += 200.0f;
		IUnit* unit = CUnitManager::GetInstance().Create((UNIT_ID)i, playerPos[i]);
		CPlayer* Player = dynamic_cast<CPlayer*>(unit);
		if (Player != nullptr)
		{
			Player->SetActionFlag(false);
			Player->SetForwardVector(m_player_default_forward);
		}
		m_EntryList.push_back(unit);

	}
	CBulletManager::GetInstance().Initialize();
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

void CFallOutGame::Update(void)
{
	CGame::Update();
	m_BackGround.Update();
	CBulletManager::GetInstance().Update();
	CCamera::GetInstance().Update();
}

void CFallOutGame::Draw(void)
{
	m_BackGround.Draw();

	CGame::Draw();
#ifdef VIVID_DEBUG

	for (int i = 0; i < m_max_topic_num; i++)
	{
		vivid::DrawText(30, std::to_string(m_ChooseObjectTimer[i].GetTimer()), vivid::Vector2(vivid::WINDOW_WIDTH - vivid::GetTextWidth(30, std::to_string(m_ChooseObjectTimer[i].GetTimer())), 10 * i));

	}
#endif // VIVID_DEBUG
}

void CFallOutGame::Finalize(void)
{
	m_BackGround.Finalize();
	CGame::Finalize();
	CBulletManager::GetInstance().Finalize();

	CCamera::GetInstance().Finalize();

	//BGM停止
	CSoundManager::GetInstance().Stop_BGM(BGM_ID::MAIN_BGM);
	//
}

void CFallOutGame::Start(void)
{
	CGame::Start();
	if (m_WaitTimer.Finished())
	{
		CUI* ui = CUIManager::GetInstance().Create(UI_ID::FALLOUT_TOPIC, m_topic_positionList[m_TopicList.size()]);

		m_TopicList.push_back((CFallOutTopic*)ui);
		m_ChooseObjectTimer[m_TopicList.size() - 1].SetActive(true);

	}

}

void CFallOutGame::Play(void)
{
	CGame::Play();

	for (int i = 0; i < m_max_topic_num; i++)
		m_ChooseObjectTimer[i].Update();

	m_AddTopicTimer.Update();
	m_ExtendTimer.Update();

	//出ているお題ごとに抽選する
	for (int i = 0; i < m_max_topic_num; i++)
	{
		//抽選する時間になったら
		if (m_ChooseObjectTimer[i].Finished())
		{
			m_ChooseObjectTimer[i].Reset();
			//タイマーの停止
			m_ChooseObjectTimer[i].SetActive(false);

			ChooseTopic();
		}
	}

	//お題のリセット
	ResetTopic();

	//お題の追加
	if (m_AddTopicTimer.Finished())
	{
		m_AddTopicTimer.Reset();
		AddTopic();
	}

}


void CFallOutGame::ChooseTopic(void)
{

	CFallOutTopic* topic = nullptr;


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
		CFallGimmick* gimmick = (CFallGimmick*)fallInfo.object->GetGimmick();
		gimmick->SetTimer(m_object_delay_time);
		gimmick->SetState(GIMMICK_STATE::PLAY);
		if (m_ExtendTimer.Finished())
		{
			const float extend_time = 1.0f;

			gimmick->AddReturnTime(extend_time);
		}

		topic->SetMarkID(fallInfo.markID);
		topic->SetTimer(m_FallTime);

	}

}

void CFallOutGame::ResetTopic(void)
{
	CGimmickManager::GIMMICK_LIST gimmickList = CGimmickManager::GetInstance().GetList();
	CGimmickManager::GIMMICK_LIST::iterator gimmick_it = gimmickList.begin();
	while (gimmick_it != gimmickList.end())
	{
		GIMMICK_STATE state = (*gimmick_it)->GetState();


		if (state != GIMMICK_STATE::WAIT && m_ExtendTimer.Finished() == false)
			break;
		++gimmick_it;
	}
	//現在出ている最後のお題が抽選され出現中のお題がなく、オブジェクトがすべて待機中なら全てのお題を再抽選
	if (m_ChooseObjectTimer[m_TopicList.size() - 1].GetActive() == true || gimmick_it != gimmickList.end()) return;

	m_ResetTopicTimer.Update();

	if (m_ResetTopicTimer.Finished())
	{
		m_ResetTopicTimer.Reset();
		for (int i = 0; i < m_TopicList.size(); i++)
		{
			m_ChooseObjectTimer[i].SetActive(true);
			m_ChooseObjectTimer[i].SetUp(m_ChooseObjectTimer[0].GetLimitTime() + i * 1.0f);

		}
		TOPIC_LIST::iterator topic_it = m_TopicList.begin();


		while (topic_it != m_TopicList.end())
		{
			CFallOutTopic* topic = (*topic_it);

			if (!topic || topic->GetState() == CFallOutTopic::STATE::APPEAR)
				break;
			topic->SetState(CFallOutTopic::STATE::SWITCHING);
			++topic_it;
		}
	}
}

void CFallOutGame::AddTopic(void)
{
	if (m_TopicList.size() >= m_max_topic_num) return;

	CUI* ui = CUIManager::GetInstance().Create(UI_ID::FALLOUT_TOPIC, m_topic_positionList[m_TopicList.size()]);

	m_TopicList.push_back((CFallOutTopic*)ui);
	m_ChooseObjectTimer[m_TopicList.size()].SetActive(true);
	m_ChooseObjectTimer[m_TopicList.size()].SetUp(m_ChooseObjectTimer[m_TopicList.size() - 1].GetTimer() + m_topic_interval_time);

}

CFallOutGame::FALL_INFO CFallOutGame::ChooseObject(void)
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
		CGimmick* gimmick = (*it)->GetGimmick();
		if (gimmick == nullptr) continue;
		if (gimmick->GetState() == GIMMICK_STATE::WAIT)
		{
			waitObjectList.push_back((*it));
		}
	}

	if (waitObjectList.size() == 1 && m_ExtendTimer.Finished() == false)
	{
		return fallInfo;
	}
	if (waitObjectList.size() == 0) return fallInfo;
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
void CFallOutGame::Finish(void)
{

	CGame::Finish();
	CSoundManager::GetInstance().Finalize();

}

/*
 終了判定
*/
void CFallOutGame::CheckFinish()
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
			if (skill->GetSkillID() == SKILL_ID::RESURRECT_FALLOUT && skill->GetState() != SKILL_STATE::COOLDOWN)
			{
				skill->SetState(SKILL_STATE::ACTIVE);
				return;
			}
			AddRanking(unit->GetUnitID());
			unit->SetDefeatFlag(true);

			CDataManager::GetInstance().AddLastGameRanking(player->GetUnitID());
			//念のため、同一フレームで全滅した場合に一人残すようにする
			if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentPlayer() - 1)
				break;

		}
		++it;
	}

	//二人以上の場合
	if (CDataManager::GetInstance().GetCurrentPlayer() > 1)
	{
		//一人が生き残った時に終了
		if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentPlayer() - 1)
		{
			//生き残った一人を勝ちにする
			CDataManager::GetInstance().PlayerWin((*m_EntryList.begin())->GetUnitID());

			CDataManager::GetInstance().AddLastGameRanking((*m_EntryList.begin())->GetUnitID());
			FinishTopic();
			CGame::SetGameState(GAME_STATE::FINISH);
		}
	}
	else //一人の場合
	{
		//やられたら終了
		if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentPlayer())
		{
			//やられているためリザルトリストから勝ちにする
			CDataManager::GetInstance().PlayerWin((*m_ResultList.begin())->GetUnitID());
			FinishTopic();
			CGame::SetGameState(GAME_STATE::FINISH);
		}
	}
}

void CFallOutGame::FinishTopic(void)
{
	for (TOPIC_LIST::iterator it = m_TopicList.begin(); it != m_TopicList.end(); it++)
	{
		(*it)->SetState(CFallOutTopic::STATE::FINISH);
	}
}

void CFallOutGame::CreateFloor(const CVector3& position)
{
	CObjectManager& om = CObjectManager::GetInstance();

	CTransform transform = m_object_transform_list[(int)MARK_ID::CIRCLE];
	transform.position += position;
	om.Create(OBJECT_ID::CIRCLE_FALL_OBJECT, transform);

	transform = m_object_transform_list[(int)MARK_ID::CROSS];
	transform.position += position;

	om.Create(OBJECT_ID::CROSS_FALL_OBJECT, transform);

	transform = m_object_transform_list[(int)MARK_ID::MOON];
	transform.position += position;

	om.Create(OBJECT_ID::MOON_FALL_OBJECT, transform);

	transform = m_object_transform_list[(int)MARK_ID::SQUARE];
	transform.position += position;

	om.Create(OBJECT_ID::SQUARE_FALL_OBJECT, transform);

	transform = m_object_transform_list[(int)MARK_ID::SUN];
	transform.position += position;

	om.Create(OBJECT_ID::SUN_FALL_OBJECT, transform);

	transform = m_object_transform_list[(int)MARK_ID::TRIANGLE];
	transform.position += position;

	om.Create(OBJECT_ID::TRIANGLE_FALL_OBJECT, transform);

}
