#pragma once
#include "../../unit_manager/unit/player/player.h"

class CPlayer;

class CSkill
{
public:
    CSkill(void);
    ~CSkill(void);

    /*!
     *  @brief      初期化
     */
    virtual void    Initialize(CPlayer* player);

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
     *  @brief      アクション呼び出し
     */
    virtual void    Action(void);

protected:
    CPlayer* m_Player;
};