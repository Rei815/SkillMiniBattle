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

    /*!
     *  @brief      アクション終了
     */
    void    ActionEnd(void);


protected:
    static const float m_duration_time;
    static const float m_effect_scale;

    IEffect*            m_SkillEffect;
    IEffect*            m_ResurrectEffect;
    CVector3            m_Resurrect_Position;
    bool                m_EffectFlag;
};