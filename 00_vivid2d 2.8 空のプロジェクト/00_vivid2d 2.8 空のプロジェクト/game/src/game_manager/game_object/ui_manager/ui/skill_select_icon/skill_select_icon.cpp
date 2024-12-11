#include "skill_select_icon.h"
#include "../../../unit_manager/unit/unit_id.h"

const int               CSkillSelectIcon::m_height = 600;
const int               CSkillSelectIcon::m_width = 600;
const vivid::Rect       CSkillSelectIcon::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CSkillSelectIcon::m_default_scale = vivid::Vector2(0.5f, 0.5f);
const vivid::Vector2    CSkillSelectIcon::m_default_anchor = vivid::Vector2((m_width * m_default_scale.x) / 2, (m_height * m_default_scale.y) / 2);

const std::string CSkillSelectIcon::m_SkillIconFileName[] =
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
CSkillSelectIcon::
CSkillSelectIcon(UI_ID id)
	: CUI(m_width, m_height, id)
	, m_Anchor(m_default_anchor)
	, m_Scale(m_default_scale)
	, m_CenterPosition(vivid::Vector2::ZERO)
{
}

/*
 *  デストラクタ
 */
CSkillSelectIcon::
~CSkillSelectIcon(void)
{
}

/*
 *  初期化
 */
void
CSkillSelectIcon::
Initialize(void)
{
	CUI::Initialize();
}

/*
 *  更新
 */
void
CSkillSelectIcon::
Update(void)
{
	CUI::Update();

	m_Position = m_CenterPosition - m_Anchor;
}

/*
 *  描画
 */
void
CSkillSelectIcon::
Draw(void)
{
	CUI::Draw();

	vivid::DrawTexture(m_FileName, m_Position, 0xffffffff, m_rect, m_Anchor, m_Scale);
}

/*
 *  解放
 */
void
CSkillSelectIcon::
Finalize(void)
{
	CUI::Finalize();
}

void
CSkillSelectIcon::
SetIcon(SKILL_ID skill_id, vivid::Vector2 position, float scale)
{
	SetSkill(skill_id);
	SetPosition(position);
	SetScale(scale);
}

void
CSkillSelectIcon::
SetIcon(SKILL_ID skill_id, vivid::Vector2 position, vivid::Vector2 scale)
{
	SetSkill(skill_id);
	SetPosition(position);
	SetScale(scale);
}

void
CSkillSelectIcon::
SetSkill(SKILL_ID skill_id)
{
	m_FileName = m_SkillIconFileName[(int)skill_id];
}

void
CSkillSelectIcon::
SetPosition(vivid::Vector2 position)
{
	m_CenterPosition = position;
}

void
CSkillSelectIcon::
SetScale(float scale)
{
	SetScale(vivid::Vector2(scale, scale));
}

void
CSkillSelectIcon::
SetScale(vivid::Vector2 scale)
{
	m_Scale = scale;
	m_Anchor = vivid::Vector2((m_width * m_Scale.x) / 2, (m_height * m_Scale.y) / 2);
}
