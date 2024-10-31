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
    virtual void        Initialize(UNIT_ID unit_id, const CVector3& position, const std::string& file_name, int controller);

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
     *  @brief      行動の可不可を設定
     *
     *  @param[in]  flag    行動フラグ
 */
    void        SetActionFlag(bool flag);

    void        AddWins();

    int         GetWins();
protected:
    /*!
     *  @brief      攻撃
     */
    void        Attack(void);

    /*!
     *  @brief      被弾
     *  @param[in]  bullet          被弾した弾
     *  @param[in]  hit_position    被弾位置
     */
    void    HitBullet(IBullet* bullet, CVector3 hit_position);


    /*!
     *  @brief      死亡
     */
    void        Defeat(void);


    /*!
     *  @brief      操作
     */
    void        Control(void);

    /*!
     *  @brief      移動処理
     */
    void        Move(void);

    /*!
     *  @brief      ダメージを喰らった時の処理(ダメージの計算はUnit)
     */
    void        Damage(void);

    static const float              m_radius;                       //!< 半径
    static const float              m_height;                       //!< 高さ
    static const float              m_move_speed;                   //!< 移動速度
    static const float              m_jump_power;                   //!< ジャンプ力
    static const float              m_move_friction;                //!< 移動用減速率
    static const float              m_fly_away_speed;               //!< 被弾時の吹っ飛び速度
    static const float              m_max_life;                     //!< 最大ライフ
    static const int                m_max_invincible_time;          //!< 無敵時間
    static const int                m_invincible_visible_interval;  //!< 無敵時間中の点滅間隔
    static const float              m_fall_accelerator;             //!< 落下加速度

    float                           m_FallSpeed;                    //!< 落下速度
    CVector3                        m_Accelerator;                  //!< 加速度
    CVector3                        m_InitialPosition;              //!< 初期位置
    bool                            m_StopFlag;                     //!< 停止フラグ
    bool                            m_FrictionFlag;                 //!< 減速フラグ
    int                             m_InvincibleTime;               //!< 無敵時間
    bool                            m_ActionFlag;                   //!< 行動処理有効フラグ
    DxLib::COLOR_F                  m_Color;
    int                             m_Controller;                   //!< コントローラー識別
    int                             m_WinsNum;                      //!< 勝った回数
};