#include "menu_bg.h"

const int               CMenuBG::m_height = 641;
const int               CMenuBG::m_width = 1178;
const vivid::Rect       CMenuBG::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CMenuBG::m_anchor = vivid::Vector2(m_width / 2, m_height / 2);
const vivid::Vector2    CMenuBG::m_default_scale = vivid::Vector2(1.0f, 1.0f);
const vivid::Vector2    CMenuBG::m_default_position = vivid::Vector2(vivid::WINDOW_WIDTH / 2.0f, vivid::WINDOW_HEIGHT / 2.0f);
const std::string CMenuBG::m_file_name = "data\\Textures\\menu_bg.png";

/*
 *  �R���X�g���N�^
 */
CMenuBG::
CMenuBG(UI_ID id)
	: CUI(m_width, m_height, id, -1)
{
	SetScale(m_default_scale);
	SetPosition(m_default_position);
}

/*
 *  �f�X�g���N�^
 */
CMenuBG::
~CMenuBG(void)
{
}

/*
 *  ������
 */
void
CMenuBG::
Initialize(void)
{
	CUI::Initialize();
}

/*!
 *  @brief      ������
 */
void
CMenuBG::
Initialize(const vivid::Vector2& position)
{
	Initialize();
	SetPosition(position);
}

/*
 *  �X�V
 */
void
CMenuBG::
Update(void)
{
	CUI::Update();
	//m_Position = m_CenterPosition - m_anchor;
}

/*
 *  �`��
 */
void
CMenuBG::
Draw(void)
{
	CUI::Draw();

	vivid::DrawTexture(m_file_name, m_Position, 0xffffffff, m_rect, m_anchor, m_Scale);
}

/*
 *  ���
 */
void
CMenuBG::
Finalize(void)
{
	CUI::Finalize();
}

void
CMenuBG::
SetPosition(const vivid::Vector2& position)
{
	CUI::SetPosition(position - m_anchor);
}