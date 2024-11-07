#include "plane.h"

const unsigned short CPlane::m_index[] = { 0,1,3,3,1,2 };
CPlane::CPlane()
	: m_Transform()
	, m_FileName("None")
	, m_Handle()
	, m_Color(DxLib::GetColorU8(255, 255, 255, 255))
	, m_Vertices()
{
}

CPlane::~CPlane()
{
}

void CPlane::SetUp()
{
	m_Vertices[0] = { VGet(-m_Transform.scale.x / 2,	-m_Transform.scale.y / 2,	0.0f) , {0.0f, 0.0f, 1.0f}, m_Color, m_Color, 0.0f, 1.0f, 0.0f, 0.0f };

	m_Vertices[1] = { VGet(m_Transform.scale.x / 2,	-m_Transform.scale.y / 2,	0.0f), {0.0f, 0.0f, 1.0f}, m_Color, m_Color, 1.0f, 1.0f, 0.0f, 0.0f };

	m_Vertices[2] = { VGet(m_Transform.scale.x / 2, m_Transform.scale.y / 2, 0.0f), { 0.0f, 0.0f, 1.0f }, m_Color, m_Color, 1.0f, 0.0f, 0.0f, 0.0f };

	m_Vertices[3] = { VGet(-m_Transform.scale.x / 2, m_Transform.scale.y / 2, 0.0f), { 0.0f, 0.0f, 1.0f }, m_Color, m_Color, 0.0f, 0.0f, 0.0f, 0.0f };
}

void CPlane::SetUp(const std::string fileName)
{
	m_FileName = fileName;
	m_Handle = DxLib::LoadGraph(fileName.c_str(), TRUE);
	SetUp();
}

void CPlane::Update()
{
	SetUp();
	CreateTranslationMatrix(&m_TransMat, m_Transform.position.x, m_Transform.position.y, m_Transform.position.z);
	CreateRotationYXZMatrix(&m_RotMat, m_Transform.rotation.x, m_Transform.rotation.y, m_Transform.rotation.z);

	// 単位行列
	m_MulMat = CMatrix::GetIdentity(m_MulMat);
	// 移動させる
	m_MulMat *= m_TransMat;
	// 回転させる 
	m_MulMat *= m_RotMat;
	// 各頂点に行列を適用
	for (int i = 0; i < 4; i++)
	{
		VectorTransform(&m_Vertices[i].pos, &m_Vertices[i].pos, &m_MulMat);
	}

}

void CPlane::Draw()
{
	if(m_Handle != VIVID_DX_ERROR)
		DrawPolygonIndexed3D(m_Vertices, 4, m_index, 2, m_Handle, TRUE);
	else
		DrawPolygonIndexed3D(m_Vertices, 4, m_index, 2, DX_NONE_GRAPH, TRUE);

}

void CPlane::Finalize()
{
}

void CPlane::SetScale(const CVector3& scale)
{
	m_Transform.scale = scale;
}

void CPlane::SetPosition(const CVector3& position)
{
	m_Transform.position = position;
}

void CPlane::SetRotation(const CVector3& rotation)
{
	m_Transform.rotation = rotation;
}

//void polygon::Draw3DRot(int handle, const CVector3& position, int width, int height, const CVector3& rot)
//{
//	DxLib::VERTEX3D vertices[] = {
//	{VGet(-width / 2,	-height / 2,	0.0f), {0.0f, 0.0f, 1.0f}, DxLib::GetColorU8(255, 255, 255, 255), DxLib::GetColorU8(255, 255, 255, 255), 0.0f, 1.0f, 0.0f, 0.0f },
//	{VGet(width / 2,	-height / 2,	0.0f), {0.0f, 0.0f, 1.0f}, DxLib::GetColorU8(255, 255, 255, 255), DxLib::GetColorU8(255, 255, 255, 255), 1.0f, 1.0f, 0.0f, 0.0f },
//	{VGet(width / 2,	 height / 2,	0.0f), {0.0f, 0.0f, 1.0f}, DxLib::GetColorU8(255, 255, 255, 255), DxLib::GetColorU8(255, 255, 255, 255), 1.0f, 0.0f, 0.0f, 0.0f },
//	{VGet(-width / 2,	 height / 2,	0.0f), {0.0f, 0.0f, 1.0f}, DxLib::GetColorU8(255, 255, 255, 255), DxLib::GetColorU8(255, 255, 255, 255), 0.0f, 0.0f, 0.0f, 0.0f },
//	};
//
//	unsigned short index[] = { 0,1,3,3,1,2 };
//
//	MATRIX transMat, rotMat, mulMat;
//
//	CreateTranslationMatrix(&transMat, position.x, position.y, position.z);
//	CreateRotationYXZMatrix(&rotMat, rot.x, rot.y, rot.z);
//
//	// 単位行列
//	CreateIdentityMatrix(&mulMat);
//	// 回転させる 
//	CreateMultiplyMatrix(&mulMat, &mulMat, &rotMat);
//	// 移動させる
//	CreateMultiplyMatrix(&mulMat, &mulMat, &transMat);
//
//	// 各頂点に行列を適用
//	for (int i = 0; i < 4; i++)
//	{
//		VectorTransform(&vertices[i].pos, &vertices[i].pos, &mulMat);
//	}
//
//	DrawPolygonIndexed3D(vertices, 4, index, 2, handle, TRUE);
//
//}