#pragma once
#include "../../../engine/core/component/component.h"
#include "../../../engine/mathematics/vector/vector3/vector3.h"
#include "../../../engine/utility/timer/timer.h"
#include "player_id.h"
#include <memory>
#include "../../../engine/utility/transform/transform.h"
#include "../../../engine/managers/bullet_manager/bullet/bullet.h"

// 前方宣言
class CController;
class CSkill;
class TransformComponent;

// プレイヤーの状態
enum class PLAYER_STATE
{
    APPEAR,
    PLAY, // 以前のATTACKに相当
    DAMAGED,
    DEFEAT,
};
class PlayerComponent : public IComponent
{
public:
    PlayerComponent(PLAYER_ID id, CTransform transform);
    ~PlayerComponent() override = default;

    void OnAttach(CGameObject* owner) override;
    void Update(float delta_time, CGameObject* owner) override;

    /*!
     *  @brief      被弾
     *  @param[in]  bullet          被弾した弾
     *  @param[in]  hit_position    被弾位置
     */
    void            HitBullet(std::shared_ptr<IBullet> bullet, CVector3 hit_position);

    /*!
     *  @brief      衝撃を与える
     *  @param[in]  hit_position   衝撃の位置
     *  @param[in]  direction      向き
     *  @param[in]  float          衝撃力
     */
    void            Impact(const CVector3& hit_position, const CVector3& direction, float power);

    PLAYER_ID GetPlayerID() const;
    bool IsDefeated() const;

    /*!
     *  @brief      敗北フラグ設定
     *
     *  @param[in]  flag    敗北フラグ
     */
    void SetDefeated(bool flag);

    /*!
     *  @brief      無敵フラグ取得
     *
     *  @return     無敵フラグ
     */
    bool            IsInvincible(void);

    /*!
     *  @brief      無敵フラグ設定
     *
     *  @param[in]  flag    無敵フラグ
     */
    void            SetInvincible(bool flag);


    void SetSkill(std::shared_ptr<CSkill> skill);

    // 接地しているかどうかを外部に教えるためのメソッド
    bool IsGround() const;
    /*!
     *  @brief      行動の可不可を設定
     *
     *  @param[in]  flag    行動フラグ
     */
    void            SetActionFlag(bool flag);

    bool            GetPlayerMoving();

    void            SetForwardVector(const CVector3& forward_vector);

    CVector3        GetForwardVector();

    /*!
     *  @brief      スキルを取得
     *
     *  @return     スキル
     */
    std::shared_ptr<CSkill>           GetSkill();

    /*!
     *  @brief      プレイヤーの高さを取得
     *
     *  @return     高さ
     */
    float           GetHeight();

    /*!
     *  @brief      プレイヤーの半径を取得
     *
     *  @return     半径
     */
    float           GetRadius();

    /*!
     *  @brief      速度を取得
     *
     *  @return     速度
     */
    CVector3        GetVelocity();

    /*!
     *  @brief      基本の重力を取得
     *
     *  @return     重力
     */
    CVector3        GetDefaultGravity();

    /*!
     *  @brief      速度を設定
     *
     *  @param[in]  velocity 速度
     */
    void        SetVelocity(const CVector3& velocity);

    /*!
     *  @brief      重力を設定
     *
     *  @param[in]  gravity 重力
     */
    void        SetGravity(const CVector3& gravity);

    /*!
     *  @brief      接地しているかを設定
     *
     *  @param[in]  true    接地している　false 接地していない
     */
    void        SetIsGround(bool isGround);

    /*!
     *  @brief      接地しているオブジェクトを設定
     *
     *  @param[in]  gameObject オブジェクト
     */
    void        SetGroundObject(CGameObject* gameObject);
    /*!
     *  @brief      『外部からの影響による移動速度』のセット
     *
     *  @param[in]  velocity    セットする速度
     */
    void            SetAffectedVelocity(CVector3 velocity);

    /*!
     *  @brief      『外部からの影響による移動速度』の加算
     *
     *  @param[in]  velocity    加算する速度
     */
    void            AddAffectedVelocity(CVector3 velocity);

    /*!
     *  @brief      アルファ値を減らしていく
     */
    void            DecAlpha(float alpha = 0.0f);
    /*!
     *  @brief      アルファ値を元に戻す
     */
    void            RevertAlpha(float alpha = 1.0f);

    void            SetAlpha(float alpha);
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

private:
    // IUnitとCPlayerから持ってきたメソッド
    void Control();
    void Move(float delta_time);
    void Impact(const CVector3& direction, float power);
    /*!
     *  @brief      出現
     */
    void    Appear(void);
    /*!
     *  @brief      出現
     */
    void    Play(float delta_time);
    /*!
     *  @brief      出現
     */
    void    Defeat(void);

    // 壁との当たり判定を行うヘルパー関数を追加
    void HandleWallCollisions(float delta_time, CGameObject* owner);
    static const float              m_radius;                                   //!< 半径
    static const float              m_height;                                   //!< 高さ
    static const float              m_model_scale;                              //!< モデルの大きさ
    static const float              m_move_speed;                               //!< 移動速度
    static const float              m_jump_power;                               //!< ジャンプ力
    static const float              m_fly_away_speed;                           //!< 被弾時の吹っ飛び速度
    static const float              m_max_life;                                 //!< 最大ライフ
    static const float              m_max_invincible_time;                      //!< 無敵時間
    static const float              m_fall_accelerator;                         //!< 落下加速度
    static const float              m_destroy_scale_adjust;                     //!< エフェクト(destroy)の大きさ調整値
    static const float              m_alpha_speed;                              //!< アルファ値の速度
    static const CVector3           m_move_friction;                            //!< 移動用減速率
    static const CVector3           m_gravity;                                  //!< 重力値
    static const int                m_invincible_visible_interval;              //!< 無敵時間中の点滅間隔

    static const COLOR_F       m_player_body_color[(int)PLAYER_ID::NONE];  //!< 体の色
    static const COLOR_F       m_player_eye_color[(int)PLAYER_ID::NONE];   //!< 目の色

    std::shared_ptr<CSkill>         m_Skill;            //!< スキル
    std::shared_ptr<CController>    m_Controller;       //!< コントローラー
    CGameObject*                    m_GroundObject;     //!< 接地した床のオブジェクト
    PLAYER_ID                       m_PlayerID;         //!< プレイヤーID
    PLAYER_STATE                    m_PlayerState;      //!< 状態ID
    CTimer                          m_InvincibleTimer;  //!< 無敵時間タイマー
    CVector3                        m_Accelerator;      //!< 加速度影響による移動速度
    CVector3                        m_InitialPosition;  //!< 初期位置
    CVector3                        m_ForwardVector;    //!< 正面方向のベクトル
    CVector3                        m_Velocity;         //!< 速度
    CVector3                        m_AffectedVelocity; //!< 外部からの影響による速度
    CVector3                        m_Gravity;          //!< 重力
    float                           m_MoveSpeedRate;    //!< 移動速度の倍率
    float                           m_JumpPowerRate;    //!< ジャンプ力の倍率
    float                           m_MoveSpeed;
    float                           m_JumpPower;
    float                           m_Alpha;            //!< アルファ値
    bool                            m_StopFlag;         //!< 停止フラグ
    bool                            m_FrictionFlag;     //!< 減速フラグ
    bool                            m_ActionFlag;       //!< 行動処理有効フラグ
    bool                            m_ActiveFlag;       //!< アクティブフラグ
    bool                            m_InvincibleFlag;   //!< 無敵フラグ
    bool                            m_DefeatFlag;       //!< 敗北フラグ
    bool                            m_IsGround;         //!< 地上にいるか


};