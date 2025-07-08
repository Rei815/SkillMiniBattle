#pragma once
#include "../skill.h"
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
    static const float  m_effect_scale;
    static const int    m_se_volume;

    GRAVITY_AFFECTED m_PlayerAffectedGravity[(int)PLAYER_ID::NONE];

    std::shared_ptr<IEffect> m_Effect;
    std::shared_ptr<IEffect> m_SkillEffect;
    std::shared_ptr<IEffect> m_PlayerAffectedEffect[(int)PLAYER_ID::NONE];
};