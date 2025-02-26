#include "cannon_object.h"

const std::string CCannonObject::m_model_file_name = "data\\Models\\cannon.mv1";
const float CCannonObject::m_scale = 1.0f;

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
	
	m_ColliderActiveFlag = false;
	IObject::Initialize(id, transform);

	m_Transform.scale = m_scale;
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