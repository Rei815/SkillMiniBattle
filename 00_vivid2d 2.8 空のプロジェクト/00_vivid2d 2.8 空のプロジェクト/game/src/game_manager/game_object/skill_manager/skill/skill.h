#pragma once
#include "../../unit_manager/unit/player/player.h"
#include "../../ui_manager/ui_manager.h"
#include "../../ui_manager/ui/skill_cursor/skill_cursor.h"
#include "../../ui_manager/ui/skill_gauge/skill_gauge.h"
#include "../../ui_manager/ui/skill_icon/skill_icon.h"
#include "skill_id.h"
#include "../../sound_manager/sound_manager.h"

class CPlayer;

enum class SKILL_STATE
{
    WAIT,
    ACTIVE,
    COOLDOWN,
};

class CSkill
{
public:
    CSkill(float duration_time = 0.0f, float cool_time = 0.0f);
    CSkill(SKILL_CATEGORY category, float duration_time = 0.0f, float cool_time = 0.0f);
    ~CSkill(void);

    /*!
     *  @brief      初期化
     */
    virtual void    Initialize(SKILL_ID skill_id);

    /*!
     *  @brief      更新
     */
    virtual void    Update(void);

    /*!
     *  @brief      描画
     */
    virtual void    Draw(void);

    /*!
     *  @brief      解放
     */
    virtual void    Finalize(void);

    /*!
     *  @brief      プレイヤーのセット
     */
    virtual void    SetPlayer(CPlayer* player);

    /*!
     *  @brief      アクション呼び出し
     */
    virtual void    Action(void);
    
    /*!
     *  @brief      アクション終了
     */
    virtual void    ActionEnd(void);

    /*!
     *  @brief      カテゴリー取得
     */
    SKILL_CATEGORY  GetSkillCategory();

    /*!
     *  @brief      ID取得
     */
    SKILL_ID        GetSkillID();

    /*!
     *  @brief      スキルの状態を取得
     *  @return     state   状態
     */
    SKILL_STATE    GetState(void);

    /*!
     *  @brief      スキルの状態を設定
     *  @param[in]   state   状態
     */
    void    SetState(SKILL_STATE state);

protected:
    static const vivid::Vector2     m_icon_positionList[];
    static const float              m_icon_scale;

    CPlayer*            m_Player;

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
    UNIT_ID             m_PlayerID;
    SKILL_STATE         m_State;
    SE_ID               m_Sound;
};