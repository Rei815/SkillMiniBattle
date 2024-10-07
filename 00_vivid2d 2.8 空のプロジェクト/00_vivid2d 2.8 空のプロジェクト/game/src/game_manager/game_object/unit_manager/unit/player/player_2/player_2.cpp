#include "player_2.h"

const DxLib::COLOR_F				CPlayer2::m_color = { 0,1,0,1 };
const std::string					CPlayer2::m_file_name = "data\\Models\\Player.mv1";
CPlayer2::CPlayer2()
	: CPlayer(UNIT_ID::PLAYER2)
{
}

CPlayer2::~CPlayer2()
{
}

void CPlayer2::Initialize(const CVector3& position, MOVE_ID moveId)
{
	m_Color = m_color;
	m_Controller = DX_INPUT_PAD2;

	CPlayer::Initialize(position, moveId);
}
