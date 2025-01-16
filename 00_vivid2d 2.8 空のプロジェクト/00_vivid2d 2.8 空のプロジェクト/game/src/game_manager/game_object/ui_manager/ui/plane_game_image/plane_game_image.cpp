#include "plane_game_image.h"
#include "..\..\..\data_manager\data_manager.h"
const int               CPlaneGameImage::m_width = 1024;
const int               CPlaneGameImage::m_height = 1024;
const float             CPlaneGameImage::m_rotation_speed = 0.015f;
const float             CPlaneGameImage::m_speed = 0.5f;
const vivid::Rect       CPlaneGameImage::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CPlaneGameImage::m_scale = vivid::Vector2(1.0f, 1.0f);
const vivid::Vector2    CPlaneGameImage::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);
const std::string       CPlaneGameImage::m_file_names[] =
{ "data\\Textures\\plane_ui_fall_out.png", "data\\Textures\\plane_ui_dodge_ball.png" , "data\\Textures\\plane_ui_daruma.png", "data\\Textures\\plane_ui_daruma.png", };

/*
 *  �R���X�g���N�^
 */
CPlaneGameImage::
CPlaneGameImage(UI_ID id)
    : CUI(m_width, m_height, id)
	, m_Angle()
	, m_PosAngle()
	, m_InitialPosition()
	, m_FileName(m_file_names[0])
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
	//m_Transform.position = m_initial_position;
    // �摜�̓ǂݍ���
 //   m_Handle = LoadGraph(m_file_name.c_str(), TRUE);
	//MATERIALPARAM Material;
	//Material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	//Material.Specular = GetColorF(0.0f, 1.0f, 0.0f, 0.0f);
	//Material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	//Material.Emissive = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
	//Material.Power = 20.0f;
	//SetMaterialParam(Material);
	//m_Plane.SetUp(m_file_name);
	//m_Plane.SetScale(CVector3(m_width, m_height, 1.0f));
	//m_Plane.SetPosition(m_Transform.position);
	//m_Plane.SetRotation(m_Transform.rotation);
}

void CPlaneGameImage::Initialize(const CTransform& transform)
{
	CUI::Initialize(transform);

	m_InitialPosition = m_Transform.position;
	m_Handle = LoadGraph(m_FileName.c_str(), TRUE);
	m_Plane.SetUp(m_FileName);
	m_Plane.SetScale(CVector3(m_width, m_height, 1.0f));
	m_Plane.SetPosition(m_Transform.position);
	m_Plane.SetRotation(m_Transform.rotation);

	m_Angle = m_Transform.rotation.y;
}

/*
 *  �X�V
 */
void
CPlaneGameImage::
Update(void)
{
	m_PosAngle += m_speed;
	if (m_PosAngle > 360)
		m_PosAngle = 0;

	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::D))
	{
		m_Transform.position.y += 10.0f;
		m_Plane.SetPosition(m_Transform.position);

	}
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::A))
		m_Angle -= 10.0f;

	m_Plane.Update();
}

/*
 *  �`��
 */
void
CPlaneGameImage::
Draw(void)
{
	float rad = DEG_TO_RAD(m_PosAngle) + m_Angle;
	CMatrix m = CMatrix::Translate(m_Transform.position) * CMatrix::Rotate(CVector3(0.0f, rad, 0.0f));


	m_Plane.Draw(m);
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
