#include "player_2.h"

const DxLib::COLOR_F               CPlayer2::m_color = { 0,1,0,1 };
CPlayer2::CPlayer2()
{
}

CPlayer2::~CPlayer2()
{
}

void CPlayer2::Initialize(const CVector3& position, MOVE_ID moveId, bool aimFlag)
{
	m_Color = m_color;
	CPlayer::Initialize(position, moveId, aimFlag);
}
