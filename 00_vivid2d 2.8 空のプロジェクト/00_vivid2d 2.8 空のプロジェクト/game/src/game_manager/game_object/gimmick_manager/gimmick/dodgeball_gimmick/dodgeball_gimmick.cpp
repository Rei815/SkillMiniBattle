#include "dodgeball_gimmick.h"

//各方向（上下左右）に何個ずつ砲を出現させるか
const int CDodgeBallGimmick::m_cannnon_count = 3;

CDodgeBallGimmick::CDodgeBallGimmick()
	: m_CannonSpawnTimer(0)
{
}

CDodgeBallGimmick::~CDodgeBallGimmick(void)
{
}

void CDodgeBallGimmick::Initialize()
{
	m_CannonSpawnTimer = 0;
}

void CDodgeBallGimmick::Update(void)
{
}

void CDodgeBallGimmick::Draw(void)
{
}

void CDodgeBallGimmick::Finalize(void)
{
}
