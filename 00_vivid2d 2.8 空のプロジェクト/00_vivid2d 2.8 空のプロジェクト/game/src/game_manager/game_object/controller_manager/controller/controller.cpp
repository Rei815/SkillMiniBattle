#include "controller.h"
#include <DxLib.h>

const float	CController::m_vibration_power = 100.0f;
const float	CController::m_vibration_time = 1.0f;
CController::CController()
	: m_Active(true)
	, m_Stick()
	, m_LeftHorizontal(false)
	, m_LeftVertical(false)
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
	if (m_Stick.x == 0.0f)
	{
		m_LeftHorizontal = false;
	}
	if (m_Stick.y == 0.0f)
	{
		m_LeftVertical = false;
	}
}

void CController::Finalize(void)
{
	m_Active = false;
}

bool CController::GetActive(void)
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