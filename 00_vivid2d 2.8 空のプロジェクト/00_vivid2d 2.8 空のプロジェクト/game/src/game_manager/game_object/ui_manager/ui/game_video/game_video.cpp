#include "game_video.h"

const int               CGameVideo::m_height = 720;
const int               CGameVideo::m_width = 1280;
const float             CGameVideo::m_scale = 0.4f;
const vivid::Vector2    CGameVideo::m_position = vivid::Vector2(80, 130);

//GAME_ID�Ɠ������тɂ���
const std::string CGameVideo::m_file_name[] =
{
		"data\\Video\\game_video_daruma_fall_down_test.mp4",
		"data\\Video\\game_video_fallout.mp4",
		"data\\Video\\game_video_dodge_ball.mp4",
		"data\\Video\\game_video_belt_conveyor.mp4",
		"data\\video_test.mp4",
		"data\\video_test.mp4",
		"data\\video_test.mp4",
		"data\\video_test.mp4",
		"data\\video_test.mp4",
};

/*
 *  �R���X�g���N�^
 */
CGameVideo::
CGameVideo(UI_ID id)
	: CUI(m_width, m_height, id)
{
}

/*
 *  �f�X�g���N�^
 */
CGameVideo::
~CGameVideo(void)
{
}

/*
 *  ������
 */
void
CGameVideo::
Initialize(void)
{
	CUI::Initialize(m_position);
	m_Handle = LoadGraph(m_file_name[0].c_str());
	ChangeMovieVolumeToGraph(0, m_Handle);
	PlayMovieToGraph(m_Handle);
}

/*
 *  �X�V
 */
void
CGameVideo::
Update(void)
{
	CUI::Update();

	//���[�v�Đ�������
	if (!GetMovieStateToGraph(m_Handle))
	{
		SeekMovieToGraph(m_Handle, 0);
		PlayMovieToGraph(m_Handle);
	}
}

/*
 *  �`��
 */
void
CGameVideo::
Draw(void)
{
	DrawExtendGraph(m_Position.x, m_Position.y, m_Position.x + m_width * m_scale, m_Position.y + m_height * m_scale, m_Handle, false);
}

/*
 *  ���
 */
void
CGameVideo::
Finalize(void)
{
	CUI::Finalize();
}

void
CGameVideo::
SetGameVideo(GAME_ID game_id)
{
	m_Handle = LoadGraph(m_file_name[(int)game_id].c_str());
	ChangeMovieVolumeToGraph(0, m_Handle);
	PlayMovieToGraph(m_Handle);
}