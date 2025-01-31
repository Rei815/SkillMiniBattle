#include "skill_cursor.h"

const int               CSkillCursor::m_height = 600;
const int               CSkillCursor::m_width = 600;
const vivid::Rect       CSkillCursor::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CSkillCursor::m_default_scale = vivid::Vector2(0.5f, 0.5f);
const vivid::Vector2    CSkillCursor::m_anchor = vivid::Vector2(m_width / 2, m_height / 2);

const std::string CSkillCursor::m_cursorFileName[] = 
	{
		"data\\Textures\\skill_cursor_1P.png",
		"data\\Textures\\skill_cursor_2P.png",
		"data\\Textures\\skill_cursor_3P.png",
		"data\\Textures\\skill_cursor_4P.png"
	};

/*
 *  �R���X�g���N�^
 */
CSkillCursor::
CSkillCursor(UI_ID id)
	: CUI(m_width, m_height, id)
	, m_FileName("")
	, m_Scale(m_default_scale)
	, m_CenterPosition(vivid::Vector2::ZERO)
{
}

/*
 *  �f�X�g���N�^
 */
CSkillCursor::
~CSkillCursor(void)
{
}

/*
 *  ������
 */
void
CSkillCursor::
Initialize(void)
{
	CUI::Initialize();
}

/*!
 *  @brief      ������
 */
void
CSkillCursor::
Initialize(vivid::Vector2 position)
{
	Initialize();
	SetPosition(position);
}

/*
 *  �X�V
 */
void
CSkillCursor::
Update(void)
{
	CUI::Update();
	//m_Position = m_CenterPosition - m_anchor;

}

/*
 *  �`��
 */
void
CSkillCursor::
Draw(void)
{
	CUI::Draw();

	if (m_FileName == "")
		return;

	vivid::DrawTexture(m_FileName, m_Position, 0xffffffff, m_rect, m_anchor, m_Scale);
}

/*
 *  ���
 */
void
CSkillCursor::
Finalize(void)
{
	CUI::Finalize();
}


void
CSkillCursor::
SetCursor(UNIT_ID player_id, vivid::Vector2 position, float scale)
{
	SetPlayer(player_id);
	SetPosition(position);
	SetScale(scale);
}

void
CSkillCursor::
SetCursor(UNIT_ID player_id, vivid::Vector2 position, vivid::Vector2 scale)
{
	SetPlayer(player_id);
	SetPosition(position);
	SetScale(scale);
}

void
CSkillCursor::
SetPlayer(UNIT_ID player_id)
{
	m_FileName = m_cursorFileName[(int)player_id];	
}

void
CSkillCursor::
SetPosition(vivid::Vector2 position)
{
	m_Position = position;
}

void CSkillCursor::SetCenterPosition(vivid::Vector2 position)
{
	m_CenterPosition = position;

}

void
CSkillCursor::
SetScale(float scale)
{
	SetScale(vivid::Vector2(scale, scale));
}

void
CSkillCursor::
SetScale(vivid::Vector2 scale)
{
	m_Scale = scale;
}