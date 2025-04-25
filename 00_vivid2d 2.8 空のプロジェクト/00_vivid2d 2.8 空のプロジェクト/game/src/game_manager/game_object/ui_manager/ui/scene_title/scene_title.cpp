#include "scene_title.h"
#include "../../../scene_manager/scene_manager.h"


const int               CSceneTitle::m_height = 105;
const int               CSceneTitle::m_width = 800;
const vivid::Rect       CSceneTitle::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CSceneTitle::m_default_scale = vivid::Vector2(1.0f, 1.0f);
const vivid::Vector2    CSceneTitle::m_anchor = vivid::Vector2(m_width / 2, m_height / 2);

const vivid::Vector2    CSceneTitle::m_default_position = vivid::Vector2(vivid::WINDOW_WIDTH / 2.0f, vivid::WINDOW_HEIGHT / 6.0f);

const std::string CSceneTitle::m_scene_title_file_name[(int)SCENE_ID::MAX] =
{
		"data\\Textures\\skill_icon_null_test.png",
		"data\\Textures\\skill_icon_null_test.png",
		"data\\Textures\\skill_icon_null_test.png",
		"data\\Textures\\scene_title_selectplayer.png",
		"data\\Textures\\skill_icon_null_test.png",
		"data\\Textures\\scene_title_selectskill.png",
		"data\\Textures\\skill_icon_null_test.png",
		"data\\Textures\\skill_icon_null_test.png",
		"data\\Textures\\skill_icon_null_test.png",
		"data\\Textures\\skill_icon_null_test.png",
		"data\\Textures\\skill_icon_null_test.png",
		"data\\Textures\\skill_icon_null_test.png",
};

/*
 *  コンストラクタ
 */
CSceneTitle::
CSceneTitle(UI_ID id)
	: CUI(m_width, m_height, id)
	, m_FileName(m_scene_title_file_name[(int)CSceneManager::GetInstance().GetLastSceneID()])
{
	SetScale(m_default_scale);
	SetPosition(m_default_position);
}

/*
 *  デストラクタ
 */
CSceneTitle::
~CSceneTitle(void)
{
}

/*
 *  初期化
 */
void
CSceneTitle::
Initialize(void)
{
	CUI::Initialize();
}


/*!
 *  @brief      初期化
 */
void
CSceneTitle::
Initialize(vivid::Vector2 position)
{
	Initialize();
	SetPosition(position);
}

/*
 *  更新
 */
void
CSceneTitle::
Update(void)
{
	CUI::Update();
}

/*
 *  描画
 */
void
CSceneTitle::
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
CSceneTitle::
Finalize(void)
{
	CUI::Finalize();
}

void
CSceneTitle::
SetData(SCENE_ID scene_id, vivid::Vector2 position, float scale)
{
	SetSceneInfo(scene_id);
	SetPosition(position);
	SetScale(scale);
}

void
CSceneTitle::
SetData(SCENE_ID scene_id, vivid::Vector2 position, vivid::Vector2 scale)
{
	SetSceneInfo(scene_id);
	SetPosition(position);
	SetScale(scale);
}

void
CSceneTitle::
SetSceneInfo(SCENE_ID scene_id)
{
	if((int)scene_id < m_scene_title_file_name->length())
		m_FileName = m_scene_title_file_name[(int)scene_id];
}

void
CSceneTitle::
SetPosition(const vivid::Vector2& position)
{
	CUI::SetPosition(position - m_anchor);
}