#pragma once

#include "..\..\..\..\..\mathematics\mathematics.h"
#include "..\unit.h"
#include "../../../model_manager/model/model.h"
#include "../../../bullet_manager/bullet/bullet.h"
#include "../../../launcher/launcher.h"

class CBossEnemy : public IUnit
{
public:

    CBossEnemy();

    ~CBossEnemy();

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

    void        _Attack(void);

    /*!
     *  @brief      移動
     */
    void        Move(void);

    /*!
     *  @brief      死亡
     */
    void        Dead(void);

    /*!
     *  @brief      攻撃パターンA
     */
    void    Appear(void);

    /*!
     *  @brief      待機
     */
    void    Wait(void);

    /*!
     *  @brief      攻撃パターンA
     */
    void    MoveAttack(void);

    /*!
     *  @brief      攻撃パターンB
     */
    void    StayAttack(void);

    /*!
     *  @brief      攻撃パターンC
     */
    void    FallAttack(void);


    /*!
     *  @brief      攻撃パターンID
     */
    enum class ATTACK_PATTERN
    {
        WAIT,
        MOVE_ATTACK,
        STAY_ATTACK,
        FALL_ATTACK,
    };

    static const float              m_max_life;                 //!< 最大ライフ
    static const float              m_move_speed;               //!< 移動速度
    static const float              m_radius;                   //!< 半径
    static const float              m_attack_time;              //!< 移動時間
    static const float              m_fall_accelerator;         //!< 落下速度
    static const int                m_wait_time;                //!< 待機時間
    //static const float              m_jump_power;             //!< ジャンプ力
    //static const float              m_fall_accelerator;       //!< 落下加速度

    static const CVector3           m_scale;                    //!< 大きさ
    CVector3                        m_Accelerator;              //!< 加速度
    ATTACK_PATTERN                  m_AttackPattern;            //!< 攻撃パターン
    CVector3                        m_StartPosition;            //!< 初期位置
    CVector3                        m_WaitPosition;             //!< 待機位置
    float                           m_AttackTimer;              //!< 移動タイマー
    int                             m_WaitTimer;                //!< 待機タイマー
    float                           m_FallSpeed;                //!< 落下速度
    CVector3                        m_ShockWavePos;
    CShot*                          m_ShotShockWave1;
    CShot*                          m_ShotShockWave2;
    CShot*                          m_ShotShockWave3;
    CShot*                          m_ShotHomingDelayShotgun;
    CShot*                          m_ShotHomingShotgun;
    CShot*                          m_ShotShotgun;
    bool                            m_BossLife;

};