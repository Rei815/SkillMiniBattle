#include "fallout_game.h"
#include "../../../../camera/camera.h"
#include "../../../../object_manager/object_manager.h"
#include "../../../../ui_manager/ui_manager.h"
#include "../../../../ui_manager/ui/fallout_topic/fallout_topic.h"
#include "../../../../data_manager/data_manager.h"
#include "../../../../skill_manager/skill_manager.h"
#include "../../../../sound_manager/sound_manager.h"
#include "../../../../bullet_manager/bullet_manager.h"
#include "game/components/player_component/player_component.h"
#include "game/components/gimmick_component/fall_gimmick_component/fall_gimmick_component.h"
#include "engine/components/transform_component/transform_component.h"

constexpr float floor_x = 475;
constexpr float floor_y = -100;
constexpr float floor_z = 275;

const CTransform CFallOutGame::m_floor_transform_list[] = 
{CTransform(CVector3(floor_x,floor_y,-floor_z)),CTransform(CVector3(-floor_x,floor_y,floor_z)), CTransform(CVector3(0,floor_y,floor_x)),
CTransform(CVector3(-floor_x,floor_y,-floor_z)), CTransform(CVector3(0,floor_y,-floor_x)), CTransform(CVector3(floor_x,floor_y,floor_z)) };

constexpr float topic_x = 250;
constexpr float topic_y = 200;
const vivid::Vector2    CFallOutGame::m_topic_positionList[] = { vivid::Vector2(0, -topic_y),vivid::Vector2(topic_x, -topic_y),vivid::Vector2(topic_x * 2, -topic_y),
vivid::Vector2(topic_x * 3, -topic_y),vivid::Vector2(topic_x * 4, -topic_y),vivid::Vector2(topic_x * 5, -topic_y) };;

const float		CFallOutGame::m_player_spawn_height = 200.0f;
const float		CFallOutGame::m_time_accelerator = 0.1f;
const float		CFallOutGame::m_min_time = 1.5f;
const float		CFallOutGame::m_fall_time = 3.0f;
const float		CFallOutGame::m_defeat_height = -500.0f;
const float		CFallOutGame::m_object_delay_time = 1.0f;
const float		CFallOutGame::m_add_topic_time = 7.0f;
const float		CFallOutGame::m_reset_topic_time = 0.5f;
const float		CFallOutGame::m_extend_return_time = 30.0f;
const float		CFallOutGame::m_topic_interval_time = 1.0f;
const CVector3  CFallOutGame::m_player_default_forward = CVector3(0.0f,0.0f,-1.0f);
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

	//タイマーの初期化
	for (int i = 0; i < m_max_topic_num; i++)
	{
		m_ChooseObjectTimer[i].SetUp(m_FallTime);
		m_ChooseObjectTimer[i].SetActive(false);
	}
	m_AddTopicTimer.SetUp(m_add_topic_time);
	m_ResetTopicTimer.SetUp(m_reset_topic_time);
	m_ExtendTimer.SetUp(m_extend_return_time);

	//カメラの設定
	CCamera::GetInstance().SetPosition(m_camera_position);
	CCamera::GetInstance().SetDirection(m_camera_direction);

	//BGM再生
	CSoundManager::GetInstance().Play_BGM(BGM_ID::MAIN_BGM, true);

	CVector3 playerPos[] = { m_floor_transform_list[(int)MARK_ID::CIRCLE].position, m_floor_transform_list[(int)MARK_ID::CROSS].position,
	m_floor_transform_list[(int)MARK_ID::MOON].position,m_floor_transform_list[(int)MARK_ID::SQUARE].position };

	for (int i = 0; i < CDataManager::GetInstance().GetCurrentJoinPlayer(); i++)
	{
		playerPos[i].y += m_player_spawn_height;
		std::shared_ptr<CGameObject> player = CObjectManager::GetInstance().Create(OBJECT_ID::PLAYER, playerPos[i], (PLAYER_ID)i);
		auto Player = player->GetComponent<PlayerComponent>();
		if (Player != nullptr)
		{
			Player->SetActionFlag(false);
			Player->SetForwardVector(m_player_default_forward);
		}
		m_EntryList.emplace_back(player);

	}
	CBulletManager::GetInstance().Initialize();
	CSkillManager::GetInstance().SetSkill();
	CObjectManager& om = CObjectManager::GetInstance();

	//各床にギミックを設定
	std::shared_ptr<CGameObject> object = nullptr;
	object = om.Create(OBJECT_ID::FALL_FLOOR_CIRCLE,m_floor_transform_list[(int)MARK_ID::CIRCLE]);
	object = om.Create(OBJECT_ID::FALL_FLOOR_CROSS,m_floor_transform_list[(int)MARK_ID::CROSS]);
	object = om.Create(OBJECT_ID::FALL_FLOOR_MOON,m_floor_transform_list[(int)MARK_ID::MOON]);
	object = om.Create(OBJECT_ID::FALL_FLOOR_SQUARE,m_floor_transform_list[(int)MARK_ID::SQUARE]);
	object = om.Create(OBJECT_ID::FALL_FLOOR_SUN,m_floor_transform_list[(int)MARK_ID::SUN]);
	object = om.Create(OBJECT_ID::FALL_FLOOR_TRIANGLE,m_floor_transform_list[(int)MARK_ID::TRIANGLE]);
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
	CBulletManager::GetInstance().Draw();

	CGame::Draw();
}

void CFallOutGame::Finalize(void)
{
	m_BackGround.Finalize();
	CGame::Finalize();
	CBulletManager::GetInstance().Finalize();

	CCamera::GetInstance().Finalize();

	CSoundManager::GetInstance().Stop_BGM(BGM_ID::MAIN_BGM);
}

void CFallOutGame::Start(void)
{
	CGame::Start();
	if (m_WaitTimer.Finished())
	{
		std::shared_ptr<CFallOutTopic> topic = std::dynamic_pointer_cast<CFallOutTopic>(CUIManager::GetInstance().Create(UI_ID::FALLOUT_TOPIC, m_topic_positionList[m_TopicList.size()]));

		m_TopicList.emplace_back(topic);
		m_ChooseObjectTimer[m_TopicList.size() - 1].SetActive(true);

		// 新しく追加されたお題に対応するタイマーをアクティブにする
		// ここで m_TopicList.size() は新しい要素が追加された後のサイズ
		if (!m_TopicList.empty() && m_TopicList.size() <= m_max_topic_num) 
		{
			m_ChooseObjectTimer[m_TopicList.size() - 1].SetActive(true);
		}
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

			m_ChooseObjectTimer[i].SetActive(false);
			//お題の選択を開始
			ChooseTopic();
		}
	}

	//お題のリセット
	ResetTopic();
}


void CFallOutGame::ChooseTopic(void)
{
	std::shared_ptr<CFallOutTopic> topic = nullptr;

	TOPIC_LIST::iterator it = m_TopicList.begin();
	bool chooseFlag = false;
	while (it != m_TopicList.end())
	{
		topic = (*it);
		//取得に失敗したら早期コンティニュー
		if (!topic) { ++it; continue; }

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
	FALL_OBJECT＿INFO fallInfo = ChooseObject();

	if (fallInfo.object == nullptr) return;

	if (fallInfo.object->GetID() != OBJECT_ID::NONE)
	{

		//落下の開始
		auto FallGimmickComp = fallInfo.object->GetComponent<FallGimmickComponent>();
		FallGimmickComp->SetTimer(m_object_delay_time);
		FallGimmickComp->SetState(GIMMICK_STATE::PLAY);

		//段々と床の復活が遅くなる
		if (m_ExtendTimer.Finished())
		{
			const float extend_time = 1.0f;

			FallGimmickComp->AddReturnTime(extend_time);
		}

		topic->SetMarkID(fallInfo.markID);
		topic->SetTimer(m_FallTime);

	}

}

void CFallOutGame::ResetTopic(void)
{
	bool allGimmicksWaiting = true;
	if (!m_ExtendTimer.Finished())
	{
		//ObjectManagerから、FallGimmickComponentを持つオブジェクトを全て取得
		auto gimmickObjects = CObjectManager::GetInstance().GetObjectsWithComponent<FallGimmickComponent>();

		//取得した全ギミックオブジェクトをループ
		for (const auto& gimmickObject : gimmickObjects)
		{
			//オブジェクトからFallGimmickComponentを取得
			auto gimmickComp = gimmickObject->GetComponent<FallGimmickComponent>();
			if (gimmickComp)
			{
				//コンポーネントの状態をチェック
				if (gimmickComp->GetState() != GIMMICK_STATE::WAIT)
				{
					allGimmicksWaiting = false;
					break;
				}
			}
		}
	}
	bool allTopicsChosen = true;

	// 現在表示されているお題の数だけチェック
	for (int i = 0; i < m_TopicList.size(); ++i)
	{
		//お題が抽選されていない
		if (m_ChooseObjectTimer[i].IsActive()) 
		{
			allTopicsChosen = false;
			break;
		}
	}

	// すべてのギミックが待機中で、かつ、すべてのお題が抽選された場合に再抽選
	// いずれかが満たされない場合は再抽選しない
	if (!allGimmicksWaiting || !allTopicsChosen) return;

	m_ResetTopicTimer.Update();

	if (m_ResetTopicTimer.Finished())
	{
		m_ResetTopicTimer.Reset();

		//時間をずらす
		for (int i = 0; i < m_TopicList.size(); i++)
		{

			m_ChooseObjectTimer[i].SetActive(true);
			m_ChooseObjectTimer[i].SetUp(m_ChooseObjectTimer[0].GetLimitTime() + i * 1.0f);
		}

		TOPIC_LIST::iterator topic_it = m_TopicList.begin();


		while (topic_it != m_TopicList.end())
		{
			std::shared_ptr<CFallOutTopic> topic = *topic_it;

			if (!topic || topic->GetState() == CFallOutTopic::STATE::APPEAR)
				break;
			topic->SetState(CFallOutTopic::STATE::SWITCHING);
			++topic_it;
		}

		//お題の追加
		AddTopic();
	}

}

void CFallOutGame::AddTopic(void)
{
	if (m_TopicList.size() >= m_max_topic_num) return;

	std::shared_ptr<CFallOutTopic> topic = std::dynamic_pointer_cast<CFallOutTopic>(CUIManager::GetInstance().Create(UI_ID::FALLOUT_TOPIC, m_topic_positionList[m_TopicList.size()]));

	m_TopicList.emplace_back(topic);
	// m_ChooseObjectTimer のインデックスは新しい要素が追加された後の m_TopicList.size() - 1
	if (m_TopicList.size() - 1 < m_max_topic_num)
	{
		m_ChooseObjectTimer[m_TopicList.size() - 1].SetActive(true);

		//ひとつ前のタイマーの制限時間から少し増やす
		float prev_timer_limit = (m_TopicList.size() - 2 >= 0) ? m_ChooseObjectTimer[m_TopicList.size() - 2].GetLimitTime() : m_FallTime;
		m_ChooseObjectTimer[m_TopicList.size() - 1].SetUp(prev_timer_limit + m_topic_interval_time);
	}
}

CFallOutGame::FALL_OBJECT＿INFO CFallOutGame::ChooseObject(void)
{
	FALL_OBJECT＿INFO fallInfo;

	int index = (int)OBJECT_ID::NONE;

	CObjectManager::OBJECT_LIST objectList = CObjectManager::GetInstance().GetList();

	if (objectList.empty()) return fallInfo;

	CObjectManager::OBJECT_LIST waitObjectList;
	CObjectManager::OBJECT_LIST::iterator it;

	// --- 1. FallGimmickComponentを持つオブジェクトをチェック ---
	auto fallGimmickObjects = CObjectManager::GetInstance().GetObjectsWithComponent<FallGimmickComponent>();
	for (const auto& object : fallGimmickObjects)
	{
		auto comp = object->GetComponent<FallGimmickComponent>();
		if (comp && comp->GetState() == GIMMICK_STATE::WAIT)
		{
			waitObjectList.push_back(object);
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
	switch ((*it)->GetID())
	{
	case OBJECT_ID::FALL_FLOOR_MOON:		fallInfo.markID = MARK_ID::MOON;		break;
	case OBJECT_ID::FALL_FLOOR_CIRCLE:		fallInfo.markID = MARK_ID::CIRCLE;		break;
	case OBJECT_ID::FALL_FLOOR_CROSS:		fallInfo.markID = MARK_ID::CROSS;		break;
	case OBJECT_ID::FALL_FLOOR_SQUARE:		fallInfo.markID = MARK_ID::SQUARE;		break;
	case OBJECT_ID::FALL_FLOOR_SUN:		fallInfo.markID = MARK_ID::SUN;			break;
	case OBJECT_ID::FALL_FLOOR_TRIANGLE:	fallInfo.markID = MARK_ID::TRIANGLE;	break;
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
	// 毎フレーム、PlayerComponentを持つオブジェクトを全て取得
	auto activePlayers = CObjectManager::GetInstance().GetObjectsWithComponent<PlayerComponent>();

	// --- 脱落プレイヤーのチェック ---
	for (auto& playerObject : activePlayers)
	{
		auto playerComp = playerObject->GetComponent<PlayerComponent>();
		auto transform = playerObject->GetComponent<TransformComponent>();

		if (!playerComp || !transform) continue;

		if (playerComp->IsDefeated())
		{
			continue;
		}

		// 落下判定
		if (transform->GetPosition().y < m_defeat_height)
		{
			auto skill = playerComp->GetSkill();
			if (skill->GetSkillID() == SKILL_ID::RESURRECT_FALLOUT && skill->GetState() != SKILL_STATE::COOLDOWN)
			{
				skill->SetState(SKILL_STATE::ACTIVE);
				continue;
			}
			// 敗北処理
			playerComp->SetDefeated(true);
			AddRanking(playerComp->GetPlayerID());
			CDataManager::GetInstance().AddLastGameRanking(playerComp->GetPlayerID());
			//念のため、同一フレームで全滅した場合に一人残すようにする
			if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentJoinPlayer() - 1)
				break;
		}
	}


	//二人以上の場合
	if (CDataManager::GetInstance().GetCurrentJoinPlayer() > 1)
	{
		auto winnerComp = m_EntryList.begin()->get()->GetComponent<PlayerComponent>();
		//一人が生き残った時に終了
		if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentJoinPlayer() - 1)
		{
			//生き残った一人を勝ちにする
			CDataManager::GetInstance().PlayerWin(winnerComp->GetPlayerID());

			CDataManager::GetInstance().AddLastGameRanking(winnerComp->GetPlayerID());
			FinishTopic();
			CGame::SetGameState(GAME_STATE::FINISH);
		}
	}
	else //一人の場合
	{
		auto winnerComp = m_ResultList.begin()->get()->GetComponent<PlayerComponent>();

		//やられたら終了
		if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentJoinPlayer())
		{
			//やられているためリザルトリストから勝ちにする
			CDataManager::GetInstance().PlayerWin(winnerComp->GetPlayerID());
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