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
	"data\\Textures\\plane_ui_daruma.png", };

/*
 *  コンストラクタ
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
 *  デストラクタ
 */
CPlaneGameImage::
~CPlaneGameImage(void)
{
}

/*
 *  初期化
 */
void
CPlaneGameImage::
Initialize(void)
{
	//m_Transform.position = m_initial_position;
    // 画像の読み込み
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
	m_Transform.scale = m_scale;
	m_Handle = LoadGraph(m_FileName.c_str(), TRUE);
	m_Plane.SetUp(m_FileName);
	m_Plane.SetTransform(m_Transform);
	m_PosAngle = m_Transform.rotation.y;
	m_Transform.rotation.y = m_Angle;
}

/*
 *  更新
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
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::W))
	{
		m_Transform.position.z += 10.0f;

	}
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::A))
	{
		m_Transform.position.x -= 10.0f;

	}
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::S))
	{
		m_Transform.position.z -= 10.0f;

	}
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::D))
	{
		m_Transform.position.x += 10.0f;

	}
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::G))
		m_Transform.rotation.y -= 1.0f;
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::Q))
		m_PosAngle -= 1.0f;
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::F))
		m_Transform.rotation.y += 1.0f;
	m_Plane.SetPosition(m_Transform.position);
	m_Plane.Update();

	float rad = DEG_TO_RAD(m_PosAngle);
	float _rad = DEG_TO_RAD(m_Angle);
	m_Matrix = CMatrix::Rotate(CVector3(0.0f, _rad, 0.0f)) * CMatrix::Translate(m_Transform.position) * CMatrix::Rotate(CVector3(0.0f, rad, 0.0f));

}

/*
 *  描画
 */
void
CPlaneGameImage::
Draw(void)
{

	
	m_Plane.Draw(m_Matrix);
}
/*
 *  解放
 */
void
CPlaneGameImage::
Finalize(void)
{
    // 読み込んだ画像のグラフィックハンドルを削除
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
