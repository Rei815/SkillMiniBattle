#pragma once
#pragma once
#include "../skill.h"

class CSkillStomp : public CSkill
{
public:
    CSkillStomp(void);
    ~CSkillStomp(void);

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
    void Action();

protected:
    static const float  m_cool_time;

    CTimer              m_Timer;
    CShot*              m_Shot;
};