#include "skill_name.h"

const int               CSkillName::m_height = 400;
const int               CSkillName::m_width = 800;
const vivid::Rect       CSkillName::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CSkillName::m_default_scale = vivid::Vector2(1.0f, 1.0f);
const vivid::Vector2    CSkillName::m_anchor = vivid::Vector2(m_width / 2, m_height / 2);

const std::string CSkillName::m_skill_info_file_name[] =
{
		"data\\Textures\\skill_info_speedup_test.png",
		"data\\Textures\\skill_info_jumpup_test.png",
		"data\\Textures\\skill_info_floating_test.png",
		"data\\Textures\\skill_info_stomp_test.png",
		"data\\Textures\\skill_info_dash_test.png",
		"data\\Textures\\skill_info_spawnwall_test.png",
		"data\\Textures\\skill_info_barrier_test.png",
		"data\\Textures\\skill_info_gravityarea_test.png",
		"data\\Textures\\skill_info_invisible_test.png",
		"data\\Textures\\skill_info_stun_test.png",
		"data\\Textures\\skill_info_mimicry_test.png",
		"data\\Textures\\skill_info_slow_test.png",
		"data\\Textures\\skill_info_ogrecontrol_test.png",
		"data\\Textures\\skill_info_resurrectdaruma_test.png",
		"data\\Textures\\skill_info_resurrectfallout_test.png",
		"data\\Textures\\skill_info_strongwind_test.png",
		"data\\Textures\\skill_info_hidetopic_test.png",
		"data\\Textures\\skill_info_test.png"
};

/*
 *  コンストラクタ
 */
CSkillName::
CSkillName(UI_ID id)
	: CUI(m_width, m_height, id)
	, m_FileName("")
{

	SetScale(m_default_scale);
}

/*
 *  デストラクタ
 */
CSkillName::
~CSkillName(void)
{
}

/*
 *  初期化
 */
void
CSkillName::
Initialize(void)
{
	CUI::Initialize();
}


/*!
 *  @brief      初期化
 */
void
CSkillName::
Initialize(vivid::Vector2 position)
{
	Initialize();
	SetPosition(position);
}

/*
 *  更新
 */
void
CSkillName::
Update(void)
{
	CUI::Update();
}

/*
 *  描画
 */
void
CSkillName::
Draw(void)
{
	CUI::Draw();

	if (m_FileName == "")
		return;

	vivid::DrawTexture(m_FileName, m_Position, 0xffffffff, m_rect, m_anchor, m_Scale);
}

/*
 *  解放
 */
void
CSkillName::
Finalize(void)
{
	CUI::Finalize();
}

void
CSkillName::
SetData(SKILL_ID skill_id, vivid::Vector2 position, float scale)
{
	SetSkillInfo(skill_id);
	SetPosition(position);
	SetScale(scale);
}

void
CSkillName::
SetData(SKILL_ID skill_id, vivid::Vector2 position, vivid::Vector2 scale)
{
	SetSkillInfo(skill_id);
	SetPosition(position);
	SetScale(scale);
}

void
CSkillName::
SetSkillInfo(SKILL_ID skill_id)
{
	if((int)skill_id < m_skill_info_file_name->length())
		m_FileName = m_skill_info_file_name[(int)skill_id];
}

void
CSkillName::
SetPosition(const vivid::Vector2& position)
{
	CUI::SetPosition(position - m_anchor);
}