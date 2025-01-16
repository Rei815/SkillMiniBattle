#pragma once
#include "../skill.h"

class CSkillMimicry : public CSkill
{
public:
    CSkillMimicry(void);
    ~CSkillMimicry(void);

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
    static const float m_mimicry_speed_rate;
};