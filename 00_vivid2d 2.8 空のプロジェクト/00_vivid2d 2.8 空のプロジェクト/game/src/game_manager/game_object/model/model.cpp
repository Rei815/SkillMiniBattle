
#include "vivid.h"
#include "model.h"
CModel::CModel(MODEL_ID id)
{
}
// コンストラクタ：ファイルパスを受け取り、Loadを呼ぶ
CModel::CModel(const std::string& file_name)
	: m_Handle(-1) // VIVID_DX_ERRORの定義がない場合、-1で初期化
{
	Load(file_name);
}
/*
 * デストラクタ
 */
CModel::~CModel()
{
}

int CModel::GetHandle() const
{
	return m_Handle;
}

void CModel::Load(const std::string& file_name)
{
	//念のため、アンロードしてからロードする
	Unload();

	m_Handle = DxLib::MV1LoadModel(file_name.c_str());

	// 当たり判定のセットアップ
	MV1SetupCollInfo(m_Handle, -1, 8, 8, 8);

	// ★★★ ここに移動 ★★★
	// モデル全体の参照用メッシュを構築
	DxLib::MV1SetupReferenceMesh(m_Handle, -1, TRUE);
}
void CModel::Unload(void)
{
	if (m_Handle == VIVID_DX_ERROR)return;

	DxLib::MV1DeleteModel(m_Handle);

	m_Handle = VIVID_DX_ERROR;
}

bool CModel::CheckHitLine(const CVector3& startPos, const CVector3& endPos)const
{
	MV1_COLL_RESULT_POLY hitPoly = MV1CollCheck_Line(m_Handle, -1, startPos, endPos);
	if (hitPoly.HitFlag == 1)
			return true;
	return false;
}

CVector3 CModel::GetHitLinePosition(const CVector3& startPos, const CVector3& endPos)const
{
	MV1_COLL_RESULT_POLY hitPoly = MV1CollCheck_Line(m_Handle, -1, startPos, endPos);
	if (hitPoly.HitFlag == 1)
		return hitPoly.HitPosition;
	return endPos;
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

