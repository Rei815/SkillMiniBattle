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

    /*!
     *  @brief      �A�N�V�����I��
     */
    void ActionEnd(void);

protected:
    static const float  m_dash_speed_up_rate;
    static const float  m_duration_time;
    static const float  m_cool_time;
};