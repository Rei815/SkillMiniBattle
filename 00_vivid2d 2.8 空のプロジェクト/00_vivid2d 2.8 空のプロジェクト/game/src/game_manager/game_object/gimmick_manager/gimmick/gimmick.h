
#pragma once
#include "gimmick_id.h"
#include "../../../../mathematics/mathematics.h"
#include "../../model/model.h"
#include "..\..\object_manager\object\object.h"
#include "..\..\..\..\utility\utility.h"
#include <memory>
class IObject;
enum class GIMMICK_STATE
{
    WAIT,
    PLAY,
    FINISH,
};

class CGimmick : public std::enable_shared_from_this<CGimmick>
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
     *  @param[in]  object          オブジェクトのポインタ
     */
    virtual void    Initialize(std::shared_ptr<IObject> object);

    /*!
     *  @brief      初期化
     * 
     *  @param[in]  object          オブジェクトのポインタ
     *  @param[in]  time            タイマーの設定
     */
    virtual void    Initialize(std::shared_ptr<IObject> object, float time);

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
    bool            IsActive(void);

    /*!
     *  @brief      アクティブフラグ設定
     *
     *  @param[in]  active  アクティブフラグ
     */
    void            Delete();

    /*!
     *  @brief      作動フラグ設定
     *
     *  @param[in]  flag  作動フラグ
     */
    virtual void    SetOperationFlag(bool flag);

    /*!
     *  @brief      タイマー設定
     *
     *  @param[in]  time  時間
     */
    void            SetTimer(float time);

    /*!
     *  @brief      状態取得
     *
     *  @return     状態
     */
    GIMMICK_STATE   GetState(void);

    /*!
     *  @brief      状態設定
     *
     *  @param[in]  state  状態
     */
    void            SetState(GIMMICK_STATE state);
protected:
    bool                        m_ActiveFlag;       //!< アクティブフラグ
    std::shared_ptr<IObject>    m_Object;           //!< 動作させるオブジェクト
    CTimer                      m_Timer;            //!< タイマー
    bool                        m_OperationFlag;    //!< 作動フラグ
    GIMMICK_STATE               m_State;            //!< 状態
};
