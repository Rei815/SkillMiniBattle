#include "dodgeball_game.h"
#include "../../../../data_manager/data_manager.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../gimmick_manager/gimmick_manager.h"
#include "../../../../gimmick_manager/gimmick/dodgeball_gimmick/dodgeball_gimmick.h"
#include "../../../../camera/camera.h"
#include "../../../../object_manager/object_manager.h"
#include "../../../../ui_manager/ui_manager.h"
#include "../../../../bullet_manager/bullet_manager.h"
#include "../../../../launcher/launcher.h"

#include "../../../../skill_manager/skill_manager.h"

//上下左右の4方向 × 各方向に3つずつ ＝ 12こ
const CVector3		CDodgeBallGame::m_cannon_pos_list[] = 
{
	CVector3(    0,   0, 1800),CVector3(  900,   0, 1550),CVector3(- 900,   0, 1550),	//上
	CVector3(    0,   0,-1800),CVector3(- 900,   0,-1550),CVector3(  900,   0,-1550),	//下
	CVector3( 1800,   0,    0),CVector3( 1550,   0,- 900),CVector3( 1550,   0,  900),	//右
	CVector3(-1800,   0,    0),CVector3(-1550,   0,  900),CVector3(-1550,   0,- 900)	//左
};

//上下左右の4方向
const CVector3		CDodgeBallGame::m_cannon_rot_list[] = 
{
	CVector3(0, 180,0),CVector3(0, 210,0),CVector3(0, 150,0),	//上
	CVector3(0,   0,0),CVector3(0,  30,0),CVector3(0, -30,0),	//下
	CVector3(0, -90,0),CVector3(0, -60,0),CVector3(0,-120,0),	//右
	CVector3(0,  90,0),CVector3(0, 120,0),CVector3(0,  60,0)	//左
};

const CVector3 CDodgeBallGame::m_player_spawnpos_list[] =
{
	CVector3(-100, 0,  100),	//Player1
	CVector3( 100, 0,  100),	//Player2
	CVector3(-100, 0, -100),	//Player3
	CVector3( 100, 0, -100)		//Player4
};

const int			CDodgeBallGame::m_max_cannnon_count = 3;
const float			CDodgeBallGame::m_cannnon_spawn_time = 3.0f;
const float			CDodgeBallGame::m_initial_shot_time = 2.0f;
const float			CDodgeBallGame::m_min_shot_time = 0.1f;
const float			CDodgeBallGame::m_shot_time_acceleration = 0.03f;
const float			CDodgeBallGame::m_defeat_distance = 3000.0f;
const CVector3		CDodgeBallGame::m_camera_position = CVector3(0, 2500.0f, -1800.0f);
const CVector3		CDodgeBallGame::m_camera_direction = CVector3(0, -1.0f, 0.6f);

CDodgeBallGame::CDodgeBallGame(void)
	:m_CannonCount(0)
	,m_SpawnTimer()
	,m_ShotTimer()
	,m_NowShotTime(m_initial_shot_time)
	,m_NextCannnonDir(CANNON_DIRECTION::UP)

{
}

CDodgeBallGame::~CDodgeBallGame(void)
{

}

void CDodgeBallGame::Initialize(SCENE_ID scene_id)
{
	m_SpawnTimer.SetUp(0);
	m_ShotTimer.SetUp(m_initial_shot_time);
	CGame::Initialize(scene_id);

	//CStage::GetInstance().Initialize();
	CObjectManager::GetInstance().Create(OBJECT_ID::DODGEBALL_STAGE_OBJECT,CTransform(CVector3(0.0f,-100.0f,0.0f)));

	CCamera::GetInstance().Initialize();
	CCamera::GetInstance().SetPosition(m_camera_position);
	CCamera::GetInstance().SetDirection(m_camera_direction);
	m_DebugText = "ドッジボールゲーム";

	//プレイヤーのスポーン
	for (int i = 0; i < CDataManager::GetInstance().GetCurrentPlayer(); i++)
	{
		IUnit* unit = CUnitManager::GetInstance().Create((UNIT_ID)i, m_player_spawnpos_list[i]);
		m_EntryList.push_back(unit);
	}

	CSkillManager::GetInstance().SetSkill();

	CLauncher::GetInstance().Initialize();
	CBulletManager::GetInstance().Initialize();
}

void CDodgeBallGame::Update(void)
{
	//CStage::GetInstance().Update();
	CGame::Update();
	CCamera::GetInstance().Update();
	CLauncher::GetInstance().Update();
	CBulletManager::GetInstance().Update();
}

void CDodgeBallGame::Draw(void)
{
	//CStage::GetInstance().Draw();
	CGame::Draw();
	CBulletManager::GetInstance().Draw();
}

void CDodgeBallGame::Finalize(void)
{
	CGame::Finalize();
	//CStage::GetInstance().Finalize();
	CCamera::GetInstance().Finalize();
	CLauncher::GetInstance().Finalize();
	CBulletManager::GetInstance().Finalize();
}

void CDodgeBallGame::Start(void)
{
	CGame::Start();
}

void CDodgeBallGame::Play(void)
{
	CGame::Play();
	
	if (m_CannonCount < m_max_cannnon_count)
	{
		m_SpawnTimer.Update();

		if (m_SpawnTimer.Finished())
		{
			m_SpawnTimer.SetUp(m_cannnon_spawn_time);

			//大砲の生成
			SpawnCannnon();

			//次の砲の向きを変更
			int Temp = (int)m_NextCannnonDir;
			Temp++;
			if (Temp > (int)CANNON_DIRECTION::LEFT)
			{
				Temp = (int)CANNON_DIRECTION::UP;
				m_CannonCount++;
			}
			m_NextCannnonDir = (CANNON_DIRECTION)Temp;
		}
	}

	m_ShotTimer.Update();
	if (m_ShotTimer.Finished())
	{
		if (m_NowShotTime > m_min_shot_time)
		{
			m_NowShotTime -= m_shot_time_acceleration * m_NowShotTime;

			if (m_NowShotTime < m_min_shot_time)
				m_NowShotTime = m_min_shot_time;
		}

		m_ShotTimer.SetUp(m_NowShotTime);

		IObject* temp = ChooseCannon();
		if(temp != nullptr)
			temp->GetGimmick()->SetSwitch(true);
	}
}

void CDodgeBallGame::Finish(void)
{
	CGame::Finish();
}

/*!
	 *  @brief      終了判定
	 */
void CDodgeBallGame::CheckFinish(void)
{
	CUnitManager::UNIT_LIST unitList = CUnitManager::GetInstance().GetUnitList();
	CUnitManager::UNIT_LIST::iterator it = unitList.begin();
	while (it != unitList.end())
	{
		IUnit* unit = (*it);
		++it;

		if (unit->GetDefeatFlag() == true)	continue;

		if (unit->GetPosition().Length() > m_defeat_distance)
		{
			AddRanking(unit->GetUnitID());
			unit->SetDefeatFlag(true);
		}
	}


	if (m_ResultList.size() == CDataManager::GetInstance().GetCurrentPlayer())
		CGame::SetGameState(GAME_STATE::FINISH);
}

void CDodgeBallGame::SpawnCannnon(void)
{

	//大砲オブジェクトの生成座標および生成回転値のセット
	CTransform Temp;
	Temp.position = m_cannon_pos_list[(int)m_NextCannnonDir * 3 + m_CannonCount];
	Temp.rotation = m_cannon_rot_list[(int)m_NextCannnonDir * 3 + m_CannonCount];

	//大砲オブジェクトの生成
	IObject* CannonObject = CObjectManager::GetInstance().Create(OBJECT_ID::CANNON_OBJECT, Temp);

	//大砲ギミックのセット
	CGimmickManager::GetInstance().Create(GIMMICK_ID::DODGEBALL_GIMMICK, CannonObject);
}


IObject* CDodgeBallGame::ChooseCannon(void)
{
	CObjectManager::OBJECT_LIST objectList = CObjectManager::GetInstance().GetList();

	if (objectList.empty())
		return nullptr;

	CObjectManager::OBJECT_LIST ReadyCannonObjectList;
	CObjectManager::OBJECT_LIST::iterator it;

	for (it = objectList.begin(); it != objectList.end(); it++)
	{
		CDodgeBallGimmick* DodgeBallGimmick = nullptr;

		if((*it)->GetGimmick() != nullptr)
			DodgeBallGimmick = dynamic_cast<CDodgeBallGimmick*>((*it)->GetGimmick());


		if (DodgeBallGimmick != nullptr)
		{
			if (DodgeBallGimmick->GetNowState() == CANNON_STATE::MOVE && 
				!DodgeBallGimmick->GetShotFlag())
			{
				ReadyCannonObjectList.push_back((*it));
			}
		}
	}

	if (ReadyCannonObjectList.size() < 1)
		return nullptr;

	it = ReadyCannonObjectList.begin();
	int index = rand() % ReadyCannonObjectList.size();

	std::advance(it, index);

	return *it;
}