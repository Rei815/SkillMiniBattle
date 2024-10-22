#include "random_game.h"

const TCHAR*            CRandomGame::m_file_name = "data\\Textures\\test.png";
const int               CRandomGame::m_height = 960;
const int               CRandomGame::m_width = 540;
const vivid::Vector2    CRandomGame::m_position = vivid::Vector2(vivid::GetWindowWidth() / 2.0f, vivid::GetWindowHeight() / 2.0f);
const vivid::Rect       CRandomGame::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CRandomGame::m_scale = vivid::Vector2(1.0f, 1.0f);
const vivid::Vector2    CRandomGame::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);

/*
 *  �R���X�g���N�^
 */
CRandomGame::
CRandomGame(void)
    : CUI(m_width, m_height)
{
}

/*
 *  �f�X�g���N�^
 */
CRandomGame::
~CRandomGame(void)
{
}

/*
 *  ������
 */
void
CRandomGame::
Initialize(void)
{
    // �摜�̓ǂݍ���
    m_Handle = LoadGraph(m_file_name);
}

/*
 *  �X�V
 */
void
CRandomGame::
Update(void)
{

}

/*
 *  �`��
 */
void
CRandomGame::
Draw(void)
{
    DrawGraph(m_position.x, m_position.y, m_Handle, true);
}

/*
 *  ���
 */
void
CRandomGame::
Finalize(void)
{
    // �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
    DeleteGraph(m_Handle);
}
