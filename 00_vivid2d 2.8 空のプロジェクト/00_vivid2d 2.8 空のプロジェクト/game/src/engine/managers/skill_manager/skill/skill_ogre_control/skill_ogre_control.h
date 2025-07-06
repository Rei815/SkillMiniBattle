#pragma once
#include "../skill.h"
#include "../../../data_manager/data_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../../../game/components/gimmick_component/daruma_fall_down_gimmick_component/daruma_fall_down_gimmick_component.h"

class CSkillOgreControl : public CSkill
{
public:
    CSkillOgreControl(void);
    ~CSkillOgreControl(void);

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
    static const float          m_cool_time;
    static const float          m_duration_time;
    static const CVector3       m_EffectPosition;
    static const float          m_effect_scale;

    std::shared_ptr<CPlayer>    m_Target;

    CDataManager&       dm = CDataManager::GetInstance();
    CObjectManager&     om = CObjectManager::GetInstance();

    std::shared_ptr<DarumaFallDownGimmickComponent> m_Gimmick;
    std::shared_ptr<IEffect> m_Effect;
    std::shared_ptr<IEffect> m_SkillEffect;
};