#pragma once
#include "../skill.h"
#include "../../../effect_manager/effect/effect.h"
#include "../../../model/model.h"
#include "../../../effect_manager/effect_manager.h"

class CSkillBarrier : public CSkill
{
public:
    CSkillBarrier(void);
    ~CSkillBarrier(void);

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
     *  @brief      プレイヤーのセット
     */
    void    SetPlayer(std::shared_ptr<CPlayer> player);

    /*!
     *  @brief      アクション呼び出し
     */
    void Action(void);

    /*!
     *  @brief      アクション終了
     */
    void ActionEnd(void);

protected:
    static const float m_duration_time;
    static const float m_cool_time;
    static const std::string m_collider_model_file_name;
    static const float m_effect_scale;

    CModel			    m_ColliderModel;
    std::shared_ptr<IEffect>            m_Effect;
    std::shared_ptr<IEffect>            m_SkillEffect;
};