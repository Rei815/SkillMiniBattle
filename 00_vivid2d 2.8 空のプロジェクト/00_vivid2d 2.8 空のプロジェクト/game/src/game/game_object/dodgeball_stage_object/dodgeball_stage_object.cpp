#include "dodgeball_stage_object.h"

const std::string CDogeballStageObject::m_model_file_name = "data\\Models\\dodgeball_stage.mv1";

CDogeballStageObject::CDogeballStageObject()
	: IObject()
{
}

CDogeballStageObject::~CDogeballStageObject()
{
}

void CDogeballStageObject::Initialize(OBJECT_ID id, const CTransform& transform)
{
	m_FileName = m_model_file_name;

	IObject::Initialize(id, transform);

	m_Model.Initialize(m_FileName, m_Transform);
	m_Tag = "Floor";

}

void CDogeballStageObject::Update(void)
{
	IObject::Update();

	m_Model.Update(m_Transform);
}

void CDogeballStageObject::Draw(void)
{
	IObject::Draw();

	m_Model.Draw();
}

void CDogeballStageObject::Finalize(void)
{
	IObject::Finalize();

	m_Model.Finalize();
}