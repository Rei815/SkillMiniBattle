
#include "vivid.h"
#include "model.h"
#include "..\model_manager\model_manager.h"
CModel::CModel(MODEL_ID id)
	: m_Handle(-1) // VIVID_DX_ERROR�̒�`���Ȃ��ꍇ�A-1�ŏ�����
{
	Load(CModelManager::GetInstance().GetModelFilePath(id));
}
/*
 * �f�X�g���N�^
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
	//�O�̂��߁A�A�����[�h���Ă��烍�[�h����
	Unload();

	m_Handle = DxLib::MV1LoadModel(file_name.c_str());

	// �����蔻��̃Z�b�g�A�b�v
	MV1SetupCollInfo(m_Handle, -1, 8, 8, 8);

	// ������ �����Ɉړ� ������
	// ���f���S�̂̎Q�Ɨp���b�V�����\�z
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

