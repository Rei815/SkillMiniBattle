#include "daruma_falldown_gimmick.h"

CDaruma_FallDownGimmick::CDaruma_FallDownGimmick()
	 :m_TurnAround(false)
	, m_SeenMove(false)
	, m_Touch(false)
	, m_TurnAroundTime(0)
	, m_RestPlayer(0)
{
}

CDaruma_FallDownGimmick::~CDaruma_FallDownGimmick(void)
{
}

void CDaruma_FallDownGimmick::Initialize()
{
	m_Timer.SetUp(0);
}

void CDaruma_FallDownGimmick::Update(void)
{
	m_Timer.Update();

	//鬼の振り向くカウントが0になったら
	

	//誰かが鬼にタッチしたら
	if (m_Touch)
	{



	}

	//プレイヤーの数が0になったら
	if (m_RestPlayer <= 0)
	{

	}
}

void CDaruma_FallDownGimmick::Draw(void)
{
}

void CDaruma_FallDownGimmick::Finalize(void)
{
}
