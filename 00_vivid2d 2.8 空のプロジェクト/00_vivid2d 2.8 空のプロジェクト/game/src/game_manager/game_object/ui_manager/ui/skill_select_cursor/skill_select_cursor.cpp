#include "skill_select_cursor.h"

const vivid::Vector2    CSkillSelectCursor::m_positionList[] = 
	{
		vivid::Vector2(100 - 72, 348 - 72),		//スキル1
		vivid::Vector2(367 - 72, 348 - 72),		//スキル2
		vivid::Vector2(633 - 72, 348 - 72),		//スキル3
		vivid::Vector2(900 - 72, 348 - 72)		//スキル4
	};

const int               CSkillSelectCursor::m_height = 576;
const int               CSkillSelectCursor::m_width = 576;
const vivid::Rect       CSkillSelectCursor::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CSkillSelectCursor::m_scale = vivid::Vector2(0.5f, 0.5f);
const vivid::Vector2    CSkillSelectCursor::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);

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
}

/*
 *  描画
 */
void
CSkillSelectCursor::
Draw(void)
{
	CUI::Draw();

	vivid::DrawTexture(m_FileName, m_Position, 0xffffffff, m_rect, m_anchor, m_scale);
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
SetCursor(UNIT_ID player_id, int PosNum)
{
	m_FileName = m_cursorFileName[(int)player_id];

	if (PosNum >= 0 && PosNum < (int)UNIT_ID::NONE)
		m_Position = m_positionList[PosNum];
	else
		m_Position = vivid::Vector2().ZERO;
}