#include "concentration_line.h"
const std::string		CConcentrationLine::m_file_name = "data\\Textures\\concentration_line.jpg";
const int               CConcentrationLine::m_width = 1280;
const int               CConcentrationLine::m_height = 720;
const vivid::Rect       CConcentrationLine::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CConcentrationLine::m_scale = vivid::Vector2(1.0f, 1.0f);
//const vivid::Vector2    CConcentrationLine::m_scale = vivid::Vector2(2.0f, 2.0f);
const vivid::Vector2    CConcentrationLine::m_anchor = vivid::Vector2(m_width / 2.0f, m_height / 2.0f);

CConcentrationLine::CConcentrationLine(UI_ID id)
	: CUI(m_width, m_height, id)
	, m_Angle(0)
{
}

CConcentrationLine::~CConcentrationLine(void)
{
}

void CConcentrationLine::Initialize()
{
}

void CConcentrationLine::Update(void)
{
	CUI::Update();
	//m_Angle += 0.01f;
}

void CConcentrationLine::Draw(void)
{
	vivid::DrawTexture(m_file_name, m_Position, 0xffffffff, m_rect, m_anchor, m_scale, m_Angle);

}

void CConcentrationLine::Finalize(void)
{
}
