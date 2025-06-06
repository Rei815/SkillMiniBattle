#pragma once
#pragma once
#include "../skill.h"

class CSkillStomp : public CSkill
{
public:
    CSkillStomp(void);
    ~CSkillStomp(void);

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
    void Action();

    /*!
     *  @brief      アクション終了
     */
    void    ActionEnd(void);

protected:
    static const float  m_cool_time;
    static const float  m_effect_scale;

    std::shared_ptr<IEffect>            m_SkillEffect;
    std::shared_ptr<CShot>              m_Shot;
};