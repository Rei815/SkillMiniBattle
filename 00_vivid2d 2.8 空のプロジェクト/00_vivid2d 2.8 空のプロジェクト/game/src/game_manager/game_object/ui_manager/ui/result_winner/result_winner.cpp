#include "result_winner.h"
#include "../../../data_manager/data_manager.h"

const int    CResultWinner::m_width = 320;
const int    CResultWinner::m_height = 150;
const vivid::Vector2    CResultWinner::m_position = vivid::Vector2(vivid::GetWindowWidth() / 2.0f - m_width / 2.0f, vivid::GetWindowHeight() / 2.0f - m_height / 2.0f);

const std::string CResultWinner::m_file_name[] =
{
		"data\\Textures\\winner_1.png",
		"data\\Textures\\winner_2.png",
		"data\\Textures\\winner_3.png",
		"data\\Textures\\winner_4.png",
		"data\\Textures\\winner_none.png"
};

/*
 *  �R���X�g���N�^
 */
CResultWinner::
CResultWinner(UI_ID id)
	: CUI(m_width, m_height, id)
	, m_FileName(m_file_name[4])
{
}

/*
 *  �f�X�g���N�^
 */
CResultWinner::
~CResultWinner(void)
{
}

/*
 *  ������
 */
void
CResultWinner::
Initialize(void)
{
	CUI::Initialize(m_position);
	CDataManager& dm = CDataManager::GetInstance();
	//�ł��_���������v���C���[��ID���擾
	for (int i = 0; i < dm.GetCurrentPlayer(); i++)
	{
		if (dm.GetPlayerWin(i) == dm.GetMaxGameNum())
		{
			m_FileName = m_file_name[i];
			break;
		}
	}
}

/*
 *  �X�V
 */
void
CResultWinner::
Update(void)
{
	CUI::Update();
}

/*
 *  �`��
 */
void
CResultWinner::
Draw(void)
{
	vivid::DrawTexture(m_FileName, m_Position);


}

/*
 *  ���
 */
void
CResultWinner::
Finalize(void)
{
}
