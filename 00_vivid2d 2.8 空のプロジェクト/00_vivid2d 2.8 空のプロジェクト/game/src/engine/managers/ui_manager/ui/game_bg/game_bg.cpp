#include "game_bg.h"
const vivid::Vector2    CGameBG::m_position = vivid::Vector2(0, 0);
const int    CGameBG::m_width = 1280;
const int    CGameBG::m_height = 780;

/*
 *  �R���X�g���N�^
 */
CGameBG::
CGameBG(UI_ID id)
    : CUI(m_width, m_height, id, -2)
{
}

/*
 *  �f�X�g���N�^
 */
CGameBG::
~CGameBG(void)
{
}

/*
 *  ������
 */
void
CGameBG::
Initialize(const std::string file_name)
{
    m_FileName = file_name;
}

/*
 *  �X�V
 */
void
CGameBG::
Update(void)
{

}

/*
 *  �`��
 */
void
CGameBG::
Draw(void)
{
    vivid::DrawTexture(m_FileName, m_position, 0xffffffff);
}

/*
 *  ���
 */
void
CGameBG::
Finalize(void)
{
}
