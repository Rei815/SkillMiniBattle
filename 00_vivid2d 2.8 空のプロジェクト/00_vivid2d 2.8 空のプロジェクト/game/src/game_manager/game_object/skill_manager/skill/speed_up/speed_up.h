#pragma once
#include "../skill.h"

class CSpeedUp : public CSkill
{
public:
	CSpeedUp(void);
	~CSpeedUp(void);

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
    static const float speed_up_rate;
};