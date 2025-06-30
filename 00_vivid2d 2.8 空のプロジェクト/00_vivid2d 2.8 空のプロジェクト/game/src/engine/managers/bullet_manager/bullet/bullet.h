#pragma once

#include "../../../../mathematics\mathematics.h"
#include "../../model/model.h"
#include "../../launcher/launcher.h"
#include "collider_id.h"
#include "bullet_id.h"
#include "..\..\game_object.h"
// 前方宣言
class TransformComponent; // キャッシュするポインタの型なので前方宣言が必要
class IBullet
{
public:


    /*!
     *  @brief      コンストラクタ
     */
    IBullet(COLLIDER_ID collider_id);

    /*!
     *  @brief      デストラクタ
     */
    virtual ~IBullet(void);

    /*!
     *  @brief      初期化
     *
     *  @param[in]  category        ユニット識別子
     *  @param[in]  position        位置
     *  @param[in]  direction       向き
     */
    virtual void    Initialize(UNIT_CATEGORY category, CShot::BulletParameters* bulletParams, const CVector3& position, const CVector3& direction);

    /*!
     *  @brief      初期化
     *
     *  @param[in]  category        ユニット識別子
     *  @param[in]  id              弾のID
     *  @param[in]  position        位置
     *  @param[in]  direction       向き
     */
    virtual void    Initialize(UNIT_CATEGORY category, const CVector3& position, const CVector3& direction);

    /*!
     *  @brief      更新
     */
    virtual void    Update(void);

    /*!
     *  @brief      描画
     */
    virtual void    Draw(void);

    /*!
     *  @brief      位置取得
     *
     *  @return     位置
     */
    CVector3        GetPosition(void);

    /*!
     *  @brief      速度ベクトル取得
     *
     *  @return     速度ベクトル
     */
    CVector3        GetVelocity(void);
    
    /*!
     *  @brief      速度ベクトルの設定
     *
     *  @param[in]  velocity    速度ベクトル
     */
    void            SetVelocity(const CVector3& velocity);

    /*!
     *  @brief      アクティブフラグ取得
     *
     *  @return     アクティブフラグ
     */
    bool            IsActive(void);

    /*!
     *  @brief      アクティブフラグ設定
     *
     *  @param[in]  active  アクティブフラグ
     */
    void            Delete();

    /*!
     *  @brief      ユニット識別子取得
     *
     *  @return     ユニット識別子
     */
    UNIT_CATEGORY   GetBulletCategory(void);

    /*!
     *  @brief      弾の色取得
     *
     *  @return     弾の色
     */
    unsigned int    GetBulletColor(void);

    /*!
     *  @brief      弾の判定ID取得
     *
     *  @return     弾の判定ID
     */
    COLLIDER_ID     GetColliderID(void);

    //CModel          GetModel(void);

    float           GetPower();

    BULLET_ID       GetID();

    /*!
     * @brief       半径取得
     * 
     * @return      半径
     */
    float           GetRadius();

    /*!
     *  @brief      モデルハンドル取得
     *
     *  @return     モデルハンドル
     */
    int             GetModelHandle(void) const;

protected:

    std::shared_ptr<CGameObject>        m_GameObject;           //!< エンティティ
    std::shared_ptr<TransformComponent> m_TransformComponent;   //!< キャッシュ用コンポーネント
    static const unsigned int           m_player_color;         //!< プレイヤーの弾の色
    static const unsigned int           m_enemy_color;          //!< 敵の弾の色
    static const float                  m_life_time;            //!< 持続時間
    static const float                  m_radius;               //!< 弾の半径(初期値)
    static const float	                m_max_speed;            //!< 最高速度
    CVector3                            m_Velocity;             //!< 速度
    unsigned int                        m_Color;                //!< 色
    UNIT_CATEGORY                       m_Category;             //!< 弾識別子
    CTimer                              m_LifeTimer;            //!< 生存時間タイマー
    float                               m_Power;                //!< パワー
    float				                m_Speed;                //!< 速さ
    float				                m_Accleration;          //!< 加速力
    CVector3			                m_Direction;            //!< 発射された向き
    BULLET_ID                           m_BulletID;             //!< 弾の種類
    COLLIDER_ID                         m_ColliderID;           //!< 判定ID
};