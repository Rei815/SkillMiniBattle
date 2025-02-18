#include "belt_conveyor_game.h"
#include "..\..\..\..\data_manager\data_manager.h"
#include "..\..\..\..\unit_manager\unit_manager.h"
#include "..\..\..\..\unit_manager\unit\player\player.h"
#include "..\..\..\..\object_manager\object_manager.h"
#include "..\..\..\..\camera\camera.h"
#include "..\..\..\..\skill_manager\skill_manager.h"
#include "..\..\..\..\gimmick_manager\gimmick_manager.h"

const float		CBeltConveyorGame::m_defeat_height			= -500.0f;
const CVector3	CBeltConveyorGame::m_camera_position		= CVector3(0.0f, 900.0f, -1350.0f);
const CVector3	CBeltConveyorGame::m_camera_direction		= CVector3(0.0f, -0.6f, 0.6f);

const CVector3	CBeltConveyorGame::m_belt_conveyor_position	= CVector3(0.0f, -100.0f, 0.0f);
const float		CBeltConveyorGame::m_belt_conveyor_rotate_y	= -135.0f;
const float     CBeltConveyorGame::m_belt_conveyor_scale = 0.6f;

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
	CGame::Initialize(scene_id);

	//ステージ生成
	m_StageObject = CObjectManager::GetInstance().Create(OBJECT_ID::BELT_CONVEYOR_STAGE_OBJECT, CTransform(m_belt_conveyor_position, CVector3(0.0f, m_belt_conveyor_rotate_y, 0.0f)));
	m_StageObject->SetScale(m_belt_conveyor_scale);
	
	CCamera::GetInstance().Initialize();
	CCamera::GetInstance().SetPosition(m_camera_position);
	CCamera::GetInstance().SetDirection(m_camera_direction);

	//BGM再生
	CSoundManager::GetInstance().Play_BGM(BGM_ID::MAIN_BGM, true);

	//
	m_DebugText = "ベルトコンベアゲーム";

	//プレイヤーのスポーン
	for (int i = 0; i < CDataManager::GetInstance().GetCurrentPlayer(); i++)
	{
		IUnit* unit = CUnitManager::GetInstance().Create((UNIT_ID)i, m_player_spawnpos_list[i]);
		CPlayer* Player = dynamic_cast<CPlayer*>(unit);
		if (Player != nullptr)
		{
			Player->SetActionFlag(false);
			Player->SetForwardVector(m_player_default_forward);
		}
		m_EntryList.push_back(unit);
	}

	CSkillManager::GetInstance().SetSkill();
}

void CBeltConveyorGame::Update(void)
{
	CGame::Update();

	if (!m_PauseFlag)
	{
		CCamera::GetInstance().Update();
	}
}

void CBeltConveyorGame::Draw(void)
{
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
	if (m_PauseFlag)
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
		IUnit* unit = (*it);
		++it;

		if (unit->GetDefeatFlag() == true)	continue;

		if (unit->GetPosition().y < m_defeat_height)
		{
			/*
			CPlayer* player = dynamic_cast<CPlayer*>(unit);
			if (player != nullptr)
			{
				CSkill* skill = player->GetSkill();
				if (skill->GetSkillID() == SKILL_ID::RESURRECT_FALLOUT && skill->GetState() != SKILL_STATE::COOLDOWN)
				{
					skill->SetState(SKILL_STATE::ACTIVE);
					break;
				}
			}
			*/

			AddRanking(unit->GetUnitID());
			unit->SetDefeatFlag(true);

			CDataManager::GetInstance().AddLastGameRanking(unit->GetUnitID());

			//念のため、同一フレームで全滅した場合に一人残すようにする
			if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentPlayer() - 1)
				break;
		}
	}

	if (CDataManager::GetInstance().GetCurrentPlayer() > 1)
	{
		if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentPlayer() - 1)
		{
			//生き残った一人を勝ちにする
			CDataManager::GetInstance().PlayerWin((*m_EntryList.begin())->GetUnitID());

			CDataManager::GetInstance().AddLastGameRanking((*m_EntryList.begin())->GetUnitID());

			CGame::SetGameState(GAME_STATE::FINISH);
		}
	}
	else
	{
		if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentPlayer())
		{
			//やられているためリザルトリストから勝ちにする
			CDataManager::GetInstance().PlayerWin((*m_ResultList.begin())->GetUnitID());

			CGame::SetGameState(GAME_STATE::FINISH);
		}
	}
}