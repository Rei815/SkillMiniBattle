#pragma once
#include "../skill.h"
#include "..\..\..\effect_manager\effect\effect.h"
class CFloating : public CSkill
{
public:
    CFloating(void);
    ~CFloating(void);

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
    void Action(UNIT_CATEGORY category);

protected:
    static const float      m_floating_time;
    static const float      m_cool_time;
    static const CVector3   m_scale;

    CTimer              m_SkillDuration;
    CTimer              m_CoolTime;

    IEffect*            m_Effect;
};