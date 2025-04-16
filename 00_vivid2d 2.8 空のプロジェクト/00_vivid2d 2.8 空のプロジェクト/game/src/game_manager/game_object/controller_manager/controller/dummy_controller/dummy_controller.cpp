#include "dummy_controller.h"

CDummyController::CDummyController()
{
}

CDummyController::~CDummyController()
{
}

bool CDummyController::GetButtonDown(BUTTON_ID button_id)
{
	return false;
}

bool CDummyController::GetButtonUp(BUTTON_ID button_id)
{
	return false;
}

bool CDummyController::GetButtonHold(BUTTON_ID button_id)
{
	return false;
}

vivid::Vector2 CDummyController::GetLeftStick()
{
	return vivid::Vector2::ZERO;
}
