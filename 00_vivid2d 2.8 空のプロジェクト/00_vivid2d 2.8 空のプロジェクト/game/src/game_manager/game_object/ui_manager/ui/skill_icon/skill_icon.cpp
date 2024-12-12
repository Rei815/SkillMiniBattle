#include "skill_icon.h"
#include "../../../unit_manager/unit/unit_id.h"

const int               CSkillIcon::m_height = 600;
const int               CSkillIcon::m_width = 600;
const vivid::Rect       CSkillIcon::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CSkillIcon::m_default_scale = vivid::Vector2(0.5f, 0.5f);
const vivid::Vector2    CSkillIcon::m_anchor = vivid::Vector2(m_width / 2, m_height / 2);

const unsigned int CSkillIcon::m_brightness_color = 0xffffffff;
const unsigned int CSkillIcon::m_dark_color = 0xff888888;

const std::string CSkillIcon::m_SkillIconFileName[] =
{
		"data\\Textures\\skill_icon_speedup.png",
		"data\\Textures\\skill_icon_jumpup.png",
		"data\\Textures\\skill_icon_floating.png",
		"data\\Textures\\skill_icon_stomp.png",
		"data\\Textures\\skill_icon_dash.png",
		"data\\Textures\\skill_icon_spawnwall_test.png",
		"data\\Textures\\skill_icon_barrier_test.png",
		"data\\Textures\\skill_icon_invisible.png",
		"data\\Textures\\skill_icon_resurrect.png",
		"data\\Textures\\skill_icon_null_test.png"
};

/*
 *  コンストラクタ
 */
CSkillIcon::
CSkillIcon(UI_ID id)
	: CUI(m_width, m_height, id)
	, m_FileName("")
	, m_Scale(m_default_scale)
	, m_CenterPosition(vivid::Vector2::ZERO)
	, m_Brightness(ICON_BRIGHTNESS::BRIGHT)
{
}

/*
 *  デストラクタ
 */
CSkillIcon::
~CSkillIcon(void)
{
}

/*
 *  初期化
 */
void
CSkillIcon::
Initialize(void)
{
	CUI::Initialize();

	m_Brightness = ICON_BRIGHTNESS::BRIGHT;
}

/*
 *  更新
 */
void
CSkillIcon::
Update(void)
{
	CUI::Update();

	m_Position = m_CenterPosition - m_anchor;
}

/*
 *  描画
 */
void
CSkillIcon::
Draw(void)
{
	CUI::Draw();

	if (m_FileName == "")
		return;

	switch (m_Brightness)
	{
	case CSkillIcon::ICON_BRIGHTNESS::BRIGHT:
		vivid::DrawTexture(m_FileName, m_Position, m_brightness_color, m_rect, m_anchor, m_Scale);
		break;
	case CSkillIcon::ICON_BRIGHTNESS::DARK:
		vivid::DrawTexture(m_FileName, m_Position, m_dark_color, m_rect, m_anchor, m_Scale);
		break;
	}
}

/*
 *  解放
 */
void
CSkillIcon::
Finalize(void)
{
	CUI::Finalize();
}

void
CSkillIcon::
SetIcon(SKILL_ID skill_id, vivid::Vector2 position, float scale)
{
	SetSkill(skill_id);
	SetPosition(position);
	SetScale(scale);
}

void
CSkillIcon::
SetIcon(SKILL_ID skill_id, vivid::Vector2 position, vivid::Vector2 scale)
{
	SetSkill(skill_id);
	SetPosition(position);
	SetScale(scale);
}

void
CSkillIcon::
SetSkill(SKILL_ID skill_id)
{
	m_FileName = m_SkillIconFileName[(int)skill_id];
}

void
CSkillIcon::
SetPosition(vivid::Vector2 position)
{
	m_CenterPosition = position;
}

void
CSkillIcon::
SetScale(float scale)
{
	SetScale(vivid::Vector2(scale, scale));
}

void
CSkillIcon::
SetScale(vivid::Vector2 scale)
{
	m_Scale = scale;
}


void
CSkillIcon::
SetBrightness(ICON_BRIGHTNESS icon_brightness)
{
	m_Brightness = icon_brightness;
}