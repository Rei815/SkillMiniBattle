#pragma once

#include "..\..\..\..\..\mathematics\mathematics.h"
#include "..\unit.h"
#include "../../../model_manager/model/model.h"
#include "../../../bullet_manager/bullet/bullet.h"
#include "../../../skill_manager/skill/skill.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../controller_manager/controller/controller.h"

class CSkill;

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
    virtual void    Initialize(UNIT_ID unit_id, const CVector3& position, const std::string& file_name);

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
     *  @brief          行動の可不可を設定
     *
     *  @param[in]      flag    行動フラグ
 */
    void                SetActionFlag(bool flag);

    CController*        GetController(void);
    
    /*!
     *  @brief      スキルの取得
     *
     *  @return     スキル
     */
    CSkill*         GetSkill();

    /*!
     *  @brief      スキルのセット
     *
     *  @param[in]  skill    スキルのポインタ
     */
    void            SetSkill(CSkill* skill);

    /*!
     *  @brief      スキル等によるスピード倍率のセット
     *
     *  @param[in]  rate    倍率
     */
    void            SetMoveSpeedRate(float rate = 1.0f);

    /*!
     *  @brief      スキル等によるスピード倍率の乗算
     *  @param[in]  rate    倍率
     */
    void            MulMoveSpeedRate(float rate = 1.0f);

    /*!
     *  @brief      スキル等によるスピード倍率の除算
     *  @param[in]  rate    倍率
     */
    void            DivMoveSpeedRate(float rate = 1.0f);

    /*!
     *  @brief      スキル等によるジャンプ倍率のセット
     *
     *  @param[in]  rate    倍率
     */
    void            SetJumpPowerRate(float rate = 1.0f);

    /*!
     *  @brief      スキル等によるジャンプ倍率の乗算
     *
     *  @param[in]  rate    倍率
     */
    void            MulJumpPowerRate(float rate = 1.0f);

    /*!
     *  @brief      スキル等によるジャンプ倍率の除算
     *
     *  @param[in]  rate    倍率
     */
    void            DivJumpPowerRate(float rate = 1.0f);

    /*!
     *  @brief      無敵効果の付与
     *
     *  @param[in]  invincible_time    無敵時間
     */
    void            StartInvincible(float invincible_time);

    bool            GetPlayerMoving();

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
     *  @brief      衝撃を与える
     *  @param[in]  hit_position   衝撃の位置
     *  @param[in]  direction      向き
     *  @param[in]  float          衝撃力
     */
    void    Impact(const CVector3& hit_position, const CVector3& direction, float power);
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
    static const float              m_model_scale;
    static const float              m_move_speed;                   //!< 移動速度
    static const float              m_jump_power;                   //!< ジャンプ力
    static const CVector3           m_move_friction;                //!< 移動用減速率
    static const float              m_fly_away_speed;               //!< 被弾時の吹っ飛び速度
    static const float              m_max_life;                     //!< 最大ライフ
    static const float              m_max_invincible_time;          //!< 無敵時間
    static const int                m_invincible_visible_interval;  //!< 無敵時間中の点滅間隔
    static const float              m_fall_accelerator;             //!< 落下加速度

    static const unsigned int       m_player_body_color[(int)UNIT_ID::NONE];
    static const unsigned int       m_player_eye_color[(int)UNIT_ID::NONE];

    float                           m_MoveSpeedRate;                //!< 移動速度の倍率
    float                           m_JumpPowerRate;                //!< ジャンプ力の倍率

    CSkill*                         m_Skill;                        //!< スキル

    //float                           m_FallSpeed;                    //!< 落下速度
    CVector3                        m_Accelerator;                  //!< 加速度影響による移動速度
    CVector3                        m_InitialPosition;              //!< 初期位置
    bool                            m_StopFlag;                     //!< 停止フラグ
    bool                            m_FrictionFlag;                 //!< 減速フラグ
    CTimer                          m_InvincibleTimer;              //!< 無敵時間タイマー
    bool                            m_ActionFlag;                   //!< 行動処理有効フラグ
    CController*                    m_Controller;                   //!< コントローラー
    IEffect*                        m_Effect;
};