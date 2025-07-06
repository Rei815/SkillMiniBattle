#pragma once
#include "controller_id.h"
#include <vivid.h>
#include "button_id.h"
#include "../../../../game/components/player_component/player_id.h"

class CPlayer;
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
     *  @brief  アクティブフラグの取得
     */
    bool        IsActive(void);

    /*!
     *  @brief  ボタンが押されたかどうか
     */
    virtual bool        GetButtonDown(BUTTON_ID button_id);

    /*!
     *  @brief  ボタンが離されたかどうか
     */
    virtual bool        GetButtonUp(BUTTON_ID button_id);

    /*!
     *  @brief  ボタンが押されているかどうか
     */
    virtual bool        GetButtonHold(BUTTON_ID button_id);

    /*!
     *  @brief  左スティックの状態を取得
     * 
     *  @return vivid::Vector2          -1.0f～1.0f
     */
    virtual vivid::Vector2        GetLeftStick();

    /*!
     *  @brief  左スティックが左右に傾いたかのフラグを取得
     *          自動でtrueにならない
     *  @return bool          左右に傾いたか
     */
    bool        GetLeftHorizontal();

    /*!
     *  @brief  左スティックが左右に傾いたかのフラグを設定
     * 
     *  @param[in]      flag    左右に傾いたか
     */
    void        SetLeftHorizontal(bool flag);

    /*!
     *  @brief  左スティックが上下に傾いたかのフラグを取得
     *          自動でtrueにならない
     *  @return bool          上下に傾いたか
     */
    bool        GetLeftVertical();

    /*!
     *  @brief  左スティックが上下に傾いたかのフラグを設定
     * 
     *  @param[in]      flag    上下に傾いたか
     */
    void        SetLeftVertical(bool flag);


    /*!
     *  @brief      コントローラーのIDを取得
     */
    CONTROLLER_ID   GetID();

    void            Vibration();

    void            SetControllerID(CONTROLLER_ID controller_id);

    /*!
     *  @brief      プレイヤーIDを取得
     *
     *  @return     プレイヤーID
     */
    PLAYER_ID       GetPlayerID();

    /*!
     *  @brief      ユニットIDを設定
     *
     *  @param[in]  unit_id    ユニットID
     */
    void            SetPlayerID(PLAYER_ID unit_id);


private:

    static const float              m_vibration_power;
    static const float              m_vibration_time;

    bool                            m_Active;
    vivid::controller::DEVICE_ID    m_Device;
    int                             m_JoyPad;
    CONTROLLER_ID                   m_ControllerID;
    bool                            m_LeftHorizontal;
    bool                            m_LeftVertical;
    vivid::Vector2                  m_Stick;
    PLAYER_ID                       m_PlayerID;
};