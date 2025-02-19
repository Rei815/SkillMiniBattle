#include "maze_stage.h"

const std::string CMazeStage::m_file_name = "data\\Floor.mv1";

CMazeStage::CMazeStage()
	: IObject()
{
}

CMazeStage::~CMazeStage()
{
}

void CMazeStage::Initialize(OBJECT_ID id, const CTransform& transform)
{
	m_FileName = m_file_name;

	IObject::Initialize(id, transform);

	m_Model.Initialize(m_FileName, m_Transform);
	m_Tag = "Floor";

}

void CMazeStage::Update(void)
{
	IObject::Update();

	m_Model.Update(m_Transform);
}

void CMazeStage::Draw(void)
{
	IObject::Draw();

	m_Model.Draw();
}

void CMazeStage::Finalize(void)
{
	IObject::Finalize();

	m_Model.Finalize();
}
