#pragma once
#include "../skill.h"

class CSkillJumpUp : public CSkill
{
public:
    CSkillJumpUp(void);
    ~CSkillJumpUp(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(CPlayer* player);

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
    static const float m_jump_up_rate;
};