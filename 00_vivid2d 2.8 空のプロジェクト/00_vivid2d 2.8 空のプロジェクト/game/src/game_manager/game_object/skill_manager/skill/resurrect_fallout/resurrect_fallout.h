#pragma once
#include "../skill.h"
#include "..\..\..\effect_manager\effect\effect.h"
class CResurrectFallout : public CSkill
{
public:
    CResurrectFallout(void);
    ~CResurrectFallout(void);

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

protected:
    static const float      m_floating_time;
    static const float      m_cool_time;
    static const CVector3   m_scale;
    static const float      m_resurrect_height;

    CTimer                  m_SkillDuration;
    CTimer                  m_CoolTime;

    IEffect*                m_Effect;
};