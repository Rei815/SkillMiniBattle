#pragma once
#include "../skill.h"
#include "..\..\..\effect_manager\effect\effect.h"
class CSkillResurrectBelt : public CSkill
{
public:
    CSkillResurrectBelt(void);
    ~CSkillResurrectBelt(void);

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
    void        Action();

    /*!
     *  @brief      アクション終了
     */
    void    ActionEnd(void);

protected:
    static const CVector3   m_resurrect_position;
    static const float      m_effect_scale;

    std::shared_ptr<IEffect>                m_SkillEffect;
    std::shared_ptr<IEffect>                m_ResurrectEffect;
};