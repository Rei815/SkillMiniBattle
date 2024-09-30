#pragma once

#include "../../../../mathematics\mathematics.h"
#include "../../model_manager/model/model.h"
#include "../../../../collider/sphere_collider/sphere_collider.h"
#include "../../launcher/launcher.h"
#include "collider_id.h"
class IBullet
{
public:


    /*!
     *  @brief      コンストラクタ
     */
    IBullet(const std::string& file_name, COLLIDER_ID collider_id);

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
    virtual void    Initialize(UNIT_CATEGORY category, CShot::BulletParameters* bulletParameter, const CVector3& position, const CVector3& direction);

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
     *  @brief      半径取得
     *
     *  @return     半径
     */
    float           GetRadius();

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
    UNIT_CATEGORY   GetBulletCategory(void);

    /*!
     *  @brief      弾の色取得
     *
     *  @return     弾の色
     */
    unsigned int    GetBulletColor(void);

    /*!
     *  @brief      弾のダメージ取得
     *
     *  @return     弾のダメージ
     */
    float           GetBulletDamage(void);


    /*!
     *  @brief      弾の判定ID取得
     *
     *  @return     弾の判定ID
     */
    COLLIDER_ID     GetColliderID(void);

    /*!
     *  @brief      弾の判定ID取得
     *
     *  @return     弾の判定ID
     */
    CVector3        GetColliderPosA(void);
    /*!
     *  @brief      弾の判定ID取得
     *
     *  @return     弾の判定ID
     */
    CVector3        GetColliderPosB(void);


protected:


    static const unsigned int   m_player_color;     //!< プレイヤーの弾の色
    static const unsigned int   m_enemy_color;      //!< 敵の弾の色
    static const int            m_life_time;        //!< 持続時間
    static const float          m_radius;           //!< 弾の半径(初期値)
    static const std::string    m_file_name;        //!< 読み込むファイル名
    static const float	        m_max_speed;        //!< 最高速度

    CModel                      m_Model;            //!< モデル
    std::string                 m_FileName;         //!< モデルのファイル名
    CTransform                  m_Transform;        //!< 位置
    CVector3                    m_Velocity;         //!< 速度
    float                       m_Radius;
    unsigned int                m_Color;            //!< 色
    float                       m_Rotation;         //!< 回転値
    bool                        m_ActiveFlag;       //!< アクティブフラグ
    UNIT_CATEGORY               m_Category;         //!< 弾識別子
    int                         m_LifeTimer;        //!< 生存時間タイマー
    float                       m_Damage;           //!< ダメージ
    float				        m_Speed;            //!< 速さ
    float				        m_Accleration;		//!< 加速力
    CVector3			        m_Direction;

    COLLIDER_ID                 m_ColliderID;       //!< 判定ID
    CVector3                    m_CapsulePosA;      //!< カプセルを形成する二点中の一点
    CVector3                    m_CapsulePosB;      //!< カプセルを形成する二点中の一点
};
