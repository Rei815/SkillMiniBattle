#pragma once
#include "../skill.h"
#include "..\..\..\effect_manager\effect\effect.h"
class CSkillResurrectBelt : public CSkill
{
public:
    CSkillResurrectBelt(void);
    ~CSkillResurrectBelt(void);

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
    void        Action();

    /*!
     *  @brief      �A�N�V�����I��
     */
    void    ActionEnd(void);

protected:
    static const CVector3   m_resurrect_position;
    static const float      m_effect_scale;

    IEffect*                m_SkillEffect;
    IEffect*                m_ResurrectEffect;
};