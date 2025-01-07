#pragma once
#pragma once
#include "../skill.h"

class CStomp : public CSkill
{
public:
    CStomp(void);
    ~CStomp(void);

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
    void Action(UNIT_CATEGORY category);

protected:
    static const float  m_floating_time;

    CTimer              m_Timer;
    CShot*              m_Shot;
};