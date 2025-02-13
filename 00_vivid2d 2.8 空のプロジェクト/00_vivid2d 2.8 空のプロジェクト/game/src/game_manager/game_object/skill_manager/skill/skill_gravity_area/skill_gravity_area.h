#pragma once
#include "../skill.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../effect_manager/effect/effect.h"

enum class GRAVITY_AFFECTED
{
    NONE,
    AFFECTED,
};

class CSkillGravityArea : public CSkill
{
public:
    CSkillGravityArea(void);
    ~CSkillGravityArea(void);

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

    /*!
     *  @brief      �A�N�V�����I��
     */
    void    ActionEnd(void);

protected:
    static const float  m_gravity_speed_down_rate;
    static const float  m_gravity_jump_down_rate;
    static const float  m_duration_time;
    static const float  m_cool_time;
    static const float  m_gravity_area_radius;

    GRAVITY_AFFECTED m_PlayerAffectedGravity[(int)UNIT_ID::NONE];

    IEffect* m_Effect;
    IEffect* m_SkillEffect;
    IEffect* m_PlayerAffectedEffect[(int)UNIT_ID::NONE];
};