#include "dodgeball_game.h"
#include "../../../../unit_manager/unit_manager.h"
#include "../../../../gimmick_manager/gimmick_manager.h"
#include "../../../../gimmick_manager/gimmick/dodgeball_gimmick/dodgeball_gimmick.h"
#include "../../../../camera/camera.h"
#include "../../../../object_manager/object_manager.h"
#include "../../../../ui_manager/ui_manager.h"
#include "../../../../bullet_manager/bullet_manager.h"
#include "../../../../launcher/launcher.h"

//�㉺���E��4���� �~ �e������3���� �� 12��
const CVector3		CDodgeBallGame::m_cannon_pos_list[] = 
{
	CVector3(    0,   0, 1000),CVector3(  500,   0, 1000),CVector3(- 500,   0, 1000),	//��
	CVector3(    0,   0,-1000),CVector3(- 500,   0,-1000),CVector3(  500,   0,-1000),	//��
	CVector3( 1000,   0,    0),CVector3( 1000,   0,- 500),CVector3( 1000,   0,  500),	//�E
	CVector3(-1000,   0,    0),CVector3(-1000,   0,  500),CVector3(-1000,   0,- 500)	//��
};

//�㉺���E��4����
const CVector3		CDodgeBallGame::m_cannon_rot_list[] = 
{
	CVector3(0,180,0),	//��
	CVector3(0,  0,0),	//��
	CVector3(0,-90,0),	//�E
	CVector3(0, 90,0)	//��
};

const int			CDodgeBallGame::m_max_cannnon_count = 3;
const float			CDodgeBallGame::m_cannnon_spawn_time = 3.0f;
const float			CDodgeBallGame::m_initial_shot_time = 1.5f;
const float			CDodgeBallGame::m_min_shot_time = 0.5f;
const float			CDodgeBallGame::m_shot_time_acceleration = 0.1f;
const CVector3		CDodgeBallGame::m_camera_position = CVector3(0, 1500.0f, -1500.0f);
const CVector3		CDodgeBallGame::m_camera_direction = CVector3(0, -1.0f, 1.0f);

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

void CDodgeBallGame::Initialize(void)
{
	m_SpawnTimer.SetUp(0);
	m_ShotTimer.SetUp(m_initial_shot_time);
	CGame::Initialize();
	CCamera::GetInstance().Initialize();
	CCamera::GetInstance().SetPosition(m_camera_position);
	CCamera::GetInstance().SetDirection(m_camera_direction);
	m_DebugText = "�h�b�W�{�[���Q�[��";

	CUnitManager::GetInstance().Create(UNIT_ID::PLAYER1, CVector3(-100, 0, 0));
	//CUnitManager::GetInstance().Create(UNIT_ID::PLAYER2, CVector3(100, 0, 0));

	CLauncher::GetInstance().Initialize();
	CBulletManager::GetInstance().Initialize();
}

void CDodgeBallGame::Update(void)
{
	CGame::Update();
	CCamera::GetInstance().Update();
	CLauncher::GetInstance().Update();
	CBulletManager::GetInstance().Update();
}

void CDodgeBallGame::Draw(void)
{
	CGame::Draw();
	CBulletManager::GetInstance().Draw();
}

void CDodgeBallGame::Finalize(void)
{
	CGame::Finalize();
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

			//��C�̐���
			SpawnCannnon();

			//���̖C�̌�����ύX
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
		IObject* temp = ChooseCannon();
		if(temp != nullptr)
			temp->GetGimmick()->SetSwitch(true);
	}
}

void CDodgeBallGame::Finish(void)
{
	CGame::Finish();
}

void CDodgeBallGame::SpawnCannnon(void)
{
	CTransform Temp;
	Temp.position = m_cannon_pos_list[(int)m_NextCannnonDir * 3 + m_CannonCount];
	Temp.rotation = m_cannon_rot_list[(int)m_NextCannnonDir];

	//��C�I�u�W�F�N�g�̐���
	IObject* CannonObject = CObjectManager::GetInstance().Create(OBJECT_ID::CANNON_OBJECT, Temp);

	//��C�M�~�b�N�̃Z�b�g
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
		CDodgeBallGimmick* DodgeBallGimmick = dynamic_cast<CDodgeBallGimmick*>((*it)->GetGimmick());

		if (DodgeBallGimmick != nullptr)
		{
			if (DodgeBallGimmick->GetNowState() == CANNON_STATE::MOVE)
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