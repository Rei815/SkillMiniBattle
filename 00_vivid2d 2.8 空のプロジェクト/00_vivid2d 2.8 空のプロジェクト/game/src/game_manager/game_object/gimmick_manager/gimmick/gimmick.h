
#pragma once
#include "gimmick_id.h"
#include "../../../../mathematics/mathematics.h"
#include "../../model_manager/model/model.h"
#include "..\..\object_manager\object\object.h"
#include "..\..\..\..\utility\utility.h"
class IObject;
enum class GIMMICK_STATE
{
    WAIT,
    PLAY,
    FINISH,
};

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
    virtual void    Initialize(IObject* object);

    /*!
     *  @brief      初期化
     *  @param[in]  object          オブジェクトのポインタ
     *  @param[in]  time            タイマーの設定
     *
     */
    virtual void    Initialize(IObject* object, float time);

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

    virtual void    SetSwitch(bool sw);

    void            SetTimer(float time);

    /*!
     *  @brief      状態取得
     *
     *  @return     状態
     */
    GIMMICK_STATE   GetState(void);

    void            SetState(GIMMICK_STATE state);
protected:
    bool            m_ActiveFlag;   //!< アクティブフラグ
    IObject*        m_Object;
    CTimer          m_Timer;
    bool            m_Switch;
    GIMMICK_STATE   m_State;
};
