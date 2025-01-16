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
     *  @brief      �v���C���[�̃Z�b�g
     */
    void    SetPlayer(CPlayer* player);

    /*!
     *  @brief      �A�N�V�����Ăяo��
     */
    void Action(void);

    /*!
     *  @brief      �A�N�V�����I��
     */
    void    ActionEnd(void);

protected:
    static const float m_jump_up_rate;
};