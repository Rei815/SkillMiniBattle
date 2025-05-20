
#pragma once

#include "unit_id.h"
#include "..\..\..\..\mathematics\mathematics.h"
#include "../../model_manager/model/model.h"
#include "..\..\bullet_manager\bullet\bullet.h"
#include "..\..\object_manager\object\object.h"
#include "../../launcher/shot/shot.h"


/*!
 *  @brief  ユニットの状態ID
 */
enum class UNIT_STATE
{
    APPEAR,
    ATTACK,
    DEFEAT,
};

class IUnit
{
public:
    IUnit();
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  category  ユニット識別子
     *  @param[in]  unit_id     ユニットID
     */
    IUnit(UNIT_CATEGORY category, UNIT_ID unit_id = UNIT_ID::NONE);

    /*!
     *  @brief      デストラクタ
     */
    virtual ~IUnit(void);

    /*!
     *  @brief      初期化
     *
     *  @param[in]  position    位置
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
     *  @brief      アタリ判定チェック
     *
     *  @param[in]  bullet  弾クラス
     *
     *  @retval     true    当たっている
     *  @retval     false   当たっていない
     */
    virtual bool    CheckHitBullet(IBullet* bullet);

    /*!
     *  @brief      アタリ判定チェック
     *
     *  @param[in]  bullet  弾クラス
     *
     *  @retval     true    当たっている
     *  @retval     false   当たっていない
     */
    virtual bool    CheckHitBulletModel(IBullet* bullet);

    /*!
     *  @brief      ユニットID取得
     *
     *  @return     ユニットID
     */
    UNIT_ID         GetUnitID(void);

    /*!
     *  @brief      位置取得
     *
     *  @return     位置
     */
    CVector3        GetPosition(void);

    /*!
     *  @brief      位置設定
     *
     *  @param[in]  position    位置
     */
    void            SetPosition(const CVector3& position);

    /*!
     *  @brief      アクティブフラグ取得
     *
     *  @return     アクティブフラグ
     */
    bool            GetActive(void);

    /*!
     *  @brief      アクティブフラグ設定
     *
     *  @param[in]  active  アクティブフラグ
     */
    void            SetActive(bool active);

    /*!
     *  @brief      ユニット識別子取得
     *
     *  @return     ユニット識別子
     */
    UNIT_CATEGORY   GetUnitCategory(void);

    /*!
     *  @brief      無敵フラグ取得
     *
     *  @return     無敵フラグ
     */
    bool            GetInvincibleFlag(void);

    /*!
     *  @brief      無敵フラグ設定
     *
     *  @param[in]  flag    無敵フラグ
     */
    void            SetInvincibleFlag(bool flag);

    /*!
     *  @brief      状態取得
     *
     *  @return     状態ID
     */
    UNIT_STATE      GetUnitState(void);

    /*!
     *  @brief      無敵フラグ設定
     *
     *  @param[in]  flag    無敵フラグ
     */
    void            SetUnitState(UNIT_STATE state);

    /*!
     *  @brief      速度ベクトルの取得
     *
     */
    CVector3        GetVelocity();

    /*!
     *  @brief      速度ベクトルの設定
     *
     */
    void            SetVelocity(const CVector3& velocity);

    /*!
     *  @brief      『外部からの影響による移動速度』のセット
     *
     *  @param[in]  velocity    セットする速度
     */
    void SetAffectedVelocity(CVector3 velocity);

    /*!
     *  @brief      『外部からの影響による移動速度』の加算
     *
     *  @param[in]  velocity    加算する速度
     */
    void AddAffectedVelocity(CVector3 velocity);

    /*!
     *  @brief      半径取得
     *
     *  @return     半径
     */
    float           GetRadius(void);

    /*!
     *  @brief      高さ取得
     *
     *  @return     高さ
     */
    float           GetHeight(void);

    /*!
     *  @brief      弾数追加
     *
     */
    void        AddShot(void);

    /*!
     *  @brief      発射数追加
     *
     */
    void        AddBullet(void);

    /*!
     *  @brief      弾数追加
     *
     */
    void        DamageUp(float damageRate);

    /*!
     *  @brief      攻撃率取得
     *
     *  @return     攻撃率
     */
    float       GetDamageRate(void);

    /*!
     *  @brief      敗北フラグ取得
     *
     *  @return     敗北フラグ
     */
    bool       GetDefeatFlag(void);

    /*!
     *  @brief      敗北フラグ設定
     *
     *  @param[in]  flag    敗北フラグ
     */
    void       SetDefeatFlag(bool flag);

    CModel      GetModel(void);

    /*!
         *  @brief      地上にいるかどうかを設定
         *
         *  @param[in]  flag    接地フラグ
     */
    void        SetIsGround(bool flag);

    /*!
         *  @brief      地上にいるかどうかを取得
         *
         *  @return     接地フラグ
     */
    bool        GetIsGround();

    /*!
     *  @brief      重力を設定
     *
     *  @param[in]  gravity    重力値
     */
    void        SetGravity(const CVector3& gravity);

    /*!
     *  @brief      基礎重力を取得
     *
     *  @return     重力値
     */
    CVector3        GetDefaultGravity();


    /*!
     *  @brief      アルファ値を減らしていく
     */
    void    DecAlpha(float alpha = 0.0f);
    /*!
     *  @brief      アルファ値を元に戻す
     */
    void        RevertAlpha(float alpha);

    void        SetAlpha(float alpha);

    /*!
     *  @brief      親のオブジェクトを取得
     *
     *  @return     親のオブジェクト
     */
    IObject*    GetParent(void);

    /*!
     *  @brief      親のオブジェクトを設定
     *
     *  @param[in]  parent    親のオブジェクト
     */
    void        SetParent(IObject* parent);

    void            SetForwardVector(const CVector3& forward_vector);

    CVector3        GetForwardVector();

protected:

    /*!
     *  @brief      出現
     */
    virtual void    Appear(void);

    /*!
     *  @brief      攻撃
     */
    virtual void    Attack(void);

    /*!
     *  @brief      射撃
     *  @param[in]  aim         Playerを狙うかどうか
     *  @param[in]  position    発射位置
     */
    void        Fire(CShot* shot, bool aim, CVector3& position);

    /*!
     *  @brief      射撃
     *  @param[in]  aim         Playerを狙うかどうか
     *  @param[in]  position    発射位置
     */
    void        Fire(CShot* shot, bool aim, CVector3& position, const CVector3& direction);

    /*!
     *  @brief      被弾
     *  @param[in]  bullet          被弾した弾
     *  @param[in]  hit_position    被弾位置
     */
    virtual void    HitBullet(IBullet* bullet, CVector3 hit_position);

    /*!
     *  @brief      衝撃を与える
     *  @param[in]  hit_position   衝撃の位置
     *  @param[in]  direction      向き
     *  @param[in]  float          衝撃力
     */
    virtual void    Impact(const CVector3& hit_position, const CVector3& direction, float power);

    /*!
     *  @brief      敗北
     */
    virtual void    Defeat(void);

    /*!
     *  @brief      削除
     */
    virtual void    Delete(void);

    static const float      m_destroy_scale_adjust;     //!< エフェクト(destroy)の大きさ調整値
    static const float      m_alpha_speed;              //!< アルファ値の速度
    static const CVector3   m_gravity;

    float                   m_Radius;
    float                   m_Height;
    CModel                  m_Model;
    CTransform	            m_Transform;		    //!< トランスフォーム
    CVector3                m_ForwardVector;        //!< 正面方向のベクトル
    CVector3	            m_Max_Vertex;		    //!< 最大頂点座標
    CVector3                m_Velocity;             //!< 速度
    CVector3                m_AffectedVelocity;     //!< 外部からの影響による速度
    CVector3                m_Gravity;              //!< 重力
    UNIT_CATEGORY           m_Category;             //!< ユニット識別子
    UNIT_ID                 m_UnitID;               //!< ユニットID
    bool                    m_ActiveFlag;           //!< アクティブフラグ
    bool                    m_InvincibleFlag;       //!< 無敵フラグ
    UNIT_STATE              m_UnitState;            //!< 状態ID
    bool                    m_AimFlag;              //!< 狙うかどうか
    float                   m_DamageRate;
    CShot*                  m_Shot;
    bool                    m_RevertAlpha;              //!< アルファ値を戻す
    float                   m_Alpha;                    //!< アルファ値
    bool                    m_DefeatFlag;               //!< 敗北フラグ
    std::string             m_FileName;
    bool                    m_IsGround;                 //!< 地上にいるか
    IObject*                m_Parent;                   //!< 親のオブジェクト
};
