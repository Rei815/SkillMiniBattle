#pragma once
#include "../../unit_manager/unit/player/player.h"
#include "skill_id.h"

class CPlayer;

class CSkill
{
public:
    CSkill(void);
    CSkill(SKILL_CATEGORY category);
    ~CSkill(void);

    /*!
     *  @brief      ������
     */
    virtual void    Initialize(CPlayer* player);

    /*!
     *  @brief      �X�V
     */
    virtual void    Update(void);

    /*!
     *  @brief      �`��
     */
    virtual void    Draw(void);

    /*!
     *  @brief      ���
     */
    virtual void    Finalize(void);

    /*!
     *  @brief      �A�N�V�����Ăяo��
     */
    virtual void    Action(void);

    /*!
     *  @brief      �A�N�V�����Ăяo��
     */
    virtual void    Action(UNIT_CATEGORY category);

    /*!
     *  @brief      �J�e�S���[�擾
     */
    SKILL_CATEGORY  GetSkillCategory();
protected:
    CPlayer*            m_Player;

    SKILL_CATEGORY      m_Category;
};