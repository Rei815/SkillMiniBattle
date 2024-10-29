#include "finish_backGround.h"
const std::string		CFinishBackGround::m_file_name = "data\\Textures\\finish_backGround.png";
const vivid::Vector2	CFinishBackGround::m_position = vivid::Vector2(0, 0);
const int               CFinishBackGround::m_width = 1024;
const int               CFinishBackGround::m_height = 512;
const vivid::Rect       CFinishBackGround::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CFinishBackGround::m_scale = vivid::Vector2(0.5f, 0.5f);
const vivid::Vector2    CFinishBackGround::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);

CFinishBackGround::CFinishBackGround(UI_ID id)
	: CUI(m_width, m_height, id)
{
}

CFinishBackGround::~CFinishBackGround(void)
{
}

void CFinishBackGround::Initialize()
{
}

void CFinishBackGround::Update(void)
{
}

void CFinishBackGround::Draw(void)
{
	vivid::DrawTexture(m_file_name, m_position, 0xffffffff, m_rect, m_anchor, m_scale);

}

void CFinishBackGround::Finalize(void)
{
}
