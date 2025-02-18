#include "maze_game.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../gimmick_manager/gimmick_manager.h"
#include "../../../../camera/camera.h"
#include "../../../../object_manager/object_manager.h"
#include "../../../../ui_manager/ui_manager.h"
#include "../../../../data_manager/data_manager.h"
#include "../../../../skill_manager/skill_manager.h"
#include "../../../../sound_manager/sound_manager.h"


const CVector3  CMazeGame::m_player_default_forward = CVector3(0.0f, 0.0f, -1.0f);
const CVector3	CMazeGame::m_camera_position = CVector3(0, 2500.0f, -1500.0f);
const CVector3	CMazeGame::m_camera_direction = CVector3(0.0f, -1.0f, 0.5f);
const CVector3	CMazeGame::m_player_position[] = {
	CVector3(0.0f, 100.0f, 1.0f),CVector3(0.0f, 100.0f, 1.0f),CVector3(0.0f, 100.0f, 1.0f),CVector3(0.0f, 100.0f, 1.0f) };
CMazeGame::CMazeGame(void)
{
}

CMazeGame::~CMazeGame(void)
{
}

void CMazeGame::Initialize(SCENE_ID scene_id)
{
	CGame::Initialize(scene_id);
	CGame::Initialize(scene_id);
	CCamera::GetInstance().Initialize();
	CCamera::GetInstance().SetPosition(m_camera_position);
	CCamera::GetInstance().SetDirection(m_camera_direction);
	//BGM再生
	CSoundManager::GetInstance().Play_BGM(BGM_ID::MAIN_BGM, true);
	//
	for (int i = 0; i < CDataManager::GetInstance().GetCurrentPlayer(); i++)
	{
		IUnit* unit = CUnitManager::GetInstance().Create((UNIT_ID)i, m_player_position[i]);
		CPlayer* Player = dynamic_cast<CPlayer*>(unit);
		if (Player != nullptr)
		{
			Player->SetActionFlag(false);
			Player->SetForwardVector(m_player_default_forward);
		}
		m_EntryList.push_back(unit);

	}

	CSkillManager::GetInstance().SetSkill();

	CObjectManager::GetInstance().Create(OBJECT_ID::MAZE_STAGE, CTransform());

	SetLightEnable(false);
	CTransform transform;
	transform.position = m_player_position[0];
	m_Light.Initialize(transform, CVector3::DOWN, GetColorF(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, CLight::LIGHT_TYPE::DIRECTIONAL);

}

void CMazeGame::Update(void)
{
	CGame::Update();
	m_Light.Update();

	CCamera::GetInstance().Update();

}

void CMazeGame::Draw(void)
{
	m_Light.Draw();
	CGame::Draw();
}

void CMazeGame::Finalize(void)
{
	CGame::Finalize();
	CCamera::GetInstance().Finalize();

	//BGM停止
	CSoundManager::GetInstance().Stop_BGM(BGM_ID::MAIN_BGM);
	//
}

void CMazeGame::Start(void)
{
	CGame::Start();
}

void CMazeGame::Play(void)
{
	CGame::Play();

}

void CMazeGame::Finish(void)
{

	CGame::Finish();
	CSoundManager::GetInstance().Finalize();

}

/*
 終了判定
*/
void CMazeGame::CheckFinish()
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

		//if (unit->GetPosition().y < m_defeat_height)
		//{
		//	CPlayer* player = (CPlayer*)unit;

		//	CSkill* skill = player->GetSkill();
		//	if (skill->GetSkillID() == SKILL_ID::RESURRECT_FALLOUT && skill->GetState() != SKILL_STATE::COOLDOWN)
		//	{
		//		skill->SetState(SKILL_STATE::ACTIVE);
		//		return;
		//	}
		//	AddRanking(unit->GetUnitID());
		//	unit->SetDefeatFlag(true);

		//	CDataManager::GetInstance().AddLastGameRanking(player->GetUnitID());
		//	//念のため、同一フレームで全滅した場合に一人残すようにする
		//	if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentPlayer() - 1)
		//		break;

		//}
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
			CGame::SetGameState(GAME_STATE::FINISH);
		}
	}
}