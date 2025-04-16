#pragma once
#include "..\controller.h"

class CDummyController : public CController
{
public:
	CDummyController();
	~CDummyController();

    /*!
     *  @return bool �_�~�[�Ȃ̂�false 
     */
    bool        GetButtonDown(BUTTON_ID button_id) override;

    /*!
     *  @return bool �_�~�[�Ȃ̂�false
     */
    bool        GetButtonUp(BUTTON_ID button_id) override;

    /*!
     *  @return bool �_�~�[�Ȃ̂�false
     */
    bool        GetButtonHold(BUTTON_ID button_id) override;

    /*!
     *  @return vivid::Vector2 �_�~�[�Ȃ̂�(0,0)
     */
    vivid::Vector2        GetLeftStick() override;

private:

};
