#include "player_num_select.h"

const int               CPlayerNumSelect::m_height = 200;
const int               CPlayerNumSelect::m_width = 200;
const vivid::Rect       CPlayerNumSelect::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CPlayerNumSelect::m_default_scale = vivid::Vector2(1.0f, 1.0f);
const float             CPlayerNumSelect::m_selected_scale_magnification = 1.2f;
const vivid::Vector2    CPlayerNumSelect::m_anchor = vivid::Vector2(m_width / 2, m_height / 2);
const unsigned int      CPlayerNumSelect::m_default_color = 0xffaaaaaa;
const unsigned int      CPlayerNumSelect::m_selected_color = 0xffffffff;

const std::string CPlayerNumSelect::m_file_name[(int)UNIT_ID::NONE] =
{
	"data\\Textures\\player_num_1.png",
	"data\\Textures\\player_num_2.png",
	"data\\Textures\\player_num_3.png",
	"data\\Textures\\player_num_4.png"
};

/*
 *  コンストラクタ
 */
CPlayerNumSelect::
CPlayerNumSelect(UI_ID id)
	: CUI(m_width, m_height, id)
	, m_PlayerNum(1)
	, m_SelectedFlag(false)
{
	SetScale(m_default_scale);
}

/*
 *  デストラクタ
 */
CPlayerNumSelect::
~CPlayerNumSelect(void)
{
}

/*
 *  初期化
 */
void
CPlayerNumSelect::
Initialize(void)
{
	CUI::Initialize();
}

/*!
 *  @brief      初期化
 */
void
CPlayerNumSelect::
Initialize(const vivid::Vector2& position)
{
	Initialize();
	SetPosition(position);
}

/*
 *  更新
 */
void
CPlayerNumSelect::
Update(void)
{
	CUI::Update();
}

/*
 *  描画
 */
void
CPlayerNumSelect::
Draw(void)
{
	CUI::Draw();

	unsigned int Color = m_default_color;
	vivid::Vector2 Scale = m_Scale;

	if (m_SelectedFlag)
	{
		Color = m_selected_color;
		Scale *= m_selected_scale_magnification;
	}

	vivid::DrawTexture(m_file_name[m_PlayerNum - 1], m_Position, Color, m_rect, m_anchor, Scale);
}

/*
 *  解放
 */
void
CPlayerNumSelect::
Finalize(void)
{
	CUI::Finalize();
}

void
CPlayerNumSelect::
SetData(const vivid::Vector2& position, int player_num, vivid::Vector2 scale)
{
	SetPosition(position);
	SetPlayerNum(player_num);
	SetScale(scale);
}

void
CPlayerNumSelect::
SetData(const vivid::Vector2& position, int player_num, float scale)
{
	SetPosition(position);
	SetPlayerNum(player_num);
	SetScale(scale);
}

void
CPlayerNumSelect::
SetPosition(const vivid::Vector2& position)
{
	CUI::SetPosition(position - m_anchor);
}


void
CPlayerNumSelect::
SetPlayerNum(int player_num)
{
	if(player_num > 0 && player_num <= (int)UNIT_ID::NONE)
		m_PlayerNum = player_num;
}

void
CPlayerNumSelect::
SetSelected(bool selected)
{
	m_SelectedFlag = selected;
}