#pragma once
#include "../../unit_manager/unit/player/player.h"
#include "../../ui_manager/ui_manager.h"
#include "../../ui_manager/ui/skill_gauge/skill_gauge.h"
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
    virtual void    Initialize(SKILL_ID skill_id);

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
     *  @brief      �v���C���[�̃Z�b�g
     */
    virtual void    SetPlayer(CPlayer* player);

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

    /*!
     *  @brief      ID�擾
     */
    SKILL_ID        GetSkillID();

protected:
    CPlayer*            m_Player;

    SKILL_CATEGORY      m_Category;
    SKILL_ID            m_SkillID;

    CSkillGauge*        m_UiSkillGauge;
};