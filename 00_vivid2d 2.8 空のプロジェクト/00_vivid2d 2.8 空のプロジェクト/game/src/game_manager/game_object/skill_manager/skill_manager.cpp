#include "skill_manager.h"
#include "skill/skill_speed_up/skill_speed_up.h"
#include "skill/skill_jump_up/skill_jump_up.h"
#include "skill/skill_dash/skill_dash.h"
#include "skill/skill_spawn_wall/skill_spawn_wall.h"
#include "skill/skill_barrier/skill_barrier.h"

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
 *  @brief      �X�L�������i����܂��񂪂���񂾁j
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
 *  @brief      �X�L�������i�t�H�[���Q�[���j
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
        skill = new CSkillJumpUp();     break;
    }

    if (!skill) return;

    m_SetSkill[(int)player_id] = skill;
}

/*!
 *  @brief      �X�L�������i�h�b�W�{�[���j
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
    case SKILL_ID_DODGEBALL::BARRIER:
        skill = new CSkillBarrier();  break;
    }

    if (!skill) return;

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
            m_SetSkill[i]->Initialize(CUnitManager::GetInstance().GetPlayer((UNIT_ID)i));
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