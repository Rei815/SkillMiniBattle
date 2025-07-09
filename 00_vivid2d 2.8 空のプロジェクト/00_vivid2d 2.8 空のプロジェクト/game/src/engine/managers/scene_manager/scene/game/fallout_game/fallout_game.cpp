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

	//�^�C�}�[�̏�����
	for (int i = 0; i < m_max_topic_num; i++)
	{
		m_ChooseObjectTimer[i].SetUp(m_FallTime);
		m_ChooseObjectTimer[i].SetActive(false);
	}
	m_AddTopicTimer.SetUp(m_add_topic_time);
	m_ResetTopicTimer.SetUp(m_reset_topic_time);
	m_ExtendTimer.SetUp(m_extend_return_time);

	//�J�����̐ݒ�
	CCamera::GetInstance().SetPosition(m_camera_position);
	CCamera::GetInstance().SetDirection(m_camera_direction);

	//BGM�Đ�
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

	//�e���ɃM�~�b�N��ݒ�
	std::shared_ptr<CGameObject> object = nullptr;
	object = om.Create(OBJECT_ID::FALL_FLOOR_CIRCLE,m_floor_transform_list[(int)MARK_ID::CIRCLE]);
	object = om.Create(OBJECT_ID::FALL_FLOOR_CROSS,m_floor_transform_list[(int)MARK_ID::CROSS]);
	object = om.Create(OBJECT_ID::FALL_FLOOR_MOON,m_floor_transform_list[(int)MARK_ID::MOON]);
	object = om.Create(OBJECT_ID::FALL_FLOOR_SQUARE,m_floor_transform_list[(int)MARK_ID::SQUARE]);
	object = om.Create(OBJECT_ID::FALL_FLOOR_SUN,m_floor_transform_list[(int)MARK_ID::SUN]);
	object = om.Create(OBJECT_ID::FALL_FLOOR_TRIANGLE,m_floor_transform_list[(int)MARK_ID::TRIANGLE]);
	m_RandEngine.seed(std::random_device()());

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

		// �V�����ǉ����ꂽ����ɑΉ�����^�C�}�[���A�N�e�B�u�ɂ���
		// ������ m_TopicList.size() �͐V�����v�f���ǉ����ꂽ��̃T�C�Y
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

	//�o�Ă��邨�育�Ƃɒ��I����
	for (int i = 0; i < m_max_topic_num; i++)
	{
		//���I���鎞�ԂɂȂ�����
		if (m_ChooseObjectTimer[i].Finished())
		{
			m_ChooseObjectTimer[i].Reset();

			m_ChooseObjectTimer[i].SetActive(false);
			//����̑I�����J�n
			ChooseTopic();
		}
	}

	//����̃��Z�b�g
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
		//�擾�Ɏ��s�����瑁���R���e�B�j���[
		if (!topic) { ++it; continue; }

		//�؂�ւ���Ă��鎞�݂̂ɂ���̎w��
		if (topic->GetState() == CFallOutTopic::STATE::SWITCHING)
		{
			chooseFlag = true; 
			break;
		}
		++it;
	}

	if (!chooseFlag) return;

	//���I����
	FALL_OBJECT�QINFO fallInfo = ChooseObject();

	if (fallInfo.object == nullptr) return;

	if (fallInfo.object->GetID() != OBJECT_ID::NONE)
	{

		//�����̊J�n
		auto FallGimmickComp = fallInfo.object->GetComponent<FallGimmickComponent>();
		FallGimmickComp->SetTimer(m_object_delay_time);
		FallGimmickComp->SetState(GIMMICK_STATE::PLAY);

		//�i�X�Ə��̕������x���Ȃ�
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
		// 1. ObjectManager����AFallGimmickComponent�����I�u�W�F�N�g��S�Ď擾
		// ��m_ObjectManager�̓V�[���������Ă���C���X�^���X�ϐ�
		auto gimmickObjects = CObjectManager::GetInstance().GetObjectsWithComponent<FallGimmickComponent>();

		// 2. �擾�����S�M�~�b�N�I�u�W�F�N�g�����[�v
		for (const auto& gimmickObject : gimmickObjects)
		{
			// 3. �I�u�W�F�N�g����FallGimmickComponent���擾
			auto gimmickComp = gimmickObject->GetComponent<FallGimmickComponent>();
			if (gimmickComp)
			{
				// 4. �R���|�[�l���g�̏�Ԃ��`�F�b�N
				if (gimmickComp->GetState() != GIMMICK_STATE::WAIT)
				{
					allGimmicksWaiting = false;
					break;
				}
			}
		}
	}
	bool allTopicsChosen = true;

	// ���ݕ\������Ă��邨��̐������`�F�b�N
	for (int i = 0; i < m_TopicList.size(); ++i)
	{
		//���肪���I����Ă��Ȃ�
		if (m_ChooseObjectTimer[i].IsActive()) 
		{
			allTopicsChosen = false;
			break;
		}
	}

	// ���ׂẴM�~�b�N���ҋ@���ŁA���A���ׂĂ̂��肪���I���ꂽ�ꍇ�ɍĒ��I
	// �����ꂩ����������Ȃ��ꍇ�͍Ē��I���Ȃ�
	if (!allGimmicksWaiting || !allTopicsChosen) return;

	m_ResetTopicTimer.Update();

	if (m_ResetTopicTimer.Finished())
	{
		m_ResetTopicTimer.Reset();

		//���Ԃ����炷
		for (int i = 0; i < m_TopicList.size(); i++)
			m_ChooseObjectTimer[i].SetUp(m_ChooseObjectTimer[0].GetLimitTime() + i * 1.0f);

		TOPIC_LIST::iterator topic_it = m_TopicList.begin();


		while (topic_it != m_TopicList.end())
		{
			std::shared_ptr<CFallOutTopic> topic = *topic_it;

			if (!topic || topic->GetState() == CFallOutTopic::STATE::APPEAR)
				break;
			topic->SetState(CFallOutTopic::STATE::SWITCHING);
			++topic_it;
		}

		//����̒ǉ�
		AddTopic();
	}

}

void CFallOutGame::AddTopic(void)
{
	if (m_TopicList.size() >= m_max_topic_num) return;

	std::shared_ptr<CFallOutTopic> topic = std::dynamic_pointer_cast<CFallOutTopic>(CUIManager::GetInstance().Create(UI_ID::FALLOUT_TOPIC, m_topic_positionList[m_TopicList.size()]));

	m_TopicList.emplace_back(topic);
	// m_ChooseObjectTimer �̃C���f�b�N�X�͐V�����v�f���ǉ����ꂽ��� m_TopicList.size() - 1
	if (m_TopicList.size() - 1 < m_max_topic_num)
	{
		m_ChooseObjectTimer[m_TopicList.size() - 1].SetActive(true);

		//�ЂƂO�̃^�C�}�[�̐������Ԃ��班�����₷
		float prev_timer_limit = (m_TopicList.size() - 2 >= 0) ? m_ChooseObjectTimer[m_TopicList.size() - 2].GetLimitTime() : m_FallTime;
		m_ChooseObjectTimer[m_TopicList.size() - 1].SetUp(prev_timer_limit + m_topic_interval_time);
	}
}

CFallOutGame::FALL_OBJECT�QINFO CFallOutGame::ChooseObject(void)
{
	FALL_OBJECT�QINFO fallInfo;

	int index = (int)OBJECT_ID::NONE;

	CObjectManager::OBJECT_LIST objectList = CObjectManager::GetInstance().GetList();

	if (objectList.empty()) return fallInfo;

	CObjectManager::OBJECT_LIST waitObjectList;
	CObjectManager::OBJECT_LIST::iterator it;

	// --- 1. FallGimmickComponent�����I�u�W�F�N�g���`�F�b�N ---
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
 �I������
*/
void CFallOutGame::CheckFinish()
{
	// ���t���[���APlayerComponent�����I�u�W�F�N�g��S�Ď擾
	auto activePlayers = CObjectManager::GetInstance().GetObjectsWithComponent<PlayerComponent>();

	// --- �E���v���C���[�̃`�F�b�N ---
	for (auto& playerObject : activePlayers)
	{
		auto playerComp = playerObject->GetComponent<PlayerComponent>();
		auto transform = playerObject->GetComponent<TransformComponent>();

		if (!playerComp || !transform) continue;

		if (playerComp->IsDefeated())
		{
			continue;
		}

		// ��������
		if (transform->GetPosition().y < m_defeat_height)
		{
			auto skill = playerComp->GetSkill();
			if (skill->GetSkillID() == SKILL_ID::RESURRECT_FALLOUT && skill->GetState() != SKILL_STATE::COOLDOWN)
			{
				skill->SetState(SKILL_STATE::ACTIVE);
				continue;
			}
			// �s�k����
			playerComp->SetDefeated(true);
			AddRanking(playerComp->GetPlayerID());
			CDataManager::GetInstance().AddLastGameRanking(playerComp->GetPlayerID());
			//�O�̂��߁A����t���[���őS�ł����ꍇ�Ɉ�l�c���悤�ɂ���
			if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentJoinPlayer() - 1)
				break;
		}
	}


	//��l�ȏ�̏ꍇ
	if (CDataManager::GetInstance().GetCurrentJoinPlayer() > 1)
	{
		auto winnerComp = m_EntryList.begin()->get()->GetComponent<PlayerComponent>();
		//��l�������c�������ɏI��
		if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentJoinPlayer() - 1)
		{
			//�����c������l�������ɂ���
			CDataManager::GetInstance().PlayerWin(winnerComp->GetPlayerID());

			CDataManager::GetInstance().AddLastGameRanking(winnerComp->GetPlayerID());
			FinishTopic();
			CGame::SetGameState(GAME_STATE::FINISH);
		}
	}
	else //��l�̏ꍇ
	{
		auto winnerComp = m_ResultList.begin()->get()->GetComponent<PlayerComponent>();

		//���ꂽ��I��
		if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentJoinPlayer())
		{
			//����Ă��邽�߃��U���g���X�g���珟���ɂ���
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