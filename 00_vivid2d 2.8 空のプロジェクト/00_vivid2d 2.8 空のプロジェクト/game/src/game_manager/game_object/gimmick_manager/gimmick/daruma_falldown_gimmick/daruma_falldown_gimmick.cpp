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
	//�S�̐U������J�E���g��0�ɂȂ�����
	if (m_TurnAroundTime <= 0)
	{
		m_TurnAround = true;

		


	}

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
