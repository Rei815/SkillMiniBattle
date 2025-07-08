#pragma once
#include "../skill.h"
#include "../../../data_manager/data_manager.h"
#include "../../../object_manager/object_manager.h"
#include "../../../effect_manager/effect/effect.h"

class CSkillStun : public CSkill
{
public:
    CSkillStun(void);
    ~CSkillStun(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(SKILL_ID skill_id);

    /*!
     *  @brief      �X�V
     */
    void        Update(void);

    /*!
     *  @brief      �`��
     */
    void        Draw(void);

    /*!
     *  @brief      ���
     */
    void        Finalize(void);

    /*!
     *  @brief      �A�N�V�����Ăяo��
     */
    void        Action(void);

    /*!
     *  @brief      �A�N�V�����I��
     */
    void    ActionEnd(void);

protected:
    static const float m_cool_time;
    static const float m_duration_time;
    static const float m_effect_scale;

    std::shared_ptr<IEffect> m_SkillEffect;
    std::shared_ptr<IEffect> m_Effect;
    std::shared_ptr<CGameObject> m_Target;
    CObjectManager& om = CObjectManager::GetInstance();
    CDataManager& dm = CDataManager::GetInstance();
};