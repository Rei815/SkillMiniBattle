#pragma once
#include "../skill.h"

class CSkillJumpUp : public CSkill
{
public:
    CSkillJumpUp(void);
    ~CSkillJumpUp(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(SKILL_ID skill_id);

    /*!
     *  @brief      更新
     */
    void        Update(void);

    /*!
     *  @brief      描画
     */
    void        Draw(void);

    /*!
     *  @brief      解放
     */
    void        Finalize(void);

    /*!
     *  @brief      プレイヤーのセット
     */
    void    SetPlayer(CPlayer* player);

    /*!
     *  @brief      アクション呼び出し
     */
    void Action(void);

    /*!
     *  @brief      アクション終了
     */
    void    ActionEnd(void);

protected:
    static const float m_jump_up_rate;
};