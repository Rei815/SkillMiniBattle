#pragma once
#include "../skill.h"
#include "../../../effect_manager/effect_manager.h"

class CSkillHideTopic: public CSkill
{
public:
    CSkillHideTopic(void);
    ~CSkillHideTopic(void);

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
    void Action(void);

    /*!
     *  @brief      �A�N�V�����I��
     */
    void    ActionEnd(void);

protected:
    static const float  m_cool_time;
    static const float  m_duration_time;
    static const float  m_effect_scale;
    std::shared_ptr<CUI>                m_ParentTopic;
    std::shared_ptr<CUI>                m_Shutter;
    std::shared_ptr<IEffect>            m_SkillEffect;
};