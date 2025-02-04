#include "menu_poster.h"

const int               CMenuPoster::m_height = 298;
const int               CMenuPoster::m_width = 295;
const vivid::Rect       CMenuPoster::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CMenuPoster::m_default_scale = vivid::Vector2(1.0f, 1.0f);
const vivid::Vector2    CMenuPoster::m_anchor = vivid::Vector2(m_width / 2, m_height / 2);

const std::string CMenuPoster::m_file_name = "data\\Textures\\reward.png";

/*
 *  コンストラクタ
 */
CMenuPoster::
CMenuPoster(UI_ID id)
	: CUI(m_width, m_height, id)
{
	SetScale(m_default_scale);
}

/*
 *  デストラクタ
 */
CMenuPoster::
~CMenuPoster(void)
{
}

/*
 *  初期化
 */
void
CMenuPoster::
Initialize(void)
{
	CUI::Initialize();
}

/*!
 *  @brief      初期化
 */
void
CMenuPoster::
Initialize(const vivid::Vector2& position)
{
	Initialize();
	SetPosition(position);
}

/*
 *  更新
 */
void
CMenuPoster::
Update(void)
{
	CUI::Update();
}

/*
 *  描画
 */
void
CMenuPoster::
Draw(void)
{
	CUI::Draw();

	vivid::DrawTexture(m_file_name, m_Position, 0xffffffff, m_rect, m_anchor, m_Scale);
}

/*
 *  解放
 */
void
CMenuPoster::
Finalize(void)
{
	CUI::Finalize();
}

void
CMenuPoster::
SetPosition(const vivid::Vector2& position)
{
	CUI::SetPosition(position - m_anchor);
}