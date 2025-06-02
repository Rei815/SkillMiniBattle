#pragma once
#include "../skill.h"
#include "../../../effect_manager/effect_manager.h"

class CSkillHideTopic: public CSkill
{
public:
    CSkillHideTopic(void);
    ~CSkillHideTopic(void);

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

    /*!
     *  @brief      アクション終了
     */
    void    ActionEnd(void);

protected:
    static const float  m_cool_time;
    static const float  m_duration_time;
    static const float  m_effect_scale;
    CUI*                m_ParentTopic;
    CUI*                m_Shutter;
    IEffect*            m_SkillEffect;
};