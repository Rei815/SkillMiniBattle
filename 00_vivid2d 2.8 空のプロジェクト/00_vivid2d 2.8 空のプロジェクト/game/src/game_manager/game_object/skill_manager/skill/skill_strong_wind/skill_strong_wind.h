#pragma once
#include "../skill.h"

class CSkillStrongWind : public CSkill
{
public:
    CSkillStrongWind(void);
    ~CSkillStrongWind(void);

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

protected:
    static const float m_wind_strength;
};