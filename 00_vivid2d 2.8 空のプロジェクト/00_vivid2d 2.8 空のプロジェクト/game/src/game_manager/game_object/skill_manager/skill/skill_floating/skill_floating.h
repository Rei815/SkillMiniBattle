#pragma once
#include "../skill.h"
#include "..\..\..\effect_manager\effect\effect.h"
class CSkillFloating : public CSkill
{
public:
    CSkillFloating(void);
    ~CSkillFloating(void);

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
    void Action();

    /*!
     *  @brief      �A�N�V�����I��
     */
    void    ActionEnd(void);

protected:
    static const float      m_duration_time;
    static const float      m_cool_time;
    static const CVector3   m_scale;
    static const float      m_effect_scale;

    IEffect*            m_Effect;
    IEffect*            m_SkillEffect;
};