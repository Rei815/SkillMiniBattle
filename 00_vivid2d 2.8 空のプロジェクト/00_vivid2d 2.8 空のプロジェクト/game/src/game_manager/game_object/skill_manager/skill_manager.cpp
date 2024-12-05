#include "skill_manager.h"
#include "skill/skill_speed_up/skill_speed_up.h"
#include "skill/skill_jump_up/skill_jump_up.h"
#include "skill/skill_dash/skill_dash.h"
#include "skill/skill_spawn_wall/skill_spawn_wall.h"
#include "skill/speed_up/speed_up.h"
#include "skill/jump_up/jump_up.h"
#include "skill/floating/floating.h"
#include "skill/stomp/stomp.h"
#include "skill/resurrect_fallout/resurrect_fallout.h"

/*
 *  インスタンスの取得
 */
CSkillManager&
CSkillManager::
GetInstance(void)
{
    static CSkillManager instance;

    return instance;
}

/*!
 *  @brief      初期化
 */
void
CSkillManager::
Initialize(void)
{
    m_SkillList.clear();

    for (int i = 0; i < (int)UNIT_ID::NONE; i++)
    {
        m_SetSkill[i] = nullptr;
    }
}

/*!
 *  @brief      更新
 */
void
CSkillManager::
Update(void)
{
    if (m_SkillList.empty()) return;

    SKILL_LIST::iterator it = m_SkillList.begin();

    while (it != m_SkillList.end())
    {
        (*it)->Update();

        ++it;
    }
}

/*!
 *  @brief      描画
 */
void
CSkillManager::
Draw(void)
{
    if (m_SkillList.empty()) return;

    SKILL_LIST::iterator it = m_SkillList.begin();

    while (it != m_SkillList.end())
    {
        (*it)->Draw();

        ++it;
    }
}

/*!
 *  @brief      解放
 */
void
CSkillManager::
Finalize(void)
{
    if (m_SkillList.empty()) return;

    SKILL_LIST::iterator it = m_SkillList.begin();

    while (it != m_SkillList.end())
    {
        (*it)->Finalize();

        delete(*it);

        ++it;
    }

    m_SkillList.clear();

    for (int i = 0; i < (int)UNIT_ID::NONE; i++)
    {
        m_SetSkill[i] = nullptr;
    }
}

/*!
 *  @brief      スキル生成（だるまさんがころんだ）
 */
void
CSkillManager::
CreateSkill(SKILL_ID_DARUMA skill_id, UNIT_ID player_id)
{
    CSkill* skill = nullptr;

    switch (skill_id)
    {
    case SKILL_ID_DARUMA::SPEED_UP:
        skill = new CSkillSpeedUp();     break;
    }

    if (!skill) return;

    m_SetSkill[(int)player_id] = skill;
}

/*!
 *  @brief      スキル生成（フォールゲーム）
 */
void
CSkillManager::
CreateSkill(SKILL_ID_FALLGAME skill_id, UNIT_ID player_id)
{
    CSkill* skill = nullptr;

    switch (skill_id)
    {
    case SKILL_ID_FALLGAME::SPEED_UP:
        skill = new CSkillSpeedUp();     break;
    case SKILL_ID_FALLGAME::JUMP_UP:
        skill = new CJumpUp();     break;
    case SKILL_ID_FALLGAME::FLOATING:
        skill = new CFloating();     break;
    case SKILL_ID_FALLGAME::STOMP:
        skill = new CStomp();     break;
    case SKILL_ID_FALLGAME::RESURRECT:
        skill = new CResurrectFallout();     break;
        skill = new CSkillJumpUp();     break;
    }

    if (!skill) return;

    m_SetSkill[(int)player_id] = skill;
}

/*!
 *  @brief      スキル生成（ドッジボール）
 */
void
CSkillManager::
CreateSkill(SKILL_ID_DODGEBALL skill_id, UNIT_ID player_id)
{
    CSkill* skill = nullptr;

    switch (skill_id)
    {
    case SKILL_ID_DODGEBALL::SPEED_UP:
        skill = new CSkillSpeedUp();    break;
    case SKILL_ID_DODGEBALL::JUMP_UP:
        skill = new CSkillJumpUp();     break;
    case SKILL_ID_DODGEBALL::DASH:
        skill = new CSkillDash();       break;
    case SKILL_ID_DODGEBALL::SPAWN_WALL:
        skill = new CSkillSpawnWall();  break;
    }

    if (!skill) return;

    m_SetSkill[(int)player_id] = skill;
}

/*!
 *  @brief      スキル付与
 */
void
CSkillManager::
SetSkill(void)
{
    for (int i = 0; i < (int)UNIT_ID::NONE; i++)
    {
        if (m_SetSkill[i] != nullptr)
        {
            m_SetSkill[i]->Initialize(CUnitManager::GetInstance().GetPlayer((UNIT_ID)i));
            m_SkillList.push_back(m_SetSkill[i]);
        }
    }
}

/*!
 *  @brief      コンストラクタ
 */
CSkillManager::
CSkillManager(void)
{

}

/*!
 *  @brief      コピーコンストラクタ
 *
 *  @param[in]  rhs     オブジェクト
 */
CSkillManager::
CSkillManager(const CSkillManager& rhs)
{
    (void)rhs;
}

/*!
 *  @brief      デストラクタ
 */
CSkillManager::
~CSkillManager(void)
{

}

/*!
 *  @brief      代入演算子
 *
 *  @param[in]  rhs 代入オブジェクト
 *
 *  @return     自身のオブジェクト
 */
CSkillManager&
CSkillManager::
operator=(const CSkillManager& rhs)
{
    (void)rhs;

    return *this;
}