#include "skill_gauge.h"
#include "../../../unit_manager/unit/unit_id.h"

const int               CSkillGauge::m_height = 600;
const int               CSkillGauge::m_width = 600;
const vivid::Rect       CSkillGauge::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const float				CSkillGauge::m_default_scale = 1.0f;
const vivid::Vector2    CSkillGauge::m_anchor = vivid::Vector2(m_width / 2, m_height / 2);
const unsigned int      CSkillGauge::m_background_color = 0xff888888;

const std::string       CSkillGauge::m_file_name = "data\\Textures\\skill_gauge.png";
const double            CSkillGauge::m_start_percent = 0.0;

/*
 *  �R���X�g���N�^
 */
CSkillGauge::
CSkillGauge(UI_ID id)
	: CUI(m_width, m_height, id)
	, m_Scale(m_default_scale)
	, m_CenterPosition(vivid::Vector2::ZERO)
	, m_ImageHandle(0)
	, m_Percent(0)
{

}

/*
 *  �f�X�g���N�^
 */
CSkillGauge::
~CSkillGauge(void)
{
}

/*
 *  ������
 */
void
CSkillGauge::
Initialize(void)
{
	CUI::Initialize();

	m_ImageHandle = LoadGraph(m_file_name.c_str());
	m_Percent = 0;
}

/*!
 *  @brief      ������
 */
void
CSkillGauge::
Initialize(vivid::Vector2 position)
{
	Initialize();
	SetPosition(position);
}

/*
{
 *  �X�V
 */
void
CSkillGauge::
Update(void)
{
	CUI::Update();

	m_Position = m_CenterPosition - m_anchor;
}

/*
 *  �`��
 */
void
CSkillGauge::
Draw(void)
{
	CUI::Draw();

	if (0 < m_Percent && m_Percent < 100)
	{
		vivid::DrawTexture(m_file_name, m_Position, m_background_color, { 0,0,m_width, m_height }, m_anchor, vivid::Vector2(m_Scale, m_Scale));
		
		DrawCircleGauge(m_CenterPosition.x, m_CenterPosition.y, m_Percent, m_ImageHandle, m_start_percent, m_Scale, 1);
	}

}

/*
 *  ���
 */
void
CSkillGauge::
Finalize(void)
{
	CUI::Finalize();
}


void
CSkillGauge::
SetGauge(vivid::Vector2 position, float scale)
{
	SetPosition(position);
	SetScale(scale);
}

void
CSkillGauge::
SetPosition(const vivid::Vector2& position)
{
	m_CenterPosition = position;
}

void
CSkillGauge::
SetScale(float scale)
{
	m_Scale = (double)scale;
}

void
CSkillGauge::
SetPercent(float percent)
{
	if (percent < 0)
		percent = 0;

	if (percent > 100)
		percent = 100;

	m_Percent = (double)percent;
}