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
	APPEAR,     //!< 出現
	PLAY,       //!< プレイ中
	DAMAGED,    //!< 被弾
	DEFEAT,     //!< 敗北
};
class PlayerComponent : public IComponent
{
public:

	/*!
	 *  @brief      コンストラクタ
	 *  @param[in]  id             プレイヤーID
	 *  @param[in]  transform      トランスフォーム
	 */
    PlayerComponent(PLAYER_ID id, CTransform transform);

	/*!
	 *  @brief      デストラクタ
	 */
    ~PlayerComponent() override = default;

	/*!
	 *  @brief      アタッチ時の初期化
     * 
	 *  @param[in]  owner          コンポーネントをアタッチしたオーナーオブジェクト
	 */
    void            OnAttach(CGameObject* owner) override;

	/*!
	 *  @brief      更新
	 *
	 *  @param[in]  delta_time     前フレームからの経過時間
	 *  @param[in]  owner          コンポーネントをデタッチしたオーナーオブジェクト
	 */
    void            Update(float delta_time, CGameObject* owner) override;

    /*!
     *  @brief      被弾
     * 
     *  @param[in]  bullet          被弾した弾
     *  @param[in]  hit_position    被弾位置
     */
    void            HitBullet(std::shared_ptr<IBullet> bullet, CVector3 hit_position);

    /*!
     *  @brief      衝撃を与える
     * 
     *  @param[in]  hit_position   衝撃の位置
     *  @param[in]  direction      向き
     *  @param[in]  power          衝撃力
     */
    void            Impact(const CVector3& hit_position, const CVector3& direction, float power);

    /*!
     *  @brief      プレイヤーが動いているかを取得
     *
     *  @return     true : 動いている, false: 動いていない
     */
    bool            GetPlayerMoving();

	/*!
	 *  @brief      プレイヤーのIDを取得
	 *
	 *  @return     プレイヤーのID
	 */
    PLAYER_ID       GetPlayerID() const { return m_PlayerID; }

	/*!
	 *  @brief      敗北フラグを取得
	 *
	 *  @return     true : 敗北している, false: 敗北していない
	 */
    bool            IsDefeated() const { return m_DefeatFlag; }

    /*!
     *  @brief      敗北フラグ設定
     *
     *  @param[in]  flag    敗北フラグ
     */
    void            SetDefeated(bool flag) { m_DefeatFlag = flag; }

    /*!
     *  @brief      無敵フラグ取得
     *
     *  @return     無敵フラグ
     */
    bool            IsInvincible(void) const { return m_InvincibleFlag; }

    /*!
     *  @brief      無敵フラグ設定
     *
     *  @param[in]  flag    無敵フラグ
     */
    void            SetInvincible(bool flag) { m_InvincibleFlag = flag; }

    /*!
     *  @brief      スキルを取得
     *
     *  @return     スキル
     */
    std::shared_ptr<CSkill>     GetSkill() const { return m_Skill; }

    /*!
	 *  @brief      スキルを設定
     *  
	 *  @param[in]  skill   スキル
     */
    void            SetSkill(std::shared_ptr<CSkill> skill) { m_Skill = skill; }

    /*!
	 *  @brief      接地しているかを取得
     *
	 *  @return	    true    接地している, false 接地していない
     */
    bool            IsGround() const { return m_IsGround; }

    /*!
     *  @brief      接地しているかを設定
     *
     *  @param[in]  isGround 接地しているかのフラグ
     */
    void            SetIsGround(bool isGround) { m_IsGround = isGround; }

    /*!
     *  @brief      行動の可不可を設定
     *
     *  @param[in]  flag    行動フラグ
     */
    void            SetActionFlag(bool flag) { m_ActionFlag = flag; }

	/*!
	 *  @brief      プレイヤーの正面方向のベクトルを取得
	 *
	 *  @return     正面方向のベクトル
	 */
    CVector3        GetForwardVector() const { return m_ForwardVector; }

	/*!
	 *  @brief      プレイヤーの正面方向のベクトルを設定
	 *
	 *  @param[in]  forward_vector 正面方向のベクトル
	 */
    void            SetForwardVector(const CVector3& forward_vector);

    /*!
     *  @brief      プレイヤーの高さを取得
     *
     *  @return     高さ
     */
    float           GetHeight() const { return m_height; }

    /*!
     *  @brief      プレイヤーの半径を取得
     *
     *  @return     半径
     */
    float           GetRadius() const { return m_radius; }

    /*!
     *  @brief      速度を取得
     *
     *  @return     速度
     */
    CVector3        GetVelocity() const { return m_Velocity; }

    /*!
     *  @brief      速度を設定
     *
     *  @param[in]  velocity 速度
     */
    void            SetVelocity(const CVector3& velocity) { m_Velocity = velocity; }

    /*!
     *  @brief      基本の重力を取得
     *
     *  @return     重力
     */
    CVector3        GetDefaultGravity() const { return m_gravity; }

    /*!
     *  @brief      重力を設定
     *
     *  @param[in]  gravity 重力
     */
    void            SetGravity(const CVector3& gravity) { m_Gravity = gravity; }

    /*!
     *  @brief      接地しているオブジェクトを設定
     *
     *  @param[in]  gameObject オブジェクト
     */
    void            SetGroundObject(CGameObject* gameObject) { m_GroundObject = gameObject; }
    /*!
     *  @brief      『外部からの影響による移動速度』のセット
     *
     *  @param[in]  velocity    セットする速度
     */
    void            SetAffectedVelocity(CVector3 velocity) { m_AffectedVelocity = velocity; }

    /*!
     *  @brief      『外部からの影響による移動速度』の加算
     *
     *  @param[in]  velocity    加算する速度
     */
    void            AddAffectedVelocity(CVector3 velocity) { m_AffectedVelocity += velocity; }

    /*!
     *  @brief      アルファ値を減らしていく
     * 
	 *  @param[in]  alpha   減らせるアルファ値の上限
     */
    void            DecAlpha(float alpha = 0.0f);
    /*!
     *  @brief      アルファ値を増やす
     * 
	 *  @param[in]  alpha   アルファ値の上限
     */
    void            RevertAlpha(float alpha = 1.0f);

	/*!
	 *  @brief      アルファ値を設定
	 *
	 *  @@param[in]  alpha   アルファ値
	 */
    void            SetAlpha(float alpha);

    /*!
     *  @brief      スキル等によるスピード倍率の乗算
     * 
     *  @param[in]  rate    倍率
     */
    void            MulMoveSpeedRate(float rate = 1.0f);

    /*!
     *  @brief      スキル等によるスピード倍率の除算
     * 
     *  @param[in]  rate    倍率
     */
    void            DivMoveSpeedRate(float rate = 1.0f);

    /*!
     *  @brief      スキル等によるジャンプ倍率のセット
     *
     *  @param[in]  rate    倍率
     */
    void            SetJumpPowerRate(float rate = 1.0f) { m_JumpPower = rate; }

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

	/*!
	 *  @brief      コントローラーの入力に基づいてプレイヤーを制御
	 */
    void            Control();


    /*!
     *  @brief      出現
     */
    void            Appear(void);

    /*!
     *  @brief      プレイ中
     * 
	 *  @param[in]  delta_time 前フレームからの経過時間
     */
    void            Play(float delta_time);

	/*!
	 *  @brief      プレイヤーの移動
	 *
	 *  @param[in]  delta_time 前フレームからの経過時間
	 */
    void            Move(float delta_time);

    /*!
	 *  @brief      床との衝突処理
     * 
	 *  @param[in]  owner  オーナーオブジェクト
     */
	void            HandleGroundCollisions(CGameObject* owner);

	/*!
	*   @brief      壁との衝突処理
    * 
	*   @param[in]  owner  オーナーオブジェクト
    */
    void            HandleWallCollisions(CGameObject* owner);

	/*!
	 *  @brief      天井との衝突処理
	 *
	 *  @param[in]  owner  オーナーオブジェクト
	 */
    void            HandleCeilingCollisions(CGameObject* owner);

	/*!
	 *  @brief      サブステップでの移動処理
	 *
	 *  @param[in]  totalMove      このフレームでの総移動量
	 *  @param[in]  maxSubsteps    最大サブステップ数
	 */
    void            SubstepMove(const CVector3& totalMove, int maxSubsteps = 5);

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