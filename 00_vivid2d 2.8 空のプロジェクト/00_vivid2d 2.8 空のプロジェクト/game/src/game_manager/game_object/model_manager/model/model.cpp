
#include "vivid.h"
#include "model.h"
#include "..\..\unit_manager\unit\unit.h"
/*
* �R���X�g���N�^
*/
CModel::CModel()
	: m_Transform()
 	, m_Handle(VIVID_DX_ERROR)
{
}

/*
* �f�X�g���N�^
*/
CModel::~CModel()
{
}

/*
* ������
*/
void CModel::Initialize(const std::string& file_name, const CVector3& position)
{
	m_Transform.position = position;

	Load(file_name);

	//�ʒu���̍X�V
	MV1SetPosition(m_Handle, m_Transform.position);

}

void CModel::Initialize(const std::string& file_name, const CTransform& transform)
{
	m_Transform = transform;

	Load(file_name);

	//�ʒu���̍X�V
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
* �X�V
*/
void CModel::Update(const CTransform& transform)
{
	//�G���[
	if (m_Handle == VIVID_DX_ERROR)
		return;

	m_Transform = transform;

	//�ʒu���̍X�V
	MV1SetPosition(m_Handle, m_Transform.position);
	MV1SetScale(m_Handle, m_Transform.scale);
	MV1SetRotationXYZ(m_Handle, m_Transform.GetRadianRotation());
	MV1RefreshCollInfo(m_Handle, -1);
}

/*
* �`��
*/
void CModel::Draw()
{
	//�G���[
	if (m_Handle == VIVID_DX_ERROR)
		return;

	//�`��
	MV1DrawModel(m_Handle);

	// ���f���S�̂̎Q�Ɨp���b�V�����\�z
	MV1SetupReferenceMesh(m_Handle, -1, TRUE);
}

/*
* ���
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

