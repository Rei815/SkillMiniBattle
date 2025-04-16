#pragma once
#include "..\controller.h"

class CDummyController : public CController
{
public:
	CDummyController();
	~CDummyController();

    /*!
     *  @return bool ダミーなのでfalse 
     */
    bool        GetButtonDown(BUTTON_ID button_id) override;

    /*!
     *  @return bool ダミーなのでfalse
     */
    bool        GetButtonUp(BUTTON_ID button_id) override;

    /*!
     *  @return bool ダミーなのでfalse
     */
    bool        GetButtonHold(BUTTON_ID button_id) override;

    /*!
     *  @return vivid::Vector2 ダミーなので(0,0)
     */
    vivid::Vector2        GetLeftStick() override;

private:

};
