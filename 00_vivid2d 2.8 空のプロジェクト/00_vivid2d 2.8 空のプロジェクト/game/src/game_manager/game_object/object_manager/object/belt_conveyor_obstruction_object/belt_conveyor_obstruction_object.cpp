#include "belt_conveyor_obstruction_object.h"

const std::string CBeltConveyorObstructionObject::m_model_file_name_list[] =
{
	"data\\Models\\belt_conveyor_obstruction_1.mv1",
	"data\\Models\\belt_conveyor_obstruction_2.mv1",
	"data\\Models\\belt_conveyor_obstruction_3.mv1",
	"data\\Models\\belt_conveyor_obstruction_4.mv1",
	"data\\Models\\belt_conveyor_obstruction_5.mv1",
	"data\\Models\\belt_conveyor_obstruction_6.mv1"
};

CBeltConveyorObstructionObject::CBeltConveyorObstructionObject()
	: IObject()
	, m_NowObstructionID(OBSTRUCTION_ID::MAX)
{

}

CBeltConveyorObstructionObject::~CBeltConveyorObstructionObject()
{

}

void CBeltConveyorObstructionObject::Initialize(OBJECT_ID id, const CTransform& transform)
{
	m_NowObstructionID = (OBSTRUCTION_ID)(rand() % (int)OBSTRUCTION_ID::MAX);

	m_FileName = m_model_file_name_list[(int)m_NowObstructionID];

	IObject::Initialize(id, transform);

	m_Model.Initialize(m_FileName, m_Transform);
	m_Tag = "Floor";
}

void CBeltConveyorObstructionObject::Update(void)
{
	IObject::Update();

	m_Model.Update(m_Transform);
}

void CBeltConveyorObstructionObject::Draw(void)
{
	IObject::Draw();

	m_Model.Draw();
}

void CBeltConveyorObstructionObject::Finalize(void)
{
	IObject::Finalize();

	m_Model.Finalize();
}


void CBeltConveyorObstructionObject::SetObstructionType(OBSTRUCTION_ID id)
{
	if (m_NowObstructionID == id)
		return;

	m_FileName = m_model_file_name_list[(int)id];
	m_Model.Initialize(m_FileName, m_Transform);
}