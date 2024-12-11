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
    CPlayer*            m_Player;

    SKILL_CATEGORY      m_Category;
    SKILL_ID            m_SkillID;

    CSkillGauge*        m_UiSkillGauge;
};