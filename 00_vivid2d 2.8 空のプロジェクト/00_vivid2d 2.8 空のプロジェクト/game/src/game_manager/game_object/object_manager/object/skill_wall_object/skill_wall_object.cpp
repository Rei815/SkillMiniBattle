#include "skill_wall_object.h"

const std::string CSkillWallObject::m_model_file_name = "data\\Models\\skill_wall.mv1";

CSkillWallObject::CSkillWallObject()
	: IObject()
{
}

CSkillWallObject::~CSkillWallObject()
{
}

void CSkillWallObject::Initialize(OBJECT_ID id, const CTransform& transform)
{
	m_FileName = m_model_file_name;

	IObject::Initialize(id, transform);

	m_Model.Initialize(m_FileName, m_Transform);
	m_Tag = "Floor";

}

void CSkillWallObject::Update(void)
{
	IObject::Update();

	m_Model.Update(m_Transform);
}

void CSkillWallObject::Draw(void)
{
	IObject::Draw();

	m_Model.Draw();
}

void CSkillWallObject::Finalize(void)
{
	IObject::Finalize();

	m_Model.Finalize();
}

bool CSkillWallObject::GetActive(void)
{
	return m_ActiveFlag;
}

void CSkillWallObject::SetActive(bool active)
{
	m_ActiveFlag = active;
}