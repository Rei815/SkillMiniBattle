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
    void        Initialize(CPlayer* player);

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
    void        Action(void);


protected:
    enum class STATE
    {
        WAIT,
        INVISIBLE,
        IS_COOL_TIME,
    };
    static const float m_cool_time;
    static const float m_invisible_time;

    STATE              m_State;
    CTimer             m_Timer;
};