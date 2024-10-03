
#pragma once
#include "gimmick_id.h"
#include "../../../../mathematics/mathematics.h"
#include "../../model_manager/model/model.h"

class IGimmick
{
public:
    IGimmick();
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  gimmick_id     ギミックID
     */
    IGimmick(GIMMICK_ID gimmick_id);

    /*!
     *  @brief      デストラクタ
     */
    virtual ~IGimmick(void);

    /*!
     *  @brief      初期化
     *
     */
    virtual void    Initialize(const CVector3& position);

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
     *  @brief      ギミックID取得
     *
     *  @return     ギミックID
     */
    GIMMICK_ID         GetGimmickID(void);

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

    CModel                  m_Model;
    CTransform	            m_Transform;		    //!< トランスフォーム

};
