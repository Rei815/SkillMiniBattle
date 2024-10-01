#include "unit_manager.h"
#include "..\scene_manager\scene_manager.h"
#include "..\bullet_manager\bullet_manager.h"
#include "..\effect_manager\effect_manager.h"
#include "..\sound_manager\sound_manager.h"
#include "..\..\..\utility\utility.h"
#include "unit\player\player_1\player_1.h"
#include "unit\player\player_2\player_2.h"
#include "unit\three_way_enemy\three_way_enemy.h"
#include "unit\five_way_enemy\five_way_enemy.h"
#include "unit\normal_enemy\normal_enemy.h"
#include "unit\burst_enemy\burst_enemy.h"
#include "unit\shotgun_enemy\shotgun_enemy.h"
#include "unit\homing_enemy\homing_enemy.h"
#include "unit\boss_enemy\boss_enemy.h"
#include "../ui_manager/ui_manager.h"


/*
 *  インスタンスの取得
 */
CUnitManager&
CUnitManager::
GetInstance(void)
{
    static CUnitManager instance;

    return instance;
}

/*
 *  初期化
 */
void
CUnitManager::
Initialize(void)
{
    m_MoveIdList["Left"] = MOVE_ID::LEFT;
    m_MoveIdList["Right"] = MOVE_ID::RIGHT;
    m_MoveIdList["Wait"] = MOVE_ID::WAIT;

    m_WaveStateList["Wave"] = CMiniGame::WAVE_STATE::WAVE;
    m_WaveStateList["WaveFinish"] = CMiniGame::WAVE_STATE::WAVE_FINISH;

    m_EnemyTable.clear();
    m_UnitList.clear();
    m_CreateTimer = 0;

    m_AppearBossFlag = false;

    m_AppearFinalEnemyFlag = false;
    m_GenerateFlag = false;
    m_WaveCount = 0;
    m_WaveCurrentCount = 1;
    DeployEnemy();
}

/*
 *  更新
 */
void
CUnitManager::
Update(void)
{

    // ユニット更新
    UpdateUnit();

    CheckHitStage();

    UpdateEnemyTable();
}

/*
 *  描画
 */
void
CUnitManager::
Draw(void)
{
    if (m_UnitList.empty()) return;

    UNIT_LIST::iterator it = m_UnitList.begin();

    while (it != m_UnitList.end())
    {
        (*it)->Draw();

        ++it;
    }
}

/*
 *  解放
 */
void
CUnitManager::
Finalize(void)
{
    if (m_UnitList.empty()) return;

    UNIT_LIST::iterator it = m_UnitList.begin();

    while (it != m_UnitList.end())
    {
        (*it)->Finalize();

        delete (*it);

        ++it;
    }

    m_UnitList.clear();
}

/*
 *  ユニット生成
 */
void
CUnitManager::
Create(UNIT_ID id, const CVector3& pos, MOVE_ID moveId, bool aimFlag)
{
    IUnit* unit = nullptr;

    switch (id)
    {
    case UNIT_ID::PLAYER1:              unit = new CPlayer1();      break;
    case UNIT_ID::PLAYER2:              unit = new CPlayer2();      break;
    case UNIT_ID::PLAYER3:              unit = new CPlayer1();      break;
    case UNIT_ID::PLAYER4:              unit = new CPlayer1();      break;
    case UNIT_ID::NORMAL_ENEMY:         unit = new CNormalEnemy();      break;
    case UNIT_ID::THREE_WAY_ENEMY:      unit = new CThreeWayEnemy();      break;
    case UNIT_ID::FIVE_WAY_ENEMY:       unit = new CFiveWayEnemy();      break;
    case UNIT_ID::BURST_ENEMY:          unit = new CBurstEnemy();      break;
    case UNIT_ID::SHOTGUN_ENEMY:        unit = new CShotGunEnemy();      break;
    case UNIT_ID::HOMING_ENEMY:         unit = new CHomingEnemy();      break;
    case UNIT_ID::BOSS_ENEMY:           unit = new CBossEnemy();      break;
    }

    if (!unit) return;

    unit->Initialize(pos, moveId, aimFlag);
    m_UnitList.push_back(unit);
}

/*
 *  ユニットと弾のアタリ判定
 */
void
CUnitManager::
CheckHitBullet(IBullet* bullet)
{
    if (m_UnitList.empty()) return;

    UNIT_LIST::iterator it = m_UnitList.begin();

    while (it != m_UnitList.end())
    {

        if ((*it)->CheckHitBullet(bullet))
            return;

        ++it;
    }
}

/*
 *  ボスが撃破されたか？
 */
bool
CUnitManager::
CheckDestoryBoss(void)
{
    if (!m_UnitList.empty())
    {
        UNIT_LIST::iterator it = m_UnitList.begin();

        if (m_UnitList.size() <= 1 && (*it)->GetUnitCategory() == UNIT_CATEGORY::PLAYER && m_AppearBossFlag)
            return true;
    }

    return false;
}

bool CUnitManager::CheckDestoryFinalEnemy(void)
{
    if (!m_UnitList.empty())
    {
        UNIT_LIST::iterator it = m_UnitList.begin();

        if (m_UnitList.size() <= 1 && (*it)->GetUnitCategory() == UNIT_CATEGORY::PLAYER && m_AppearFinalEnemyFlag)
            return true;
    }

    return false;
}

void CUnitManager::CheckHitStage()
{
    if (m_UnitList.empty()) return;
    UNIT_LIST::iterator it = m_UnitList.begin();

    while (it != m_UnitList.end())
    {

        if (CStage::GetInstance().GetModel().GetModelHandle() == VIVID_DX_ERROR)
            return;

        CVector3 startPos = (*it)->GetPosition();
        CVector3 dir = (*it)->GetVelocity().Normalize();

        //動いている場合常に1か-1を保つ
        dir.x = (dir.x > 0) - (dir.x < 0);

        CVector3 endPos = startPos + dir * (*it)->GetRadius();

        DxLib::MV1_COLL_RESULT_POLY_DIM hit_poly_dim = MV1CollCheck_LineDim(CStage::GetInstance().GetModel().GetModelHandle(), -1, startPos, endPos);

        // 線分の描画
        DrawLine3D(startPos, endPos, GetColor(255, 255, 0));

        if (hit_poly_dim.HitNum >= 1)
        {

            (*it)->SetVelocity(CVector3::ZERO);

            CVector3 hitPos = CVector3(hit_poly_dim.Dim->HitPosition.x, hit_poly_dim.Dim->HitPosition.y, hit_poly_dim.Dim->HitPosition.z);

            CVector3 diffPos = endPos - hitPos;

            if (diffPos != CVector3::ZERO)
                (*it)->SetPosition((*it)->GetPosition() - diffPos);
        }

        // 当たり判定情報の後始末
        MV1CollResultPolyDimTerminate(hit_poly_dim);

        ++it;
    }

}

CPlayer* CUnitManager::GetPlayer(void)
{
    if (m_UnitList.empty()) return nullptr;

    UNIT_LIST::iterator it = m_UnitList.begin();

    while (it != m_UnitList.end())
    {
        if ((*it)->GetUnitID() == UNIT_ID::PLAYER1)
            return (CPlayer*)(*it);

        ++it;
    }

    return nullptr;
}

IUnit* CUnitManager::GetBoss(void)
{
    if (m_UnitList.empty()) return nullptr;

    UNIT_LIST::iterator it = m_UnitList.begin();

    while (it != m_UnitList.end())
    {
        if ((*it)->GetUnitID() == UNIT_ID::BOSS_ENEMY)
            return (*it);

        ++it;
    }

    return nullptr;
}

int CUnitManager::GetMaxWave(void)
{
    return m_WaveCount;
}


int CUnitManager::GetCurrentWave(void)
{
    return m_WaveCurrentCount;
}

CVector3 CUnitManager::CheckHitLine(const CVector3& startPos, const CVector3& endPos)
{
    CVector3 hitPos = CStage::GetInstance().GetModel().GetHitLinePosition(startPos, endPos);
    if (m_UnitList.empty()) return hitPos;
    UNIT_LIST::iterator it = m_UnitList.begin();

    while (it != m_UnitList.end())
    {
        if ((*it)->GetModel().CheckHitLine(startPos, endPos) == true)
            hitPos = (*it)->GetModel().GetHitLinePosition(startPos, endPos);

        ++it;
    }
    return hitPos;
}

bool CUnitManager::CheckHitLineEnemy(const CVector3& startPos, const CVector3& endPos)
{
    if (m_UnitList.empty()) return false;
    UNIT_LIST::iterator it = m_UnitList.begin();

    while (it != m_UnitList.end())
    {
        if ((*it)->GetModel().CheckHitLine(startPos, endPos) == true && (*it)->GetUnitCategory() != UNIT_CATEGORY::PLAYER)
            return true;

        ++it;
    }

    return false;
}

bool CUnitManager::CheckFinishWave(void)
{
    if (CheckDestoryFinalEnemy())
        return true;
    else
        false;
}

/*
 *  ENEMYの配置
 */
void
CUnitManager::
DeployEnemy(void)
{
    // CSVローダーの宣言
    CCSVLoader csv_loader;

    // CSVファイルロード
    csv_loader.Load("data\\enemy_table.csv");

    for (int i = 0; i < csv_loader.GetRows(); ++i)
    {
        ENEMY_TABLE_DATA t;

        string unit_id = csv_loader.GetString(i, ENEMY_TABLE_DATA_PARAM_ID);
        t.aim_flag = unit_id[0] == 'T';
        t.id = (UNIT_ID)stoi(&unit_id[1]);
        t.x = csv_loader.GetInteger(i, ENEMY_TABLE_DATA_PARAM_X);
        t.y = csv_loader.GetInteger(i, ENEMY_TABLE_DATA_PARAM_Y);
        t.z = csv_loader.GetInteger(i, ENEMY_TABLE_DATA_PARAM_Z);
        t.create_frame = csv_loader.GetInteger(i, ENEMY_TABLE_DATA_PARAM_CREATE_TIME);
        t.move_id = m_MoveIdList[csv_loader.GetString(i, ENEMY_TABLE_DATA_PARAM_MOVE_ID)];
        t.wave_state = m_WaveStateList[csv_loader.GetString(i, ENEMY_TABLE_DATA_PARAM_WAVE_STATE)];
        if (t.wave_state == CMiniGame::WAVE_STATE::WAVE_FINISH)
            m_WaveCount++;

        m_EnemyTable.push_back(t);
    }

    // 解放
    csv_loader.Unload();
}


/*
 *  Enemyテーブル更新
 */
void
CUnitManager::
UpdateEnemyTable(void)
{
    if (m_EnemyTable.empty() || !m_GenerateFlag || m_AppearFinalEnemyFlag) return;

    ENEMY_TABLE::iterator it = m_EnemyTable.begin();

    ENEMY_TABLE_DATA t = *it;


    if (++m_CreateTimer > t.create_frame)
    {
        CVector3 pos((float)(t.x), (float)(t.y), (float)(t.z));

        Create(t.id, pos, t.move_id, t.aim_flag);

        // ボスが生成された時には警告エフェクトを出す
        if (t.id == UNIT_ID::BOSS_ENEMY)
        {
            CEffectManager::GetInstance().Create(EFFECT_ID::EMERGENCY, vivid::Vector2(0.0f, 0.0f), 0xffffffff, 0.0f);
            CUIManager::GetInstance().Create(UI_ID::BOSS_LIFE);

            CSoundManager::GetInstance().Play(SOUND_ID::WARNING);
            CSoundManager::GetInstance().Play(SOUND_ID::WARNING_SHORT);

            m_AppearBossFlag = true;
        }

        if (t.wave_state == CMiniGame::WAVE_STATE::WAVE_FINISH)
        {
            m_AppearFinalEnemyFlag = true;

        }

        m_EnemyTable.erase(it);
    }
}

void CUnitManager::SetGenerateFlag(bool flag)
{
    m_GenerateFlag = flag;
}

void CUnitManager::SetAppearFinalEnemyFlag(bool flag)
{
    m_AppearFinalEnemyFlag = flag;
}

bool CUnitManager::GetAppearBossFlag()
{
    return m_AppearBossFlag;
}

void CUnitManager::AddWaveCurrentCount()
{
    m_WaveCurrentCount++;
}

/*
 *  ユニット更新
 */
void
CUnitManager::
UpdateUnit(void)
{
    if (m_UnitList.empty()) return;

    UNIT_LIST::iterator it = m_UnitList.begin();

    while (it != m_UnitList.end())
    {
        IUnit* unit = (IUnit*)(*it);

        unit->Update();

        if (!unit->GetActive())
        {
            unit->Finalize();

            delete unit;

            it = m_UnitList.erase(it);

            continue;
        }

        ++it;
    }
}



/*
 *  コンストラクタ
 */
CUnitManager::
CUnitManager(void)
    : m_CreateTimer(0)
    , m_WaveCount(0)
{
}

/*
 *  コピーコンストラクタ
 */
CUnitManager::
CUnitManager(const CUnitManager& rhs)
{
    (void)rhs;
}

/*
 *  デストラクタ
 */
CUnitManager::
~CUnitManager(void)
{
}

/*
 *  代入演算子
 */
CUnitManager&
CUnitManager::
operator=(const CUnitManager& rhs)
{
    (void)rhs;

    return *this;
}