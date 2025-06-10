#pragma once
#include "../../model/model.h"
#include "object_id.h"
#include "../../gimmick_manager/gimmick/gimmick.h"
#include <memory>
class CGimmick;
class IObject
{
public:
    IObject();
    ~IObject();

    /*!
     *  @brief      初期化
     *
     */
    virtual void    Initialize(OBJECT_ID id, const CTransform& pos);

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
     *  @brief      オブジェクトID取得
     *
     *  @return     オブジェクトID
     */
    OBJECT_ID       GetObjectID(void);

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
    void            SetActive(bool active);

    /*!
     *  @brief      位置取得
     *
     *  @return     位置
     */
    CVector3        GetPosition();
    /*!
     *  @brief      位置設定
     *
     *  @param[in]  position  位置
     */
    void            SetPosition(const CVector3& position);

    /*!
     *  @brief      回転取得
     *
     *  @return     回転
     */
    CVector3        GetRotation();

    /*!
     *  @brief      Tramsform取得
     *
     *  @return     Tramsform
     */
    CTransform      GetTransform();

    /*!
     *  @brief      位置設定
     *
     *  @param[in]  rotation  位置
     */
    void            SetRotation(const CVector3& rotation);

    /*!
     *  @brief      速度設定
     *
     *  @param[in]  velocity  速度
     */
    void            SetVelocity(const CVector3& velocity);

    /*!
     *  @brief      スケール設定
     *
     *  @param[in]  scale  オブジェクトの大きさ
     */
    void            SetScale(float scale);

    /*!
     *  @brief      スケール設定
     *
     *  @param[in]  scale  オブジェクトの大きさ
     */
    void            SetScale(const CVector3& scale);


    /*!
     *  @brief      モデル取得
     *
     *  @return     モデル
     */
    CModel          GetModel();

    void            SetGimmick(std::shared_ptr<CGimmick> gimmick);
    
    std::shared_ptr<CGimmick>       GetGimmick();

    /*!
     *  @brief      モデル取得
     *
     *  @return     モデル
     */
    std::string     GetTag();

    /*!
     *  @brief      アルファ値設定
     *
     *  @param[in]  alpha  アルファ値
     */
    void            SetAlpha(float alpha);

    /*!
     *  @brief      判定フラグ取得
     *
     *  @return     判定フラグ
     */
    bool            GetColliderActiveFlag();

    /*!
     *  @brief      判定フラグ設定
     *
     *  @param[in]  active  判定フラグ
     */
    void            SetColliderActiveFlag(bool active);

protected:
    static const float          m_limit_alpha;          //!< アルファ値の限界値
    OBJECT_ID                   m_ObjectID;             //!< オブジェクトのID
    CModel			            m_Model;                //!< モデル
    CTransform		            m_Transform;            //!< トランスフォーム
    CVector3                    m_Velocity;             //!< 速度
    std::string                 m_FileName;             //!< ファイル名
    bool                        m_ActiveFlag;           //!< アクティブフラグ
    float                       m_Alpha;                //!< アルファ値
    std::shared_ptr<CGimmick>   m_Gimmick;              //!< ギミック
    std::string                 m_Tag;                  //!< タグ名
    bool                        m_ColliderActiveFlag;   //!< 判定を取るか
};