#include "player_1.h"

const DxLib::COLOR_F               CPlayer1::m_color = { 1,0,0,1 };
CPlayer1::CPlayer1()
{
}

CPlayer1::~CPlayer1()
{
}

void CPlayer1::Initialize(const CVector3& position, MOVE_ID moveId, bool aimFlag)
{
	m_Color = m_color;
	CPlayer::Initialize(position, moveId, aimFlag);
}
