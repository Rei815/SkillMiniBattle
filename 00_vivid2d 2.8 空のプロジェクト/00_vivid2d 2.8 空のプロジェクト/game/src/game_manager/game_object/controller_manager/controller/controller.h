#pragma once
#include "button_id.h"
#include "controller_id.h"
#include <vivid.h>

class CController
{
public:
	CController();
	~CController();

    /*!
      *  @brief      初期化
      */
    void    Initialize(CONTROLLER_ID controller_id);

    /*!
     *  @brief      更新
     */
    void    Update(void);

    /*!
     *  @brief      解放
     */
    void    Finalize(void);

    /*!
     *  @brief      アクティブフラグの取得
     */
    bool    GetActive(void);

    /*!
     *  @brief      ボタンが押されたかどうか
     */
    bool    GetButtonDown(BUTTON_ID button_id);

    /*!
     *  @brief      コントローラーのIDを取得
     */
    CONTROLLER_ID    GetID();


private:
    /*!
     *  @brief      入力のリセット
     */
    void    Reset(void);

    bool                            m_Active;
    vivid::controller::DEVICE_ID    m_Device;
    int                             m_JoyPad;
    bool                            m_BButton;
    bool                            m_AnyButton;
    CONTROLLER_ID                   m_ControllerID;
};