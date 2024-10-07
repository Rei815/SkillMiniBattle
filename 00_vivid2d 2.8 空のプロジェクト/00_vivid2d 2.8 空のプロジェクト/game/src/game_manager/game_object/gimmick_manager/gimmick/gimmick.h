
#pragma once
#include "gimmick_id.h"
#include "../../../../mathematics/mathematics.h"
#include "../../model_manager/model/model.h"

class CGimmick
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CGimmick();

    /*!
     *  @brief      デストラクタ
     */
    virtual ~CGimmick(void);

    /*!
     *  @brief      初期化
     *
     */
    virtual void    Initialize();

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
    GIMMICK_ID      GetGimmickID(void);

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
    CTransform	            m_Transform;    //!< トランスフォーム
    bool                    m_ActiveFlag;       //!< アクティブフラグ
};
