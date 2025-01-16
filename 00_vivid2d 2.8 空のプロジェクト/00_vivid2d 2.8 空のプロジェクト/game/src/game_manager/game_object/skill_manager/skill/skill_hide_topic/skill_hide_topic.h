#pragma once
#include "../skill.h"

class CSkillHideTopic: public CSkill
{
public:
    CSkillHideTopic(void);
    ~CSkillHideTopic(void);

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
    static const float  m_cool_time;
    static const float  m_duration_time;
    CTimer              m_Timer;
    CUI*                m_Parent;
    CUI*                m_Shutter;
};