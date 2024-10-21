
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
void CModel::Initialize(const std::string& file_name, const CVector3& position)
{
	m_Transform.position = position;

	Load(file_name);

	//位置情報の更新
	MV1SetPosition(m_Handle, m_Transform.position);

}

void CModel::Initialize(const std::string& file_name, const CTransform& transform)
{
	m_Transform = transform;

	Load(file_name);

	//位置情報の更新
	MV1SetPosition(m_Handle, m_Transform.position);

	MV1SetRotationXYZ(m_Handle, m_Transform.GetRadianRotation());
}

void CModel::Load(const std::string& file_name)
{
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
void CModel::Update(const CTransform& transform)
{
	//エラー
	if (m_Handle == VIVID_DX_ERROR)
		return;

	m_Transform = transform;

	//位置情報の更新
	MV1SetPosition(m_Handle, m_Transform.position);

	MV1SetRotationXYZ(m_Handle, m_Transform.GetRadianRotation());
	MV1RefreshCollInfo(m_Handle, -1);
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

bool CModel::CheckHitLine(const CVector3& startPos, const CVector3& endPos)
{
	MV1_COLL_RESULT_POLY hitPoly = MV1CollCheck_Line(m_Handle, -1, startPos, endPos);
	if (hitPoly.HitFlag == 1)
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

