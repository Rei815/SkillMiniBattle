#include "cannon_object.h"

const std::string CCannonObject::m_model_file_name =
"data\\Models\\cannon_test.mv1";

CCannonObject::CCannonObject()
	: IObject()
{
}

CCannonObject::~CCannonObject()
{
}

void CCannonObject::Initialize(OBJECT_ID id, const CTransform& transform)
{
	m_FileName = m_model_file_name;
	
	IObject::Initialize(id, transform);

	m_Model.Initialize(m_FileName, m_Transform);
}

void CCannonObject::Update(void)
{
	IObject::Update();
	m_Model.Update(m_Transform);
}

void CCannonObject::Draw(void)
{
	IObject::Draw();

	m_Model.Draw();
}

void CCannonObject::Finalize(void)
{
	IObject::Finalize();

	m_Model.Finalize();
}

bool CCannonObject::GetActive(void)
{
	return m_ActiveFlag;
}

void CCannonObject::SetActive(bool active)
{
	m_ActiveFlag = active;
}