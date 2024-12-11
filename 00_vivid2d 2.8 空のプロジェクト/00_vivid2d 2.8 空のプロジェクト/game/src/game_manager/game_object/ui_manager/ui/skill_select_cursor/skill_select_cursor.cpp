#include "skill_select_cursor.h"

const int               CSkillSelectCursor::m_height = 600;
const int               CSkillSelectCursor::m_width = 600;
const vivid::Rect       CSkillSelectCursor::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CSkillSelectCursor::m_default_scale = vivid::Vector2(0.5f, 0.5f);
const vivid::Vector2    CSkillSelectCursor::m_default_anchor = vivid::Vector2((m_width * m_default_scale.x) / 2, (m_height * m_default_scale.y) / 2);

const std::string CSkillSelectCursor::m_cursorFileName[] = 
	{
		"data\\Textures\\skill_cursor_1P.png",
		"data\\Textures\\skill_cursor_2P.png",
		"data\\Textures\\skill_cursor_3P.png",
		"data\\Textures\\skill_cursor_4P.png"
	};

/*
 *  コンストラクタ
 */
CSkillSelectCursor::
CSkillSelectCursor(UI_ID id)
	: CUI(m_width, m_height, id)
	, m_Anchor(m_default_anchor)
	, m_Scale(m_default_scale)
	, m_CenterPosition(vivid::Vector2::ZERO)
{
}

/*
 *  デストラクタ
 */
CSkillSelectCursor::
~CSkillSelectCursor(void)
{
}

/*
 *  初期化
 */
void
CSkillSelectCursor::
Initialize(void)
{
	CUI::Initialize();
}

/*
 *  更新
 */
void
CSkillSelectCursor::
Update(void)
{
	CUI::Update();

	m_Position = m_CenterPosition - m_Anchor;
}

/*
 *  描画
 */
void
CSkillSelectCursor::
Draw(void)
{
	CUI::Draw();

	vivid::DrawTexture(m_FileName, m_Position, 0xffffffff, m_rect, m_Anchor, m_Scale);
}

/*
 *  解放
 */
void
CSkillSelectCursor::
Finalize(void)
{
	CUI::Finalize();
}


void
CSkillSelectCursor::
SetCursor(UNIT_ID player_id, vivid::Vector2 position, float scale)
{
	SetPlayer(player_id);
	SetPosition(position);
	SetScale(scale);
}

void
CSkillSelectCursor::
SetCursor(UNIT_ID player_id, vivid::Vector2 position, vivid::Vector2 scale)
{
	SetPlayer(player_id);
	SetPosition(position);
	SetScale(scale);
}

void
CSkillSelectCursor::
SetPlayer(UNIT_ID player_id)
{
	m_FileName = m_cursorFileName[(int)player_id];	
}

void
CSkillSelectCursor::
SetPosition(vivid::Vector2 position)
{
	m_CenterPosition = position;
}

void
CSkillSelectCursor::
SetScale(float scale)
{
	SetScale(vivid::Vector2(scale, scale));
}

void
CSkillSelectCursor::
SetScale(vivid::Vector2 scale)
{
	m_Scale = scale;
	m_Anchor = vivid::Vector2((m_width * m_Scale.x) / 2, (m_height * m_Scale.y) / 2);
}