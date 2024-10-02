#include "player_2.h"

const DxLib::COLOR_F               CPlayer2::m_color = { 0,1,0,1 };
CPlayer2::CPlayer2()
{
}

CPlayer2::~CPlayer2()
{
}

void CPlayer2::Initialize(const CVector3& position, MOVE_ID moveId)
{
	m_Color = m_color;
	m_Controller = PAD_INPUT_2;

	CPlayer::Initialize(position, moveId);
}
