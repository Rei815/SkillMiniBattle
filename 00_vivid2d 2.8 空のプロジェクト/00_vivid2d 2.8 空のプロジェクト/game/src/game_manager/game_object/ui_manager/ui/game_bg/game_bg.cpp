#include "game_bg.h"
#include "../../../unit_manager/unit_manager.h"

const vivid::Vector2    CGameBG::m_position = vivid::Vector2(0, 0);
const int    CGameBG::m_width = 1280;
const int    CGameBG::m_height = 780;

/*
 *  �R���X�g���N�^
 */
CGameBG::
CGameBG(UI_ID id)
    : CUI(m_width, m_height, id)
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
Initialize(void)
{
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
    //vivid::DrawTexture("data\\Textures\\sea.jpg", m_position, 0xffffffff);


}

/*
 *  ���
 */
void
CGameBG::
Finalize(void)
{
}
