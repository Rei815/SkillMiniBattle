#include "plane.h"

const unsigned short CPlane::m_index[] = { 0,1,3,3,1,2 };
CPlane::CPlane()
	: m_Transform()
	, m_Handle(DX_NONE_GRAPH)
	, m_Color(DxLib::GetColorU8(255, 255, 255, 255))
	, m_Normal()
{
}

CPlane::~CPlane()
{
}

void CPlane::SetUp(const std::string fileName)
{
	vivid::LoadTexture(fileName);
	m_Handle = vivid::core::FindLoadedTexture(fileName);

	if (m_Handle != VIVID_DX_ERROR)
	{
		//幅、高さを取得して変数に入る
		DxLib::GetGraphSize(m_Handle, &m_Width, &m_Height);
	}
}

void CPlane::_Draw()
{
	//トランスフォーム内の情報から行列を作る
	CMatrix mat_trans = CMatrix::Translate(m_Transform.position);
	CMatrix mat_rot = CMatrix::Rotate(m_Transform.rotation);
	CMatrix mat_scale = CMatrix::Scale(m_Transform.scale);
	CMatrix m = mat_scale * mat_rot * mat_trans;

	Draw(m);
}

void CPlane::Draw(const CMatrix& mat)
{
	//行列から頂点座標を計算
	DxLib::VERTEX3D		vertices[4] = {};

	const float width_half = m_Width * .5f;
	const float height_half = m_Height * .5f;

	//左上、右上、左下、右下の順番
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