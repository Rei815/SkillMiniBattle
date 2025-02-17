#include "controller.h"
#include <DxLib.h>

CController::CController()
	: m_Active(true)
	, m_BButton(false)
	, m_AnyButton(false)
{
}

CController::~CController()
{
}

void CController::Initialize(CONTROLLER_ID controller_id)
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
	m_ControllerID = controller_id;
}

void CController::Update(void)
{
	Reset();
	if (GetJoypadInputState(m_JoyPad) & PAD_INPUT_B)
	{
		m_BButton = true;
	}
	if (GetJoypadInputState(m_JoyPad) & (PAD_INPUT_B | PAD_INPUT_A))
	{
		m_AnyButton = true;
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
		button = m_BButton;
		break;
	case BUTTON_ID::ALL:
		button = m_AnyButton;
		break;
	}
	return button;
}

CONTROLLER_ID CController::GetID()
{
	return m_ControllerID;
}

void CController::Reset(void)
{
	m_BButton = false;
	m_AnyButton = false;
}
