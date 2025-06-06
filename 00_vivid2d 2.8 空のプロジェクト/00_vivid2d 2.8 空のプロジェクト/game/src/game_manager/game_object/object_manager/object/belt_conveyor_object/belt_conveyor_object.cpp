#include "belt_conveyor_object.h"


const std::string CBeltConveyorObject::m_model_file_name = "data\\Models\\belt_conveyor_stage.mv1";


CBeltConveyorObject::CBeltConveyorObject()
	:IObject()
{

}


CBeltConveyorObject::~CBeltConveyorObject()
{

}

void CBeltConveyorObject::Initialize(OBJECT_ID id, const CTransform& transform)
{
	m_FileName = m_model_file_name;

	IObject::Initialize(id, transform);
	
	m_Model.Initialize(m_FileName, m_Transform);
	m_Tag = "Floor";
}

void CBeltConveyorObject::Update(void)
{
	IObject::Update();

	m_Model.Update(m_Transform);
}

void CBeltConveyorObject::Draw(void)
{
	IObject::Draw();

	m_Model.Draw();
}

void CBeltConveyorObject::Finalize(void)
{
	IObject::Finalize();

	m_Model.Finalize();
}