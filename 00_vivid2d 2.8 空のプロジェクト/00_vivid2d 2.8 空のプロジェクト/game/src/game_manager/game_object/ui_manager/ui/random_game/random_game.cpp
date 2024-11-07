#include "random_game.h"
const std::string       CRandomGame::m_file_name = "data\\Textures\\test.png";
const int               CRandomGame::m_width = 1024;
const int               CRandomGame::m_height = 1024;
const float             CRandomGame::m_rotation_speed = 0.015f;
const float             CRandomGame::m_speed = 1.0f;
const vivid::Rect       CRandomGame::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CRandomGame::m_scale = vivid::Vector2(1.0f, 1.0f);
const vivid::Vector2    CRandomGame::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);
const CVector3			CRandomGame::m_initial_position = CVector3(0.0f, 0.0f, 3000.0f);

/*
 *  �R���X�g���N�^
 */
CRandomGame::
CRandomGame(UI_ID id)
    : CUI(m_width, m_height, id)
	, m_Angle()
	, m_PosAngle()
{
}

/*
 *  �f�X�g���N�^
 */
CRandomGame::
~CRandomGame(void)
{
}

/*
 *  ������
 */
void
CRandomGame::
Initialize(void)
{
	m_Transform.position = m_initial_position;
    // �摜�̓ǂݍ���
    m_Handle = LoadGraph(m_file_name.c_str(), TRUE);
	MATERIALPARAM Material;
	Material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	Material.Specular = GetColorF(0.0f, 1.0f, 0.0f, 0.0f);
	Material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	Material.Emissive = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
	Material.Power = 20.0f;
	SetMaterialParam(Material);
	m_Plane.SetUp(m_file_name);
	m_Plane.SetScale(CVector3(m_width, m_height, 1.0f));
	m_Plane.SetPosition(m_Transform.position);
}

/*
 *  �X�V
 */
void
CRandomGame::
Update(void)
{
	//m_PosAngle += m_speed;
	//if (m_PosAngle > 360)
	//	m_PosAngle = 360;
	m_Angle += 0.01f;

	//m_Transform.RotateAround(CVector3(0.0f, 0.0f, 0.0f), CVector3(0.0f, 1.0f, 0.0f), m_PosAngle, m_initial_position);
	m_Plane.Update();
}

/*
 *  �`��
 */
void
CRandomGame::
Draw(void)
{
	m_Plane.SetRotation(CVector3(0, m_Angle, 0));
	m_Plane.Draw();
}
/*
 *  ���
 */
void
CRandomGame::
Finalize(void)
{
    // �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
    DeleteGraph(m_Handle);
}
