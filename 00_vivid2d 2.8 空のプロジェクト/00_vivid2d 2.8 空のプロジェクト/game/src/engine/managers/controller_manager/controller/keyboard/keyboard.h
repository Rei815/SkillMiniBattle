#pragma once
#include "..\controller.h"
class CKeyboard : public CController
{
public:
	CKeyboard();
	~CKeyboard();

    /*!
     *  @brief  ボタンに対応するキーが押されたかどうか
     */
    bool        GetButtonDown(BUTTON_ID button_id) override;

    /*!
     *  @brief  ボタンに対応するキーが離されたかどうか
     */
    bool        GetButtonUp(BUTTON_ID button_id) override;

    /*!
     *  @brief  ボタンに対応するキーが押されているかどうか
     */
    bool        GetButtonHold(BUTTON_ID button_id) override;

    /*!
     *  @brief  左スティックに対応するキーの状態を取得
     *
     *  @return vivid::Vector2          -1.0f～1.0f
     */
    vivid::Vector2        GetLeftStick() override;
};