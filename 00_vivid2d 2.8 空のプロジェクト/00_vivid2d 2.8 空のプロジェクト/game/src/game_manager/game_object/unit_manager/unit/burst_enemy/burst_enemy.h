#pragma once

#include "..\..\..\..\..\mathematics\mathematics.h"
#include "..\unit.h"
#include "../../../model_manager/model/model.h"
#include "../../../bullet_manager/bullet/bullet.h"

class CBurstEnemy : public IUnit
{
public:

    CBurstEnemy();

    ~CBurstEnemy();

    /*!
     *  @brief      初期化
     *
     *  @param[in]  position    位置
     *  @param[in]  moveID      動きのID
     *  @param[in]  aimFlag     狙うかどうか
     */
    virtual void    Initialize(const CVector3& position, MOVE_ID moveID, bool aimFlag);

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
private:

    enum BURST_STATE
    {
        WAIT,
        FIRE,
    };
    /*!
     *  @brief      攻撃
     */
    void        Attack(void);

    /*!
     *  @brief      移動
     */
    void        Move(void);

    /*!
     *  @brief      死亡
     */
    void        Dead(void);

    static const CVector3           m_StartValue;           //!< 初期位置
    static const float              m_max_life;             //!< 最大ライフ
    static const float              m_move_speed;           //!< 移動速度
    static const float              m_radius;               //!< 半径

    CVector3                        m_Accelerator;          //!< 加速度
};