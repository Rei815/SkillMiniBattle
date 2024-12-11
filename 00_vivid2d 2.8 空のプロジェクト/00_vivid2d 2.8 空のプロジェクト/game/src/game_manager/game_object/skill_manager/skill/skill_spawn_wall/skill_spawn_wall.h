#pragma once
#include "../skill.h"
#include "../../../object_manager/object/object.h"

class CSkillSpawnWall : public CSkill
{
public:
    CSkillSpawnWall(void);
    ~CSkillSpawnWall(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(SKILL_ID skill_id);

    /*!
     *  @brief      �X�V
     */
    void        Update(void);

    /*!
     *  @brief      �`��
     */
    void        Draw(void);

    /*!
     *  @brief      ���
     */
    void        Finalize(void);


    /*!
     *  @brief      �A�N�V�����Ăяo��
     */
    void Action(void);

protected:
    enum class STATE
    {
        WAIT,
        SPAWN,
        IS_COOL_TIME,
    };

    static const float  m_spawn_cool_time;
    static const float  m_wall_exist_time;
    static const float  m_wall_spawn_distance;

    STATE m_NowState;

    CTimer              m_Timer;

    IObject*            m_WallObj;
};