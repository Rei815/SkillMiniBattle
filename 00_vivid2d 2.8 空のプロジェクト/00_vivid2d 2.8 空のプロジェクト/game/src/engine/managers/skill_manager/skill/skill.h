#pragma once
#include "../../ui_manager/ui_manager.h"
#include "../../ui_manager/ui/skill_cursor/skill_cursor.h"
#include "../../ui_manager/ui/skill_gauge/skill_gauge.h"
#include "../../ui_manager/ui/skill_icon/skill_icon.h"
#include "skill_id.h"
#include "../../sound_manager/sound_manager.h"
#include "../../../utility/timer/timer.h"
#include "../../../../game/components/player_component/player_id.h"
#include "../../../core/game_object/game_object.h"

class CPlayer;

enum class SKILL_STATE
{
    WAIT,
    ACTIVE,
    COOLDOWN,
};

class CSkill : public std::enable_shared_from_this<CSkill>
{
public:
    CSkill(float duration_time = 0.0f, float cool_time = 0.0f);
    CSkill(SKILL_CATEGORY category, float duration_time = 0.0f, float cool_time = 0.0f);
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
    virtual void    SetPlayer(std::shared_ptr<CGameObject> player);

    /*!
     *  @brief      �A�N�V�����Ăяo��
     */
    virtual void    Action(void);
    
    /*!
     *  @brief      �A�N�V�����I��
     */
    virtual void    ActionEnd(void);

    /*!
     *  @brief      �J�e�S���[�擾
     */
    SKILL_CATEGORY  GetSkillCategory();

    /*!
     *  @brief      ID�擾
     */
    SKILL_ID        GetSkillID();

    /*!
     *  @brief      �X�L���̏�Ԃ��擾
     *  @return     state   ���
     */
    SKILL_STATE    GetState(void);

    /*!
     *  @brief      �X�L���̏�Ԃ�ݒ�
     *  @param[in]   state   ���
     */
    void    SetState(SKILL_STATE state);

protected:
    static const vivid::Vector2     m_icon_positionList[];
    static const float              m_icon_scale;

    std::weak_ptr<CGameObject>      m_Player;

    SKILL_CATEGORY      m_Category;
    SKILL_ID            m_SkillID;

    std::shared_ptr<CSkillIcon>         m_UiSkillIcon;
    std::shared_ptr<CSkillGauge>        m_UiSkillGauge;
    std::shared_ptr<CSkillCursor>       m_UiSkillCursor;

    vivid::Vector2      m_IconPosition;

    float               m_DurationTime;
    float               m_CoolTime;
    CTimer              m_Timer;

    float               m_GaugePercent;
    PLAYER_ID           m_PlayerID;
    SKILL_STATE         m_State;
    SE_ID               m_Sound;
};