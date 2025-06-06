#include "skill_manager.h"
#include "skill/skill_speed_up/skill_speed_up.h"
#include "skill/skill_jump_up/skill_jump_up.h"
#include "skill/skill_dash/skill_dash.h"
#include "skill/skill_spawn_wall/skill_spawn_wall.h"
#include "skill/skill_barrier/skill_barrier.h"
#include "skill/skill_invisible/skill_invisible.h"
#include "skill/skill_stun/skill_stun.h"
#include "skill/skill_mimicry/skill_mimicry.h"
#include "skill/skill_slow/skill_slow.h"
#include "skill/skill_ogre_control/skill_ogre_control.h"
#include "skill/skill_resurrect_daruma/skill_resurrect_daruma.h"
#include "skill/skill_floating/skill_floating.h"
#include "skill/skill_stomp/skill_stomp.h"
#include "skill/skill_resurrect_fallout/skill_resurrect_fallout.h"
#include "skill/skill_strong_wind/skill_strong_wind.h"
#include "skill/skill_gravity_area/skill_gravity_area.h"
#include "skill/skill_hide_topic/skill_hide_topic.h"
#include "skill/skill_resurrect_belt/skill_resurrect_belt.h"


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

        ++it;
    }

    m_SkillList.clear();

    for (int i = 0; i < (int)UNIT_ID::NONE; i++)
    {
        m_SetSkill[i] = nullptr;
    }
}

/*!
 *  @brief      スキル生成
 */
void
CSkillManager::
CreateSkill(SKILL_ID skill_id, UNIT_ID player_id)
{
    std::shared_ptr<CSkill> skill = nullptr;

    switch (skill_id)
    {
    case SKILL_ID::SPEED_UP:
        skill = std::make_shared<CSkillSpeedUp>();          break;
    case SKILL_ID::JUMP_UP:
        skill = std::make_shared<CSkillJumpUp>();           break;
    case SKILL_ID::FLOATING:
        skill = std::make_shared<CSkillFloating>();         break;
    case SKILL_ID::STOMP:
        skill = std::make_shared<CSkillStomp>();            break;
    case SKILL_ID::DASH:
        skill = std::make_shared<CSkillDash>();             break;
    case SKILL_ID::SPAWN_WALL:
        skill = std::make_shared<CSkillSpawnWall>();        break;
    case SKILL_ID::BARRIER:
        skill = std::make_shared<CSkillBarrier>();          break;
    case SKILL_ID::GRAVITY_AREA:
        skill = std::make_shared<CSkillGravityArea>();      break;
    case SKILL_ID::INVISIBLE:
        skill = std::make_shared<CSkillInvisible>();        break;
    case SKILL_ID::STUN:
        skill = std::make_shared<CSkillStun>();             break;
    case SKILL_ID::MIMICRY:
        skill = std::make_shared<CSkillMimicry>();          break;
    case SKILL_ID::SLOW:
        skill = std::make_shared<CSkillSlow>();             break;
    case SKILL_ID::OGRE_CONTOROL:
        skill = std::make_shared<CSkillOgreControl>();      break;
    case SKILL_ID::RESURRECT_DARUMA:
        skill = std::make_shared<CSkillResurrectDaruma>();  break;
    case SKILL_ID::RESURRECT_FALLOUT:
        skill = std::make_shared<CSkillResurrectFallout>(); break;
    case SKILL_ID::RESURRECT_BELT:
        skill = std::make_shared<CSkillResurrectBelt>();    break;
    case SKILL_ID::STRONG_WIND:
        skill = std::make_shared<CSkillStrongWind>();       break;
    case SKILL_ID::HIDE_TOPIC:
        skill = std::make_shared<CSkillHideTopic>();        break;

    default:
        break;
    }

    if (!skill) return;

    skill->Initialize(skill_id);
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
            m_SetSkill[i]->SetPlayer(CUnitManager::GetInstance().GetPlayer((UNIT_ID)i));
            m_SkillList.emplace_back(m_SetSkill[i]);
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