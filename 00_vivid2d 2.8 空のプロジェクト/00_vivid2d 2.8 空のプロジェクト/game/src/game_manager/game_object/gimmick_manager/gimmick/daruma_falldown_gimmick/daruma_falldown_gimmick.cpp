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

	//�S�̐U������J�E���g��0�ɂȂ�����
	

	//�N�����S�Ƀ^�b�`������
	if (m_Touch)
	{



	}

	//�v���C���[�̐���0�ɂȂ�����
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
