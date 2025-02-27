#pragma once
#include "../skill.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../data_manager/data_manager.h"

class CSkillSlow : public CSkill
{
public:
    CSkillSlow(void);
    ~CSkillSlow(void);

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
    static const float m_cool_time;
    static const float m_duration_time;
    static const float m_effect_scale;

    
    IEffect* m_SkillEffect;
    IEffect* m_DebuffEffect;
    std::list<IEffect*> m_EffectList;
    CDataManager&       dm = CDataManager::GetInstance();
    CUnitManager&       um = CUnitManager::GetInstance();
};