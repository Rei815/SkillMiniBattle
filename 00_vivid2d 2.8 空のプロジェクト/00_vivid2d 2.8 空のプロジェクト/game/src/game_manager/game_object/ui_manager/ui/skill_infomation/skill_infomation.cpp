#include "skill_infomation.h"

const int				CSkillInfomation::m_height	= 200;
const int				CSkillInfomation::m_width	= 450;
const vivid::Rect		CSkillInfomation::m_rect	= vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2	CSkillInfomation::m_anchor	= vivid::Vector2(m_width / 2, m_height / 2);
const vivid::Vector2	CSkillInfomation::m_default_scale = vivid::Vector2(1.0f, 1.0f);

const std::string		CSkillInfomation::m_skill_info_file_name[] =
{
		"data\\Textures\\skill_info_speedup.png",
		"data\\Textures\\skill_info_jumpup.png",
		"data\\Textures\\skill_info_floating.png",
		"data\\Textures\\skill_info_stomp.png",
		"data\\Textures\\skill_info_dash.png",
		"data\\Textures\\skill_info_spawnwall.png",
		"data\\Textures\\skill_info_barrier.png",
		"data\\Textures\\skill_info_gravityarea.png",
		"data\\Textures\\skill_info_invisible.png",
		"data\\Textures\\skill_info_stun.png",
		"data\\Textures\\skill_info_mimicry.png",
		"data\\Textures\\skill_info_slow.png",
		"data\\Textures\\skill_info_ogrecontrol.png",
		"data\\Textures\\skill_info_resurrect.png",
		"data\\Textures\\skill_info_resurrect.png",
		"data\\Textures\\skill_info_strongwind.png",
		"data\\Textures\\skill_info_hidetopic.png",
		"data\\Textures\\skill_info.png"
};

const std::string		CSkillInfomation::m_skill_info_bg_file_name = "data\\Textures\\skill_info.png";

const int				CSkillInfomation::m_bg_height = 279;
const int				CSkillInfomation::m_bg_width = 568;
const vivid::Rect		CSkillInfomation::m_bg_rect = vivid::Rect{ 0, 0, m_bg_width, m_bg_height };
const vivid::Vector2	CSkillInfomation::m_bg_anchor = vivid::Vector2(m_bg_width / 2, m_bg_height / 2);
const vivid::Vector2    CSkillInfomation::m_bg_shift_pos = m_anchor - m_bg_anchor + vivid::Vector2(0.0f, -25.0f);

/*
 *  コンストラクタ
 */
CSkillInfomation::
CSkillInfomation(UI_ID id)
	: CUI(m_width, m_height, id)
	, m_FileName("")
{

	SetScale(m_default_scale);
}

/*
 *  デストラクタ
 */
CSkillInfomation::
~CSkillInfomation(void)
{
}

/*
 *  初期化
 */
void
CSkillInfomation::
Initialize(void)
{
	CUI::Initialize();
}


/*!
 *  @brief      初期化
 */
void
CSkillInfomation::
Initialize(vivid::Vector2 position)
{
	Initialize();
	SetPosition(position);
}

/*
 *  更新
 */
void
CSkillInfomation::
Update(void)
{
	CUI::Update();
}

/*
 *  描画
 */
void
CSkillInfomation::
Draw(void)
{
	CUI::Draw();

	vivid::DrawTexture(m_skill_info_bg_file_name, m_Position + m_bg_shift_pos, 0xffffffff, m_bg_rect, m_bg_anchor, m_Scale);

	if (m_FileName == "")
		return;

	vivid::DrawTexture(m_FileName, m_Position, 0xffffffff, m_rect, m_anchor, m_Scale);
}

/*
 *  解放
 */
void
CSkillInfomation::
Finalize(void)
{
	CUI::Finalize();
}

void
CSkillInfomation::
SetData(SKILL_ID skill_id, vivid::Vector2 position, float scale)
{
	SetSkillInfo(skill_id);
	SetPosition(position);
	SetScale(scale);
}

void
CSkillInfomation::
SetData(SKILL_ID skill_id, vivid::Vector2 position, vivid::Vector2 scale)
{
	SetSkillInfo(skill_id);
	SetPosition(position);
	SetScale(scale);
}

void
CSkillInfomation::
SetSkillInfo(SKILL_ID skill_id)
{
	if((int)skill_id < m_skill_info_file_name->length())
		m_FileName = m_skill_info_file_name[(int)skill_id];
}

void
CSkillInfomation::
SetPosition(const vivid::Vector2& position)
{
	CUI::SetPosition(position - m_anchor);
}