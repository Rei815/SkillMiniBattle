#pragma once
#include "../skill.h"

class CSkillInvisible : public CSkill
{
public:
    CSkillInvisible(void);
    ~CSkillInvisible(void);

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


protected:
    enum class STATE
    {
        WAIT,
        INVISIBLE,
        IS_COOL_TIME,
    };
    static const float m_cooltime;
    static const float m_invisibletime;

    STATE              m_State;
    CTimer             m_Timer;
};