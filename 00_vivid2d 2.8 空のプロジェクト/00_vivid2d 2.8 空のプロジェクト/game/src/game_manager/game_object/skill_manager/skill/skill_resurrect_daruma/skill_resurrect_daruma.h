#pragma once
#include "../skill.h"

class CSkillResurrectDaruma : public CSkill
{
public:
    CSkillResurrectDaruma(void);
    ~CSkillResurrectDaruma(void);

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
    static const float m_duration_time;
    static const float m_effect_scale;

    std::shared_ptr<IEffect>            m_SkillEffect;
    std::shared_ptr<IEffect>            m_ResurrectEffect;
    CVector3            m_Resurrect_Position;
    bool                m_EffectFlag;
};