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
    std::shared_ptr<IEffect> m_DebuffEffect;
    std::list<std::shared_ptr<IEffect>> m_EffectList;
    CDataManager&       dm = CDataManager::GetInstance();
    CUnitManager&       um = CUnitManager::GetInstance();
};