#pragma once
#include "../skill.h"

class CSkillDash : public CSkill
{
public:
    CSkillDash(void);
    ~CSkillDash(void);

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
    enum class DASH_STATE
    {
        WAIT,
        IS_DASH,
        IS_COOL_TIME,
    };

    static const float  m_dash_speed_up_rate;
    static const float  m_dash_time;
    static const float  m_dash_cool_time;

    DASH_STATE m_NowDashState;

    CTimer              m_Timer;
};