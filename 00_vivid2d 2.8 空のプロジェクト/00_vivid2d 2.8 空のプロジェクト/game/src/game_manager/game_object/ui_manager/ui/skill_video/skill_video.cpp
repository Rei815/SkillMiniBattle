#include "skill_video.h"

const int               CSkillVideo::m_height = 400;
const int               CSkillVideo::m_width = 800;
const vivid::Vector2    CSkillVideo::m_default_scale = vivid::Vector2(1.0f, 1.0f);
const vivid::Vector2    CSkillVideo::m_default_position = vivid::Vector2(vivid::WINDOW_WIDTH / 3.0f, vivid::WINDOW_HEIGHT / 4.0f * 3.0f);

const std::string CSkillVideo::m_skill_video_file_name[] =
{
		"data\\Video\\skill_video_move_up.mp4",
		"data\\Video\\skill_video_jump_up.mp4",
		"data\\Video\\skill_video_floating.mp4",
		"data\\Video\\skill_video_stomp.mp4",
		"data\\Video\\skill_video_dash.mp4",
		"data\\Video\\skill_video_spawnwall.mp4",
		"data\\Video\\skill_video_barrier.mp4",
		"data\\Video\\skill_video_gravityarea.mp4",
		"data\\Video\\skill_video_invisible.mp4",
		"data\\Video\\skill_video_stun.mp4",
		"data\\Video\\skill_video_mimicry.mp4",
		"data\\Video\\skill_video_slow.mp4",
		"data\\Video\\skill_video_ogre_control.mp4",
		"data\\Video\\skill_video_resurrect_daruma.mp4",
		"data\\Video\\skill_video_resurrect_fallout.mp4",
		"data\\Video\\skill_video_resurrect_belt_conveyor.mp4",
		"data\\Video\\skill_video_strongwind.mp4",
		"data\\Video\\skill_video_hidetopic.mp4",
		"data\\video_test.mp4"
};

/*
 *  �R���X�g���N�^
 */
CSkillVideo::
CSkillVideo(UI_ID id)
	: CUI(m_width, m_height, id)
	, m_CenterPos(vivid::Vector2::ZERO)
	, m_NowSkillNum(-1)
{
	for (int i = 0; i < (int)UNIT_ID::NONE; i++)
	{
		m_Handle[i] = -1;
		m_HandleSkillID[i] = SKILL_ID::MAX;
	}

	SetScale(m_default_scale);
}

/*
 *  �f�X�g���N�^
 */
CSkillVideo::
~CSkillVideo(void)
{
}

/*
 *  ������
 */
void
CSkillVideo::
Initialize(void)
{
	CUI::Initialize();
	SetPosition(m_default_position);
}


/*!
 *  @brief      ������
 */
void
CSkillVideo::
Initialize(const vivid::Vector2& position)
{
	Initialize();
	SetPosition(position);
}

/*
 *  �X�V
 */
void
CSkillVideo::
Update(void)
{
	CUI::Update();
}

/*
 *  �`��
 */
void
CSkillVideo::
Draw(void)
{
	CUI::Draw();

	if (m_NowSkillNum >= 0 && m_NowSkillNum < (int)UNIT_ID::NONE)
	{
		if (GetMovieStateToGraph(m_Handle[m_NowSkillNum]) == 0)
		{
			SeekMovieToGraph(m_Handle[m_NowSkillNum], 0);
			PlayMovieToGraph(m_Handle[m_NowSkillNum]);
		}

		DrawExtendGraph(m_Position.x, m_Position.y, m_Position.x + m_Width * m_Scale.x, m_Position.y + m_Height * m_Scale.y, m_Handle[m_NowSkillNum], true);
	}
}

/*
 *  ���
 */
void
CSkillVideo::
Finalize(void)
{
	CUI::Finalize();

	ResetSkillVideo();
}

void
CSkillVideo::
SetPosition(const vivid::Vector2& position)
{
	m_CenterPos = position;
	CUI::SetPosition(position - vivid::Vector2(m_width * m_Scale.x / 2.0f, m_height * m_Scale.y / 2.0f));
}

void
CSkillVideo::
SetScale(float scale)
{
	CUI::SetScale(scale);

	SetPosition(m_CenterPos);
}

void
CSkillVideo::
SetScale(const vivid::Vector2& scale)
{
	CUI::SetScale(scale);

	SetPosition(m_CenterPos);
}

void
CSkillVideo::
SetSkillVideo(int skill_num, SKILL_ID skill_id)
{
	if (skill_num < 0 || skill_num >= (int)UNIT_ID::NONE)
		return;

	if (m_Handle[skill_num] != -1)
		return;

	m_HandleSkillID[skill_num] = skill_id;

	for (int i = 0; i < (int)UNIT_ID::NONE; i++)
	{
		if (i == skill_num)
			continue;

		if (m_HandleSkillID[i] != SKILL_ID::MAX)
		{
			if (m_skill_video_file_name[(int)m_HandleSkillID[skill_num]] == m_skill_video_file_name[(int)m_HandleSkillID[i]])
			{
				m_Handle[skill_num] = m_Handle[i];
				return;
			}
		}
	}

	m_Handle[skill_num] = LoadGraph(m_skill_video_file_name[(int)skill_id].c_str());
	ChangeMovieVolumeToGraph(0, m_Handle[skill_num]);
}

void
CSkillVideo::
ResetSkillVideo()
{
	for (int i = 0; i < (int)UNIT_ID::NONE; i++)
	{
		DeleteGraph(m_Handle[i]);
		m_Handle[i] = -1;
		m_HandleSkillID[i] = SKILL_ID::MAX;
	}

	m_NowSkillNum = -1;
}

void
CSkillVideo::
SetSkillNum(int skill_num)
{
	if (m_NowSkillNum == skill_num)
		return;

	if (m_NowSkillNum != -1)
	{
		SeekMovieToGraph(m_Handle[m_NowSkillNum], 0);
		PauseMovieToGraph(m_Handle[m_NowSkillNum]);
	}

	m_NowSkillNum = skill_num;

	SeekMovieToGraph(m_Handle[m_NowSkillNum], 0);
	PlayMovieToGraph(m_Handle[m_NowSkillNum]);
}