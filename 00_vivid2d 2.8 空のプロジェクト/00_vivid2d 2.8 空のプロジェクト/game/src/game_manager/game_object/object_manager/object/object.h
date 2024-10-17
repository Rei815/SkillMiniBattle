#pragma once
#include "../../model_manager/model/model.h"
#include "object_id.h"
#include "../../gimmick_manager/gimmick/gimmick.h"

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
    bool            GetActive(void);

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
     *  @brief      状態取得
     *
     *  @return     状態
     */
    OBJECT_STATE    GetState();

    /*!
     *  @brief      モデル取得
     *
     *  @return     モデル
     */
    CModel          GetModel();

    /*!
     *  @brief      状態設定
     *
     *  @param[in]  state   状態
     */
    void            SetState(OBJECT_STATE state);

    void            SetGimmick(CGimmick* gimmick);
    
    CGimmick*       GetGimmick();

    /*!
     *  @brief      モデル取得
     *
     *  @return     モデル
     */
    std::string     GetTag();
protected:
    static const float  m_limit_alpha;
    OBJECT_ID           m_ObjectID;
    CModel			    m_Model;
    CTransform		    m_Transform;
    CVector3            m_Velocity;
    std::string         m_FileName;
    bool                m_ActiveFlag;
    float               m_Alpha;
    CGimmick*           m_Gimmick;
    std::string         m_Tag;
};