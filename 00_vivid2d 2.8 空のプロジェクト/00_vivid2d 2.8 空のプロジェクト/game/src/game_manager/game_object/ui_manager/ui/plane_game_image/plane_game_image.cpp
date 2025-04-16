#include "plane_game_image.h"
#include "..\..\..\data_manager\data_manager.h"
const int               CPlaneGameImage::m_width = 1024;
const int               CPlaneGameImage::m_height = 1024;
const float             CPlaneGameImage::m_rotation_speed = 0.015f;
const float             CPlaneGameImage::m_speed = 0.5f;
const vivid::Rect       CPlaneGameImage::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const CVector3			CPlaneGameImage::m_scale = CVector3(0.3f, 0.3f, 0.3f);
const vivid::Vector2    CPlaneGameImage::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);
const std::string       CPlaneGameImage::m_file_names[] =
{
	"data\\Textures\\plane_ui_daruma.png",
	"data\\Textures\\plane_ui_fall_out.png",
	"data\\Textures\\plane_ui_dodge_ball.png",
	"data\\Textures\\plane_ui_belt_conveyor.png", 
	"data\\Textures\\plane_ui_daruma.png", 
	"data\\Textures\\plane_ui_daruma.png", 
	"data\\Textures\\plane_ui_daruma.png"
};

/*
 *  �R���X�g���N�^
 */
CPlaneGameImage::
CPlaneGameImage(UI_ID id)
    : CUI(m_width, m_height, id, 1)
	, m_Angle()
	, m_PosAngle()
	, m_InitialPosition()
	, m_FileName(m_file_names[0])
	, m_Matrix()
	, m_Speed(m_speed)
	, m_Animation(nullptr)

{
}

/*
 *  �f�X�g���N�^
 */
CPlaneGameImage::
~CPlaneGameImage(void)
{
}

/*
 *  ������
 */
void
CPlaneGameImage::
Initialize(void)
{
}

void CPlaneGameImage::Initialize(const CTransform& transform)
{
	CUI::Initialize(transform);

	m_InitialPosition = m_Transform.position;
	m_Transform.scale = m_scale;
	m_Handle = LoadGraph(m_FileName.c_str(), TRUE);
	m_Plane.SetUp(m_FileName);
	m_Plane.SetTransform(m_Transform);
	m_PosAngle = m_Transform.rotation.y;
	m_Transform.rotation.y = m_Angle;
}

/*
 *  �X�V
 */
void
CPlaneGameImage::
Update(void)
{
	CUI::Update();
	m_PosAngle += m_Speed;
	if (m_PosAngle > 360)
		m_PosAngle = 0;
	if (m_Angle > 360)
		m_Angle = 0;
	m_Plane.SetPosition(m_Transform.position);
	m_Plane.Update();

	float rad = DEG_TO_RAD(m_PosAngle);
	float _rad = DEG_TO_RAD(m_Angle);

	//�s��̍쐬
	//��]��Ɉړ����A�ēx��]������
	m_Matrix = CMatrix::Rotate(CVector3(0.0f, _rad, 0.0f)) * CMatrix::Translate(m_Transform.position) * CMatrix::Rotate(CVector3(0.0f, rad, 0.0f));

}

/*
 *  �`��
 */
void
CPlaneGameImage::
Draw(void)
{	
	m_Plane.Draw(m_Matrix);
}
/*
 *  ���
 */
void
CPlaneGameImage::
Finalize(void)
{
    // �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
    DeleteGraph(m_Handle);
}

GAME_ID CPlaneGameImage::GetGameID(void)
{
	return m_GameID;
}

void CPlaneGameImage::SetGameID(GAME_ID game_id)
{
	m_GameID = game_id;
	m_FileName = m_file_names[(int)game_id];
	m_Plane.SetUp(m_FileName);

}

void CPlaneGameImage::SetTransform(const CTransform& transform)
{
	m_Transform = transform;
	m_Plane.SetTransform(transform);
}

void CPlaneGameImage::SetPosAngle(float angle)
{
	m_PosAngle = angle;
}

void CPlaneGameImage::SetSpeed(float speed)
{
	m_Speed = speed;
}

IAnimation* CPlaneGameImage::GetAnimation(void)
{
	return m_Animation;
}

void CPlaneGameImage::SetAnimation(IAnimation* animation)
{
	m_Animation = animation;
}
