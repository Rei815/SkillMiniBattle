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
    void        Initialize(CPlayer* player);

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
     *  @brief      アクション呼び出し
     */
    void Action(void);

protected:
    static const float m_jump_up_rate;
};