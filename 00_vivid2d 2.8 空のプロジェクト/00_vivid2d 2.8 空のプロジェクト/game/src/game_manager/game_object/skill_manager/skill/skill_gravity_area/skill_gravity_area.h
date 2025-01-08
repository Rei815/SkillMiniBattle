#pragma once
#include "../skill.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../effect_manager/effect/effect.h"

enum class GRAVITY_AFFECTED
{
    NONE,
    AFFECTED,
};

class CSkillGravityArea : public CSkill
{
public:
    CSkillGravityArea(void);
    ~CSkillGravityArea(void);

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
    static const float  m_gravity_speed_down_rate;
    static const float  m_gravity_jump_down_rate;
    static const float  m_gravity_time;
    static const float  m_gravity_cool_time;
    static const float  m_gravity_area_radius;

    GRAVITY_AFFECTED m_PlayerAffectedGravity[(int)UNIT_ID::NONE];


    IEffect* m_Effect;
    IEffect* m_PlayerAffectedEffect[(int)UNIT_ID::NONE];

    CTimer              m_Timer;
};