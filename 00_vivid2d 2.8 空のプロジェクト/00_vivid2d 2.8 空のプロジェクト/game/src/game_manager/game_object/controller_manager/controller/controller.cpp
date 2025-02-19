#include "controller.h"
#include <DxLib.h>

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
	//Reset();

	//B
	if (GetJoypadInputState(m_JoyPad) & PAD_INPUT_B)
	{
		m_BButtonDown++;
		m_BButton = true;
	}
	else
	{
		m_BButtonDown = 0;
		m_BButton = false;

	}

	//A
	if (GetJoypadInputState(m_JoyPad) & PAD_INPUT_A)
	{
		m_AButtonDown++;
		m_AButton = true;
	}
	else
	{
		m_AButtonDown = 0;
		m_AButton = false;
	}
	//All
	if (GetJoypadInputState(m_JoyPad) & (PAD_INPUT_A | PAD_INPUT_B))
	{
		m_AllButtonDown++;
		m_AllButton = true;
	}
	else
	{
		m_AllButtonDown = 0;
		m_AllButton = false;
	}
	//左スティックの左
	if (GetJoypadInputState(m_JoyPad) & PAD_INPUT_LEFT)
	{
		m_StickLeftDown++;
		m_StickLeftButton = true;
	}
	else
	{
		m_StickLeftDown = 0;
		m_StickLeftButton = false;
	}
	//左スティックの右
	if (GetJoypadInputState(m_JoyPad) & PAD_INPUT_RIGHT)
	{
		m_StickRightDown++;
		m_StickRightButton = true;
	}
	else
	{
		m_StickRightDown = 0;
		m_StickRightButton = false;
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

bool CController::GetButtonDown(INPUT_ID input_id)
{
	bool input = false;
	switch (input_id)
	{
	case INPUT_ID::B:
		input = m_BButton && (m_BButtonDown == 1);
		break;
	case INPUT_ID::A:
		input = m_AButton && (m_AButtonDown == 1);
		break;
	case INPUT_ID::ALL:
		input = m_AllButton && (m_AllButtonDown == 1);
		break;
	case INPUT_ID::STICK_LEFT:
		input = m_StickLeftButton && (m_StickLeftDown == 1);
		break;
	case INPUT_ID::STICK_RIGHT:
		input = m_StickRightButton && (m_StickRightDown == 1);
		break;
	}
	return input;
}

CONTROLLER_ID CController::GetID()
{
	return m_ControllerID;
}

void CController::Reset(void)
{
	m_BButton = false;
	m_AllButton = false;
}
