#pragma once
#include "../skill.h"

class CSkillStrongWind : public CSkill
{
public:
    CSkillStrongWind(void);
    ~CSkillStrongWind(void);

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
    void Action(void);

protected:
    static const float  m_wind_strength;
    static const float  m_cool_time;
    static const float  m_duration_time;
    CTimer              m_Timer;
};