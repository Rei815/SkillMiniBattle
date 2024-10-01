#pragma once

#include "..\..\..\..\..\mathematics\mathematics.h"
#include "..\unit.h"
#include "../../../model_manager/model/model.h"
#include "../../../bullet_manager/bullet/bullet.h"

class CPlayer: public IUnit
{
public:

	CPlayer();

	~CPlayer();

    /*!
     *  @brief      初期化
     *
     *  @param[in]  position    初期位置
     */
    virtual void        Initialize(const CVector3& position, MOVE_ID moveId, bool aimFlag);

    /*!
     *  @brief      更新
     */
    virtual void        Update(void);

    /*!
     *  @brief      描画
     */
    virtual void        Draw(void);

    /*!
     *  @brief      解放
     */
    virtual void        Finalize(void);

    /*!
     *  @brief      ライフ取得
     *
     *  @return     現在のライフ
     */
    float        GetLife(void);


/*!
     *  @brief      行動可能かどうかを設定
     *
     *  @param[in]  flag    行動可能かどうか
 */
    void        SetActionFlag(bool flag);

/*!
     *  @brief     発射可能かどうかを設定
     *
     *  @param[in]  flag    発射可能かどうか
 */
    void        SetFireFlag(bool flag);

protected:
    /*!
     *  @brief      攻撃
     */
    void        Attack(void);

    /*!
     *  @brief      死亡
     */
    void        Dead(void);


    /*!
     *  @brief      操作
     */
    void        Control(void);

    /*!
     *  @brief      射撃
     */
    void        Fire(void);

    /*!
     *  @brief      移動処理
     */
    void        Move(void);

    /*!
     *  @brief      ダメージを喰らった時の処理(ダメージの計算はUnit)
     */
    void        Damage(void);

    static const float              m_radius;                       //!< 半径
    static const float              m_move_speed;                   //!< 移動速度
    static const float              m_jump_power;                   //!< ジャンプ力
    static const float              m_move_friction;                //!< 移動用減速率
    static const float              m_max_life;                     //!< 最大ライフ
    static const int                m_max_invincible_time;          //!< 無敵時間
    static const int                m_invincible_visible_interval;  //!< 無敵時間中の点滅間隔
    static const float              m_fall_accelerator;             //!< 落下加速度
    static const int                m_dust_cloud_interval;          //!< 土煙の生成間隔
    static const CVector3           m_dust_cloud_position;          //!< 土煙の生成位置
    static const float              m_dust_cloud_scale_adjust;      //!< エフェクト(土煙)の大きさ調整値

    CVector3                        m_Offset;                       //!< カメラとの距離
    float                           m_FallSpeed;                    //!< 落下速度
    CVector3                        m_Accelerator;                  //!< 加速度
    bool                            m_IsGround;                     //!< 地上にいるか
    bool                            m_StopFlag;                     //!< 停止フラグ
    int                             m_InvincibleTime;               //!< 無敵時間
    int                             m_DustCloudTime;                //!< 土煙時間
    bool                            m_ActionFlag;                   //!< 行動処理有効フラグ
    bool                            m_FireFlag;                     //!< 発射処理有効フラグ
    DxLib::COLOR_F                  m_Color;

};