#include "keyboard.h"

CKeyboard::CKeyboard()
	: CController()
{
}

CKeyboard::~CKeyboard()
{
}

bool CKeyboard::GetButtonDown(BUTTON_ID button_id)
{
	bool button = false;
	switch (button_id)
	{
	case BUTTON_ID::B:
		button = vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE);
		break;
	case BUTTON_ID::A:
		button = vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN);
		break;
	case BUTTON_ID::X:
		button = vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN);
		break;
	case BUTTON_ID::Y:
		button = vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::Y);
		break;
	case BUTTON_ID::START:
		button = vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::TAB);
		break;
	case BUTTON_ID::ANY:
		button = (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE)
			|| vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN));
		break;
	}
	return button;
}

bool CKeyboard::GetButtonUp(BUTTON_ID button_id)
{
	bool button = false;
	switch (button_id)
	{
	case BUTTON_ID::B:
		button = vivid::keyboard::Released(vivid::keyboard::KEY_ID::SPACE);
		break;
	case BUTTON_ID::A:
		button = vivid::keyboard::Released(vivid::keyboard::KEY_ID::RETURN);
		break;
	case BUTTON_ID::X:
		button = vivid::keyboard::Released(vivid::keyboard::KEY_ID::RETURN);
		break;
	case BUTTON_ID::Y:
		button = vivid::keyboard::Released(vivid::keyboard::KEY_ID::Y);
		break;
	case BUTTON_ID::START:
		button = vivid::keyboard::Released(vivid::keyboard::KEY_ID::TAB);
		break;
	case BUTTON_ID::ANY:
		button = (vivid::keyboard::Released(vivid::keyboard::KEY_ID::SPACE)
			|| vivid::keyboard::Released(vivid::keyboard::KEY_ID::RETURN));
		break;
	}
	return button;
}

bool CKeyboard::GetButtonHold(BUTTON_ID button_id)
{
	bool button = false;
	switch (button_id)
	{
	case BUTTON_ID::B:
		button = vivid::keyboard::Button(vivid::keyboard::KEY_ID::SPACE);
		break;
	case BUTTON_ID::A:
		button = vivid::keyboard::Button(vivid::keyboard::KEY_ID::RETURN);
		break;
	case BUTTON_ID::X:
		button = vivid::keyboard::Button(vivid::keyboard::KEY_ID::RETURN);
		break;
	case BUTTON_ID::Y:
		button = vivid::keyboard::Button(vivid::keyboard::KEY_ID::Y);
		break;
	case BUTTON_ID::START:
		button = vivid::keyboard::Button(vivid::keyboard::KEY_ID::TAB);
		break;
	case BUTTON_ID::ANY:
		button = (vivid::keyboard::Button(vivid::keyboard::KEY_ID::SPACE)
			|| vivid::keyboard::Button(vivid::keyboard::KEY_ID::RETURN));
		break;
	}
	return button;
}

vivid::Vector2 CKeyboard::GetLeftStick()
{
	vivid::Vector2 input = vivid::Vector2::ZERO;
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::W)) input.y -= 1.0f;
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::S)) input.y += 1.0f;
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::A)) input.x -= 1.0f;
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::D)) input.x += 1.0f;
	return input;
}
