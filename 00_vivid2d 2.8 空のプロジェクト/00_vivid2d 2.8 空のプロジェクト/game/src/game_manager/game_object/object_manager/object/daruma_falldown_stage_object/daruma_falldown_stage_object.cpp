#include "daruma_falldown_stage_object.h"

const std::string CDarumaFallDownStageObject::m_model_file_name = "data\\darumaStage.mv1";

CDarumaFallDownStageObject::CDarumaFallDownStageObject()
	: IObject()
{
}

CDarumaFallDownStageObject::~CDarumaFallDownStageObject()
{
}

void CDarumaFallDownStageObject::Initialize(OBJECT_ID id, const CTransform& transform)
{
	m_FileName = m_model_file_name;
	m_Tag = "Floor";
	IObject::Initialize(id, transform);

	m_Model.Initialize(m_FileName, m_Transform);
}

void CDarumaFallDownStageObject::Update(void)
{
	IObject::Update();
	m_Model.Update(m_Transform);
}

void CDarumaFallDownStageObject::Draw(void)
{
	IObject::Draw();

	m_Model.Draw();
}

void CDarumaFallDownStageObject::Finalize(void)
{
	IObject::Finalize();

	m_Model.Finalize();
}