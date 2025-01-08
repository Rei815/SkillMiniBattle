#include "skill_manager.h"
#include "skill/skill_speed_up/skill_speed_up.h"
#include "skill/skill_jump_up/skill_jump_up.h"
#include "skill/skill_dash/skill_dash.h"
#include "skill/skill_spawn_wall/skill_spawn_wall.h"
#include "skill/skill_barrier/skill_barrier.h"
#include "skill/floating/floating.h"
#include "skill/stomp/stomp.h"
#include "skill/resurrect_fallout/resurrect_fallout.h"
#include "skill/skill_invisible/skill_invisible.h"
#include "skill/skill_gravity_area/skill_gravity_area.h"

/*
 *  �C���X�^���X�̎擾
 */
CSkillManager&
CSkillManager::
GetInstance(void)
{
    static CSkillManager instance;

    return instance;
}

/*!
 *  @brief      ������
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
 *  @brief      �X�V
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
 *  @brief      �`��
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
 *  @brief      ���
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
 *  @brief      �X�L������
 */
void
CSkillManager::
CreateSkill(SKILL_ID skill_id, UNIT_ID player_id)
{
    CSkill* skill = nullptr;

    switch (skill_id)
    {
    case SKILL_ID::SPEED_UP:
        skill = new CSkillSpeedUp();        break;
    case SKILL_ID::JUMP_UP:
        skill = new CSkillJumpUp();         break;
    case SKILL_ID::FLOATING:
        skill = new CFloating();            break;
    case SKILL_ID::STOMP:
        skill = new CStomp();               break;
    case SKILL_ID::DASH:
        skill = new CSkillDash();           break;
    case SKILL_ID::SPAWN_WALL:
        skill = new CSkillSpawnWall();      break;
    case SKILL_ID::BARRIER:
        skill = new CSkillBarrier();        break;
    case SKILL_ID::GRAVITY_AREA:
        skill = new CSkillGravityArea();    break;
    case SKILL_ID::INVISIBLE:
        skill = new CSkillInvisible();      break;
    case SKILL_ID::RESURRECT_FALLOUT:
        skill = new CResurrectFallout();    break;
    default:
        break;
    }

    if (!skill) return;

    skill->Initialize(skill_id);
    m_SetSkill[(int)player_id] = skill;
}

/*!
 *  @brief      �X�L���t�^
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
            m_SkillList.push_back(m_SetSkill[i]);
        }
    }
}

/*!
 *  @brief      �R���X�g���N�^
 */
CSkillManager::
CSkillManager(void)
{

}

/*!
 *  @brief      �R�s�[�R���X�g���N�^
 *
 *  @param[in]  rhs     �I�u�W�F�N�g
 */
CSkillManager::
CSkillManager(const CSkillManager& rhs)
{
    (void)rhs;
}

/*!
 *  @brief      �f�X�g���N�^
 */
CSkillManager::
~CSkillManager(void)
{

}

/*!
 *  @brief      ������Z�q
 *
 *  @param[in]  rhs ����I�u�W�F�N�g
 *
 *  @return     ���g�̃I�u�W�F�N�g
 */
CSkillManager&
CSkillManager::
operator=(const CSkillManager& rhs)
{
    (void)rhs;

    return *this;
}