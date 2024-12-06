#pragma once
#include "../skill.h"

class CSkillInvisible : public CSkill
{
public:
    CSkillInvisible(void);
    ~CSkillInvisible(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(CPlayer* player);

    /*!
     *  @brief      更新
     */
    void        Update(void);

    /*!
     *  @brief      描画
     */
    void        Draw(void);

    /*!
     *  @brief      解放
     */
    void        Finalize(void);

    /*!
     *  @brief      アクション呼び出し
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