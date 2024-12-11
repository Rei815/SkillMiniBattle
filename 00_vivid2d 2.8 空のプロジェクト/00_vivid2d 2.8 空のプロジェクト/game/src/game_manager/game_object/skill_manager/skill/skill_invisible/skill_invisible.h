#pragma once
#include "../skill.h"

class CSkillInvisible : public CSkill
{
public:
    CSkillInvisible(void);
    ~CSkillInvisible(void);

    /*!
     *  @brief      èâä˙âª
     */
    void        Initialize(SKILL_ID skill_id);

    /*!
     *  @brief      çXêV
     */
    void        Update(void);

    /*!
     *  @brief      ï`âÊ
     */
    void        Draw(void);

    /*!
     *  @brief      âï˙
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