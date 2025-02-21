#include "controller.h"
#include <DxLib.h>

const float	CController::m_vibration_power = 100.0f;
const float	CController::m_vibration_time = 1.0f;
CController::CController()
	: m_Active(true)
	, m_BButton(false)
	, m_AllButton(false)
	, m_BButtonDown(0)
	, m_AllButtonDown(0)
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

}

void CController::Finalize(void)
{
	m_Active = false;
}

bool CController::GetActive(void)
{
	return m_Active;
}

bool CController::GetButtonDown(INPUT_ID input_id)
{
	bool input = false;
	switch (input_id)
	{
	case INPUT_ID::B:
		input = vivid::controller::Trigger(m_Device, vivid::controller::INPUT_ID::B);
		break;
	case INPUT_ID::A:
		input = vivid::controller::Trigger(m_Device, vivid::controller::INPUT_ID::A);
		break;
	case INPUT_ID::ALL:
		//input = vivid::controller::Trigger(m_Device, vivid::controller::INPUT_ID::);
		break;
	case INPUT_ID::STICK_LEFT:
		input = vivid::controller::Trigger(m_Device, vivid::controller::INPUT_ID::LEFT);
		break;
	case INPUT_ID::STICK_RIGHT:
		input = vivid::controller::Trigger(m_Device, vivid::controller::INPUT_ID::RIGHT);
		break;
	}
	return input;
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

void CController::Reset(void)
{
	m_BButton = false;
	m_AllButton = false;
}
