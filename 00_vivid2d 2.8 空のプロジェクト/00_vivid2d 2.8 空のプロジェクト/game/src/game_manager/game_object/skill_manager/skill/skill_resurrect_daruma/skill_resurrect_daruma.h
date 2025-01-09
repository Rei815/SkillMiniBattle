#pragma once
#include "../skill.h"

class CSkillResurrectDaruma : public CSkill
{
public:
    CSkillResurrectDaruma(void);
    ~CSkillResurrectDaruma(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(SKILL_ID skill_id);

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
    static const float m_active_time;

    CVector3            m_Resurrect_Position;
    CTimer              m_Timer;
};