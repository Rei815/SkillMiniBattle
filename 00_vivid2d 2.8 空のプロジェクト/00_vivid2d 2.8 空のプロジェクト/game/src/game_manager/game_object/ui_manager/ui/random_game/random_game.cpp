#include "random_game.h"

const TCHAR*            CRandomGame::m_file_name = "data\\Textures\\test.png";
const int               CRandomGame::m_width = 1024;
const int               CRandomGame::m_height = 1024;
const float             CRandomGame::m_rotation_speed = 0.05f;
const float             CRandomGame::m_speed = 0.05f;
const vivid::Rect       CRandomGame::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CRandomGame::m_scale = vivid::Vector2(1.0f, 1.0f);
const vivid::Vector2    CRandomGame::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);

/*
 *  コンストラクタ
 */
CRandomGame::
CRandomGame(UI_ID id)
    : CUI(m_width, m_height, id)
	, m_Angle()
{
}

/*
 *  デストラクタ
 */
CRandomGame::
~CRandomGame(void)
{
}

/*
 *  初期化
 */
void
CRandomGame::
Initialize(void)
{
	m_Transform.position = CVector3(0.0f, 0.0f, 0.0f);
    // 画像の読み込み
    m_Handle = LoadGraph(m_file_name, TRUE);
	MATERIALPARAM Material;
	Material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	Material.Specular = GetColorF(0.0f, 1.0f, 0.0f, 0.0f);
	Material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	Material.Emissive = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
	Material.Power = 20.0f;
	SetMaterialParam(Material);
}

/*
 *  更新
 */
void
CRandomGame::
Update(void)
{
	//m_Angle -= m_rotation_speed;

	m_Transform.RotateAround(CVector3(0.0f, 0.0f, 0.0f), CVector3(0.0f, 1.0f, 0.0f), 90);
}

/*
 *  描画
 */
void
CRandomGame::
Draw(void)
{
	Draw3DRot(m_Transform.position, 0,m_Angle,0);
}
// 回転描画
void CRandomGame::Draw3DRot(const CVector3& position, float _x_rot, float _y_rot, float _z_rot)
{

	DxLib::VERTEX3D vertices[] = {
		{VGet(-m_width / 2,	-m_height / 2,	0.0f), {0.0f, 0.0f, 1.0f}, DxLib::GetColorU8(255, 255, 255, 255), DxLib::GetColorU8(255, 255, 255, 255), 0.0f, 1.0f, 0.0f, 0.0f },
		{VGet(m_width / 2,	-m_height / 2,	0.0f), {0.0f, 0.0f, 1.0f}, DxLib::GetColorU8(255, 255, 255, 255), DxLib::GetColorU8(255, 255, 255, 255), 1.0f, 1.0f, 0.0f, 0.0f },
		{VGet(m_width / 2,	 m_height / 2,	0.0f), {0.0f, 0.0f, 1.0f}, DxLib::GetColorU8(255, 255, 255, 255), DxLib::GetColorU8(255, 255, 255, 255), 1.0f, 0.0f, 0.0f, 0.0f },
		{VGet(-m_width / 2,	 m_height / 2,	0.0f), {0.0f, 0.0f, 1.0f}, DxLib::GetColorU8(255, 255, 255, 255), DxLib::GetColorU8(255, 255, 255, 255), 0.0f, 0.0f, 0.0f, 0.0f },
	};

	unsigned short index[] = {0,1,3,3,1,2};

	//VECTOR m_pos[4] = {
	//	{-m_width / 2,	-m_height / 2,	0.0f},	// 左上頂点
	//	{m_width / 2,	-m_height / 2,	0.0f},	// 右上頂点
	//	{m_width / 2,	m_height / 2,	0.0f},	// 右下頂点
	//	{-m_width / 2,	m_height / 2,	0.0f},	// 左下頂点
	//};
	MATRIX transMat, rotMat, mulMat;

	CreateTranslationMatrix(&transMat, position.x, position.y, position.z);
	CreateRotationYXZMatrix(&rotMat, _x_rot, _y_rot, _z_rot);

	// 単位行列
	CreateIdentityMatrix(&mulMat);
	// 回転させる 
	CreateMultiplyMatrix(&mulMat, &mulMat, &rotMat);
	// 移動させる
	CreateMultiplyMatrix(&mulMat, &mulMat, &transMat);

	// 各頂点に行列を適用
	for (int i = 0; i < 4; i++)
	{
		VectorTransform(&vertices[i].pos, &vertices[i].pos, &mulMat);
	}

	//DrawModiGraphF(m_pos[0].x, m_pos[0].y, m_pos[1].x, m_pos[1].y, m_pos[2].x, m_pos[2].y, m_pos[3].x, m_pos[3].y, m_Handle, TRUE);

	DrawPolygonIndexed3D(vertices, 4, index, 2, m_Handle, TRUE);

}
/*
 *  解放
 */
void
CRandomGame::
Finalize(void)
{
    // 読み込んだ画像のグラフィックハンドルを削除
    DeleteGraph(m_Handle);
}
