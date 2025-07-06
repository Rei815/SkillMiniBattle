#include "controller.h"
#include <DxLib.h>

const float	CController::m_vibration_power = 100.0f;
const float	CController::m_vibration_time = 1.0f;
CController::CController()
	: m_Active(true)
	, m_Stick()
	, m_LeftHorizontal(false)
	, m_LeftVertical(false)
	, m_PlayerID(PLAYER_ID::NONE)
	, m_Device(vivid::controller::DEVICE_ID::MAX)
{
}

CController::~CController()
{
}

void CController::Initialize(CONTROLLER_ID controller_id)
{
	SetControllerID(controller_id);
	m_ControllerID = controller_id;
}

void CController::Update(void)
{
	m_Stick = GetLeftStick();

	//ÉjÉÖÅ[ÉgÉâÉãÇ…Ç»Ç¡ÇΩÇÁfalse
	if (-0.1f <= m_Stick.x && m_Stick.x <= 0.1f)
	{
		m_LeftHorizontal = false;
	}
	if (-0.1f <= m_Stick.y && m_Stick.y <= 0.1f)
	{
		m_LeftVertical = false;
	}

}

void CController::Finalize(void)
{
	m_Active = false;
}

bool CController::IsActive(void)
{
	return m_Active;
}

bool CController::GetButtonDown(BUTTON_ID button_id)
{
	bool button = false;
	switch (button_id)
	{
	case BUTTON_ID::B:
		button = vivid::controller::Trigger(m_Device, vivid::controller::BUTTON_ID::B);
		break;
	case BUTTON_ID::A:
		button = vivid::controller::Trigger(m_Device, vivid::controller::BUTTON_ID::A);
		break;
	case BUTTON_ID::X:
		button = vivid::controller::Trigger(m_Device, vivid::controller::BUTTON_ID::X);
		break;
	case BUTTON_ID::Y:
		button = vivid::controller::Trigger(m_Device, vivid::controller::BUTTON_ID::Y);
		break;
	case BUTTON_ID::START:
		button = vivid::controller::Trigger(m_Device, vivid::controller::BUTTON_ID::START);
		break;
	case BUTTON_ID::ANY:
		button = (vivid::controller::Trigger(m_Device, vivid::controller::BUTTON_ID::START)
			|| vivid::controller::Trigger(m_Device, vivid::controller::BUTTON_ID::B)
			|| vivid::controller::Trigger(m_Device, vivid::controller::BUTTON_ID::A)
			|| vivid::controller::Trigger(m_Device, vivid::controller::BUTTON_ID::X)
			|| vivid::controller::Trigger(m_Device, vivid::controller::BUTTON_ID::Y));
		break;
	}
	return button;
}

bool CController::GetButtonUp(BUTTON_ID button_id)
{
	bool button = false;
	switch (button_id)
	{
	case BUTTON_ID::B:
		button = vivid::controller::Released(m_Device, vivid::controller::BUTTON_ID::B);
		break;
	case BUTTON_ID::A:
		button = vivid::controller::Released(m_Device, vivid::controller::BUTTON_ID::A);
		break;
	case BUTTON_ID::X:
		button = vivid::controller::Released(m_Device, vivid::controller::BUTTON_ID::X);
		break;
	case BUTTON_ID::Y:
		button = vivid::controller::Released(m_Device, vivid::controller::BUTTON_ID::Y);
		break;
	case BUTTON_ID::START:
		button = vivid::controller::Released(m_Device, vivid::controller::BUTTON_ID::START);
		break;
	case BUTTON_ID::ANY:
		button = (vivid::controller::Released(m_Device, vivid::controller::BUTTON_ID::START)
			|| vivid::controller::Released(m_Device, vivid::controller::BUTTON_ID::B)
			|| vivid::controller::Released(m_Device, vivid::controller::BUTTON_ID::A)
			|| vivid::controller::Released(m_Device, vivid::controller::BUTTON_ID::X)
			|| vivid::controller::Released(m_Device, vivid::controller::BUTTON_ID::Y));
		break;
	}
	return button;
}

bool CController::GetButtonHold(BUTTON_ID button_id)
{
	bool button = false;
	switch (button_id)
	{
	case BUTTON_ID::B:
		button = vivid::controller::Button(m_Device, vivid::controller::BUTTON_ID::B);
		break;
	case BUTTON_ID::A:
		button = vivid::controller::Button(m_Device, vivid::controller::BUTTON_ID::A);
		break;
	case BUTTON_ID::X:
		button = vivid::controller::Button(m_Device, vivid::controller::BUTTON_ID::X);
		break;
	case BUTTON_ID::Y:
		button = vivid::controller::Button(m_Device, vivid::controller::BUTTON_ID::Y);
		break;
	case BUTTON_ID::START:
		button = vivid::controller::Button(m_Device, vivid::controller::BUTTON_ID::START);
		break;
	case BUTTON_ID::ANY:
		button = (vivid::controller::Button(m_Device, vivid::controller::BUTTON_ID::START)
			|| vivid::controller::Button(m_Device, vivid::controller::BUTTON_ID::B)
			|| vivid::controller::Button(m_Device, vivid::controller::BUTTON_ID::A)
			|| vivid::controller::Button(m_Device, vivid::controller::BUTTON_ID::X)
			|| vivid::controller::Button(m_Device, vivid::controller::BUTTON_ID::Y));
		break;
	}
	return button;
}

vivid::Vector2 CController::GetLeftStick()
{
	return vivid::controller::GetAnalogStickLeft(m_Device);
}

bool CController::GetLeftHorizontal()
{
	return m_LeftHorizontal;
}

void CController::SetLeftHorizontal(bool flag)
{
	m_LeftHorizontal = flag;
}

bool CController::GetLeftVertical()
{
	return m_LeftVertical;
}

void CController::SetLeftVertical(bool flag)
{
	m_LeftVertical = flag;
}

CONTROLLER_ID CController::GetID()
{
	return m_ControllerID;
}

void CController::Vibration()
{
	vivid::controller::StartVibration(m_Device, m_vibration_power, m_vibration_time);
}

void CController::SetControllerID(CONTROLLER_ID controller_id)
{
	switch (controller_id)
	{
	case CONTROLLER_ID::ONE:
		m_Device = vivid::controller::DEVICE_ID::PLAYER1;
		m_JoyPad = DX_INPUT_PAD1;
		break;
	case CONTROLLER_ID::TWO:
		m_Device = vivid::controller::DEVICE_ID::PLAYER2;

		m_JoyPad = DX_INPUT_PAD2;
		break;
	case CONTROLLER_ID::THREE:
		m_Device = vivid::controller::DEVICE_ID::PLAYER3;

		m_JoyPad = DX_INPUT_PAD3;
		break;
	case CONTROLLER_ID::FOUR:
		m_Device = vivid::controller::DEVICE_ID::PLAYER4;

		m_JoyPad = DX_INPUT_PAD4;
		break;
	}
}

PLAYER_ID CController::GetPlayerID()
{
	return m_PlayerID;
}

void CController::SetPlayerID(PLAYER_ID player_id)
{
	m_PlayerID = player_id;
}