#pragma once
#include "../../model_manager/model/model.h"
#include "object_id.h"

class IObject
{
public:
    IObject();
    ~IObject();

    /*!
     *  @brief      初期化
     *
     */
    virtual void    Initialize(OBJECT_ID id, const CVector3& pos);

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
     *  @brief      位置設定
     *
     *  @param[in]  position  位置
     */
    void            SetPosition(const CVector3& position);

    /*!
     *  @brief      速度設定
     *
     *  @param[in]  velocity  速度
     */
    void            SetVelocity(const CVector3& velocity);

protected:
    OBJECT_ID           m_ObjectID;
    static const float  m_fall_speed;
    CModel			    m_Model;
    CTransform		    m_Transform;
    CVector3            m_Velocity;
    std::string         m_FileName;
    float               m_FallSpeed;
    bool                m_ActiveFlag;
};