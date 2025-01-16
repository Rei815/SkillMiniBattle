#pragma once
#include "../skill.h"
#include "..\..\..\effect_manager\effect\effect.h"
class CSkillResurrectFallout : public CSkill
{
public:
    CSkillResurrectFallout(void);
    ~CSkillResurrectFallout(void);

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
    static const float      m_resurrect_height;
    static const CVector3   m_initial_position;

    IEffect*                m_Effect;
};