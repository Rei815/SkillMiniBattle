#include "plane.h"

const unsigned short CPlane::m_index[] = { 0,1,3,3,1,2 };
CPlane::CPlane()
	: m_Transform()
	, m_FileName("None")
	, m_Handle(DX_NONE_GRAPH)
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

	if (m_Handle != VIVID_DX_ERROR)
	{
		DxLib::GetGraphSize(m_Handle, &m_Width, &m_Height);
	}
}

void CPlane::SetUp(const std::string fileName)
{
	m_FileName = fileName;
	vivid::LoadTexture(fileName);
	m_Handle = vivid::core::FindLoadedTexture(fileName);//DxLib::LoadGraph(fileName.c_str(), TRUE);
	SetUp();
}

void CPlane::Update()
{
	
	SetUp();
	SetVertices();
}

void CPlane::Draw()
{
	if(m_Handle != VIVID_DX_ERROR)
		DrawPolygonIndexed3D(m_Vertices, 4, m_index, 2, m_Handle, TRUE);
	else
		DrawPolygonIndexed3D(m_Vertices, 4, m_index, 2, DX_NONE_GRAPH, TRUE);

}

void CPlane::_Draw()
{
	CMatrix mat_trans = CMatrix::Translate(m_Transform.position);
	CMatrix mat_rot = CMatrix::Rotate(m_Transform.rotation);
	CMatrix mat_scale = CMatrix::Scale(m_Transform.scale);
	CMatrix m = mat_scale * mat_rot * mat_trans;

	Draw(m);
}

void CPlane::Draw(const CMatrix& mat)
{
	DxLib::VERTEX3D		vertices[4] = {};

	const float width_half = m_Width * .5f;
	const float height_half = m_Height * .5f;

	vertices[0].pos = CVector3(-width_half * m_Transform.scale.x, -height_half * m_Transform.scale.y, 0.0f) * mat;
	vertices[0].norm = m_Normal * DxLib::MGetRotElem(mat);
	vertices[0].u = 0.0f;
	vertices[0].v = 1.0f;
	vertices[0].dif = m_Color;
	vertices[0].spc = m_Color;

	vertices[1].pos = CVector3(width_half * m_Transform.scale.x, -height_half * m_Transform.scale.y, 0.0f) * mat;
	vertices[1].norm = vertices[0].norm;
	vertices[1].u = 1.0f;
	vertices[1].v = 1.0f;
	vertices[1].dif = m_Color;
	vertices[1].spc = m_Color;

	vertices[2].pos = CVector3(width_half * m_Transform.scale.x, height_half * m_Transform.scale.y, 0.0f) * mat;
	vertices[2].norm = vertices[0].norm;
	vertices[2].u = 1.0f;
	vertices[2].v = 0.0f;
	vertices[2].dif = m_Color;
	vertices[2].spc = m_Color;

	vertices[3].pos = CVector3(-width_half * m_Transform.scale.x, height_half * m_Transform.scale.y, 0.0f) * mat;
	vertices[3].norm = vertices[0].norm;
	vertices[3].u = 0.0f;
	vertices[3].v = 0.0f;
	vertices[3].dif = m_Color;
	vertices[3].spc = m_Color;

	DrawPolygonIndexed3D(vertices, 4, m_index, 2, m_Handle, TRUE);
}

void CPlane::Finalize()
{
}

void CPlane::SetTransform(const CTransform& transform)
{
	m_Transform = transform;
}

CTransform CPlane::GetTransform()
{
	return m_Transform;
}

CTransform* CPlane::GetTransformPointer()
{
	return &m_Transform;
}

CPlane::MATRICES CPlane::GetMatrices()
{
	return m_Matrices;
}

void CPlane::SetMatrix(const CMatrix& matrix)
{
	m_Matrices.m_MulMat = matrix;

}

void CPlane::SetScale(const CVector3& scale)
{
	m_Transform.scale = scale;
}

void CPlane::SetPosition(const CVector3& position)
{
	m_Transform.position = position;
	CreateTranslationMatrix(&m_Matrices.m_TransMat, m_Transform.position.x, m_Transform.position.y, m_Transform.position.z);

	// 移動させる
	m_Matrices.m_MulMat *= m_Matrices.m_TransMat;

}

void CPlane::SetRotation(const CVector3& rotation)
{
	m_Transform.rotation = rotation;
	CreateRotationYXZMatrix(&m_Matrices.m_RotMat, DEG_TO_RAD(m_Transform.rotation.x), DEG_TO_RAD(m_Transform.rotation.y), DEG_TO_RAD(m_Transform.rotation.z));
	// 単位行列
	m_Matrices.m_MulMat = CMatrix::GetIdentity(m_Matrices.m_MulMat);

	// 回転させる
	m_Matrices.m_MulMat *= m_Matrices.m_RotMat;

}

void CPlane::SetVertices()
{
	// 各頂点に行列を適用
	for (int i = 0; i < 4; i++)
		VectorTransform(&m_Vertices[i].pos, &m_Vertices[i].pos, &m_Matrices.m_MulMat);

}

void CPlane::SetVertices(const CMatrix& matrix)
{
	// 各頂点に行列を適用
	for (int i = 0; i < 4; i++)
		VectorTransform(&m_Vertices[i].pos, &m_Vertices[i].pos, &matrix);
}

void CPlane::Translation()
{
}


void CPlane::Rotation()
{
	CreateRotationYXZMatrix(&m_Matrices.m_RotMat, DEG_TO_RAD(m_Transform.rotation.x), DEG_TO_RAD(m_Transform.rotation.y), DEG_TO_RAD(m_Transform.rotation.z));

	// 単位行列
	m_Matrices.m_MulMat = CMatrix::GetIdentity(m_Matrices.m_MulMat);
	// 回転させる 
	m_Matrices.m_MulMat *= m_Matrices.m_RotMat;
	// 移動させる
	m_Matrices.m_MulMat *= m_Matrices.m_TransMat;
}