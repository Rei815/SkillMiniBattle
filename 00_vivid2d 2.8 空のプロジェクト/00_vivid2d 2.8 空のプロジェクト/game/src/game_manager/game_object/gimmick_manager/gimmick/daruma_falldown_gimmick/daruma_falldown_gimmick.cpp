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
}

void CDaruma_FallDownGimmick::Update(void)
{
	//鬼の振り向くカウントが0になったら
	if (m_TurnAroundTime <= 0)
	{
		m_TurnAround = true;

		//プレイヤーの数が0になったら
		if (m_RestPlayer <= 0)
		{

		}


	}

	//誰かが鬼にタッチしたら
	if (m_Touch)
	{



	}

}

void CDaruma_FallDownGimmick::Draw(void)
{
}

void CDaruma_FallDownGimmick::Finalize(void)
{
}
