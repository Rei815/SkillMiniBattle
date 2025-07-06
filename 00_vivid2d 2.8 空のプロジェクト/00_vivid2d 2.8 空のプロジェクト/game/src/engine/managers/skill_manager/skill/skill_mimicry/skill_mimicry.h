#pragma once
#include "../skill.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../../components/transform_component/transform_component.h"

class CSkillMimicry : public CSkill
{
public:
    CSkillMimicry(void);
    ~CSkillMimicry(void);

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
    static const float          m_mimicry_speed_rate;
    static const float          m_effect_scale;
    static const CVector3       m_model_pos;
    static const CVector3       m_model_rot;
    static const float          m_model_scale;

    std::shared_ptr<CGameObject>        m_GameObject;   //!< エンティティ
    std::shared_ptr<TransformComponent> m_TransformComponent;   //!< キャッシュ用コンポーネント

    std::shared_ptr<IEffect>            m_SkillEffect;
};