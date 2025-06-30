#include "finish_backGround.h"
const std::string		CFinishGameBG::m_file_name = "data\\Textures\\finish_backGround.png";
const vivid::Vector2	CFinishGameBG::m_position = vivid::Vector2(0, 0);
const int               CFinishGameBG::m_width = 1024;
const int               CFinishGameBG::m_height = 512;
const vivid::Rect       CFinishGameBG::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CFinishGameBG::m_scale = vivid::Vector2(0.5f, 0.5f);
const vivid::Vector2    CFinishGameBG::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);

CFinishGameBG::CFinishGameBG(UI_ID id)
	: CUI(m_width, m_height, id)
{
}

CFinishGameBG::~CFinishGameBG(void)
{
}

void CFinishGameBG::Initialize()
{
}

void CFinishGameBG::Update(void)
{
}

void CFinishGameBG::Draw(void)
{
	vivid::DrawTexture(m_file_name, m_position, 0xffffffff, m_rect, m_anchor, m_scale);

}

void CFinishGameBG::Finalize(void)
{
}
