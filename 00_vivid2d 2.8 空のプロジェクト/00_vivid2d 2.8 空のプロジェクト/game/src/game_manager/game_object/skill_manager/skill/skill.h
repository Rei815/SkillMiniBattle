#pragma once
#include "../../unit_manager/unit/player/player.h"
#include "../../ui_manager/ui_manager.h"
#include "../../ui_manager/ui/skill_cursor/skill_cursor.h"
#include "../../ui_manager/ui/skill_gauge/skill_gauge.h"
#include "../../ui_manager/ui/skill_icon/skill_icon.h"
#include "skill_id.h"

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
    CSkill(void);
    CSkill(SKILL_CATEGORY category);
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
     *  @brief      カテゴリー取得
     */
    SKILL_CATEGORY  GetSkillCategory();

    /*!
     *  @brief      ID取得
     */
    SKILL_ID        GetSkillID();

protected:
    static const vivid::Vector2     m_icon_positionList[];
    static const float              m_icon_scale;

    CPlayer*            m_Player;

    SKILL_CATEGORY      m_Category;
    SKILL_ID            m_SkillID;

    CSkillIcon*         m_UiSkillIcon;
    CSkillGauge*        m_UiSkillGauge;
    CSkillCursor*       m_UiSkillCursor;

    vivid::Vector2      m_IconPosition;

    float               m_GaugePercent;
    UNIT_ID             m_PlayerID;
    SKILL_STATE         m_State;
};