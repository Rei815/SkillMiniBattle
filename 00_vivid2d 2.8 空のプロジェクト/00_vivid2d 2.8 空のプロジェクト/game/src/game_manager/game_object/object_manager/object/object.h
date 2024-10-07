#pragma once
#include "../../model_manager/model/model.h"

class IObject
{
public:
    IObject();
    ~IObject();

    /*!
     *  @brief      初期化
     *
     */
    virtual void    Initialize(const CVector3& pos);

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

protected:
    static const float  m_fall_speed;
    CModel			    m_Model;
    CTransform		    m_Transform;
    CVector3            m_Velocity;
    std::string         m_FileName;
    float               m_FallSpeed;
    bool                m_ActiveFlag;
};