#pragma once
#include "../skill.h"
#include "../../../effect_manager/effect/effect.h"


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

    /*!
     *  @brief      アクション終了
     */
    void    ActionEnd(void);

protected:
    static const float          m_wind_strength;    //風の強さ
    static const float          m_cool_time;
    static const float          m_duration_time;
    static const float          m_effect_scale;
    static const int            m_se_volume;

    std::shared_ptr<IEffect>    m_SkillEffect;
    std::shared_ptr<IEffect>    m_Effect;
};