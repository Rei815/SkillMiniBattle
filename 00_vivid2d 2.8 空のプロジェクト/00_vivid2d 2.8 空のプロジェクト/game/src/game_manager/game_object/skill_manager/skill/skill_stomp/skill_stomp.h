#pragma once
#pragma once
#include "../skill.h"

class CSkillStomp : public CSkill
{
public:
    CSkillStomp(void);
    ~CSkillStomp(void);

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
    static const float  m_cool_time;
    static const float  m_effect_scale;

    std::shared_ptr<IEffect>            m_SkillEffect;
    std::shared_ptr<CShot>              m_Shot;
};