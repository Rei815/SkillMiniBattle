#include "belt_conveyor_game.h"
#include "..\..\..\..\data_manager\data_manager.h"
#include "..\..\..\..\unit_manager\unit_manager.h"
#include "..\..\..\..\unit_manager\unit\player\player.h"
#include "..\..\..\..\object_manager\object_manager.h"
#include "..\..\..\..\camera\camera.h"
#include "..\..\..\..\skill_manager\skill_manager.h"
#include "..\..\..\..\gimmick_manager\gimmick_manager.h"
#include "..\..\..\..\scene_manager\scene_manager.h"

const float		CBeltConveyorGame::m_defeat_height			= -500.0f;
const CVector3	CBeltConveyorGame::m_camera_position		= CVector3(0.0f, 800.0f, -1350.0f);
const CVector3	CBeltConveyorGame::m_camera_direction		= CVector3(0.0f, -0.45f, 0.6f);

const CVector3	CBeltConveyorGame::m_belt_conveyor_position	= CVector3(0.0f, -100.0f, 0.0f);
const float		CBeltConveyorGame::m_belt_conveyor_rotate_y	= -135.0f;
const float     CBeltConveyorGame::m_belt_conveyor_scale	= 0.6f;

const CVector3 CBeltConveyorGame::m_player_spawnpos_list[] =
{
	CVector3(-150, 0,  75),	//Player1
	CVector3( -50, 0,  25),	//Player2
	CVector3(  50, 0, -25),	//Player3
	CVector3( 150, 0, -75)	//Player4
};

const CVector3 CBeltConveyorGame::m_player_default_forward = CVector3(1.0f, 0.0f, 1.0f);


CBeltConveyorGame::CBeltConveyorGame(void)
	: m_StageObject(nullptr)
{

}

CBeltConveyorGame::~CBeltConveyorGame(void)
{

}


void CBeltConveyorGame::Initialize(SCENE_ID scene_id)
{
	SetLightDirection(CVector3::DOWN + CVector3::FORWARD);

	CGame::Initialize(scene_id);

	m_BackGround.Initialize("data\\Textures\\belt_conveyor_bg.png");

	//ステージ生成
	m_StageObject = CObjectManager::GetInstance().Create(OBJECT_ID::BELT_CONVEYOR_STAGE_OBJECT, CTransform(m_belt_conveyor_position, CVector3(0.0f, m_belt_conveyor_rotate_y, 0.0f)));
	m_StageObject->SetScale(m_belt_conveyor_scale);
	
	CCamera::GetInstance().Initialize();
	CCamera::GetInstance().SetPosition(m_camera_position);
	CCamera::GetInstance().SetDirection(m_camera_direction);

	//BGM再生
	CSoundManager::GetInstance().Play_BGM(BGM_ID::MAIN_BGM, true);

	//プレイヤーのスポーン
	for (int i = 0; i < CDataManager::GetInstance().GetCurrentJoinPlayer(); i++)
	{
		std::shared_ptr<IUnit> unit = CUnitManager::GetInstance().Create((UNIT_ID)i, m_player_spawnpos_list[i]);
		std::shared_ptr<CPlayer> Player = dynamic_pointer_cast<CPlayer>(unit);
		if (Player != nullptr)
		{
			Player->SetActionFlag(false);
			Player->SetForwardVector(m_player_default_forward);
		}
		m_EntryList.emplace_back(unit);
	}

	CSkillManager::GetInstance().SetSkill();
	CTransform transform = CTransform();
}

void CBeltConveyorGame::Update(void)
{
	CGame::Update();

	if (!CSceneManager::GetInstance().Pausing())
	{
		CCamera::GetInstance().Update();
	}
}

void CBeltConveyorGame::Draw(void)
{
	m_BackGround.Draw();

	CGame::Draw();
}

void CBeltConveyorGame::Finalize(void)
{
	CGame::Finalize();
	CSoundManager::GetInstance().Finalize();

	CCamera::GetInstance().Finalize();

	//BGM停止
	CSoundManager::GetInstance().Stop_BGM(BGM_ID::MAIN_BGM);
}

void CBeltConveyorGame::Start(void)
{
	CGame::Start();

	//プレイになるタイミングで 、ギミックを付与する
	if(m_GameState == GAME_STATE::PLAY)
		CGimmickManager::GetInstance().Create(GIMMICK_ID::BELT_CONVEYOR_GIMMICK, m_StageObject);
}

void CBeltConveyorGame::Play(void)
{
	CGame::Play();

	//ポーズだったら処理をスキップ
	if (CSceneManager::GetInstance().Pausing())
		return;
}

void CBeltConveyorGame::Finish(void)
{
	CGame::Finish();
}

void CBeltConveyorGame::CheckFinish(void)
{
	CUnitManager::UNIT_LIST unitList = CUnitManager::GetInstance().GetUnitList();
	CUnitManager::UNIT_LIST::iterator it = unitList.begin();
	while (it != unitList.end())
	{
		std::shared_ptr<IUnit> unit = *it;
		++it;

		if (unit->GetDefeatFlag() == true)	continue;

		if (unit->GetPosition().y < m_defeat_height)
		{
			std::shared_ptr<CPlayer> player = dynamic_pointer_cast<CPlayer>(unit);
			if (player != nullptr)
			{
				std::shared_ptr<CSkill> skill = player->GetSkill();
				if (skill->GetSkillID() == SKILL_ID::RESURRECT_BELT && skill->GetState() != SKILL_STATE::COOLDOWN)
				{
					skill->SetState(SKILL_STATE::ACTIVE);
					break;
				}
			}

			AddRanking(unit->GetUnitID());
			unit->SetDefeatFlag(true);

			CDataManager::GetInstance().AddLastGameRanking(unit->GetUnitID());

			//念のため、同一フレームで全滅した場合に一人残すようにする
			if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentJoinPlayer() - 1)
				break;
		}
	}

	if (CDataManager::GetInstance().GetCurrentJoinPlayer() > 1)
	{
		if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentJoinPlayer() - 1)
		{
			//生き残った一人を勝ちにする
			CDataManager::GetInstance().PlayerWin((*m_EntryList.begin())->GetUnitID());

			CDataManager::GetInstance().AddLastGameRanking((*m_EntryList.begin())->GetUnitID());

			CGame::SetGameState(GAME_STATE::FINISH);
		}
	}
	else
	{
		if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentJoinPlayer())
		{
			//やられているためリザルトリストから勝ちにする
			CDataManager::GetInstance().PlayerWin((*m_ResultList.begin())->GetUnitID());

			CGame::SetGameState(GAME_STATE::FINISH);
		}
	}
}