
#include "vivid.h"
#include "model.h"
#include "..\..\unit_manager\unit\unit.h"
/*
* コンストラクタ
*/
CModel::CModel()
	: m_Transform()
 	, m_Handle(VIVID_DX_ERROR)
{
}

/*
* デストラクタ
*/
CModel::~CModel()
{
}

/*
* 初期化
*/
void CModel::Initialize(const std::string& file_name, const CVector3& position, float scale)
{
	Initialize(file_name, position, CVector3(scale, scale, scale));
}

void CModel::Initialize(const std::string& file_name, const CVector3& position, const CVector3& scale)
{
	CTransform TempTr;
	TempTr.position = position;
	Initialize(file_name, TempTr, scale);
}

void CModel::Initialize(const std::string& file_name, const CTransform& transform, float scale)
{
	Initialize(file_name, transform, CVector3(scale, scale, scale));
}

void CModel::Initialize(const std::string& file_name, const CTransform& transform, const CVector3& scale)
{
	m_Transform = transform;
	m_Transform.scale = scale;

	Load(file_name);

	//位置情報の更新
	MV1SetPosition(m_Handle, m_Transform.position);
	MV1SetScale(m_Handle, m_Transform.scale);
	MV1SetRotationXYZ(m_Handle, m_Transform.GetRadianRotation());
}


void CModel::Load(const std::string& file_name)
{
	//念のため、アンロードしてからロードする
	Unload();

	m_Handle = DxLib::MV1LoadModel(file_name.c_str());

	MV1SetupCollInfo(m_Handle, -1, 8, 8, 8);
}

void CModel::Unload(void)
{
	if (m_Handle == VIVID_DX_ERROR)return;

	DxLib::MV1DeleteModel(m_Handle);

	m_Handle = VIVID_DX_ERROR;
}

/*
* 更新
*/
void CModel::Update(void)
{
	Update(m_Transform);
}

void CModel::Update(const CTransform& transform)
{
	//エラー
	if (m_Handle == VIVID_DX_ERROR)
		return;

	m_Transform = transform;

	//位置情報の更新
	MV1SetPosition(m_Handle, m_Transform.position);
	MV1SetScale(m_Handle, m_Transform.scale);
	MV1SetRotationXYZ(m_Handle, m_Transform.GetRadianRotation());
	MV1RefreshCollInfo(m_Handle);
}

/*
* 描画
*/
void CModel::Draw()
{
	//エラー
	if (m_Handle == VIVID_DX_ERROR)
		return;

	//描画
	MV1DrawModel(m_Handle);

	// モデル全体の参照用メッシュを構築
	MV1SetupReferenceMesh(m_Handle, -1, TRUE);
}

/*
* 解放
*/
void CModel::Finalize()
{
	Unload();
}

int CModel::GetModelHandle() const
{
	return m_Handle;
}

void CModel::SetPosition(const CVector3& position)
{
	m_Transform.position = position;
}

void CModel::SetRotation(const CVector3& rotation)
{
	m_Transform.rotation == rotation;
}

void CModel::SetScale(float scale)
{
	SetScale(CVector3(scale, scale, scale));
}

void CModel::SetScale(const CVector3& scale)
{
	m_Transform.scale = scale;
}

bool CModel::CheckHitLine(const CVector3& startPos, const CVector3& endPos)
{
	MV1_COLL_RESULT_POLY hitPoly = MV1CollCheck_Line(m_Handle, -1, startPos, endPos);
	if (hitPoly.HitFlag == 1)
			return true;
	return false;
}

bool CModel::CheckHitTriangle(const CVector3& posA, const CVector3& posB, const CVector3& posC)
{
	MV1_COLL_RESULT_POLY_DIM hitPolyDim = MV1CollCheck_Triangle(m_Handle, -1, posA, posB, posC);
	if (hitPolyDim.HitNum > 0)
		return true;
	return false;
}

CVector3 CModel::GetHitLinePosition(const CVector3& startPos, const CVector3& endPos)
{
	MV1_COLL_RESULT_POLY hitPoly = MV1CollCheck_Line(m_Handle, -1, startPos, endPos);
	if (hitPoly.HitFlag == 1)
		return hitPoly.HitPosition;
	return endPos;
}

CVector3 CModel::GetHitTrianglePosition(const CVector3& posA, const CVector3& posB, const CVector3& posC)
{
	MV1_COLL_RESULT_POLY_DIM hitPolyDim = MV1CollCheck_Triangle(m_Handle, -1, posA, posB, posC);
	if (hitPolyDim.HitNum > 0)
		return hitPolyDim.Dim->HitPosition;
	return CVector3();
}

unsigned int CModel::GetMaterialDif(int material_index)
{
	COLOR_F difColor = MV1GetMaterialDifColor(m_Handle, material_index);

	unsigned int color = int(difColor.a * 255.0f) << 24 | int(difColor.r * 255.0f) << 16 | int(difColor.g * 255.0f) << 8 | int(difColor.b * 255.0f);

	return color;
}

void CModel::SetMaterialDif(int material_index, unsigned int color)
{
	COLOR_F difColor;
	difColor.a = ((color >> 24) & 0xff) / 255.0f;
	difColor.r = ((color >> 16) & 0xff) / 255.0f;
	difColor.g = ((color >> 8) & 0xff) / 255.0f;
	difColor.b = ((color) & 0xff) / 255.0f;
	MV1SetMaterialDifColor(m_Handle, material_index, difColor);
}

