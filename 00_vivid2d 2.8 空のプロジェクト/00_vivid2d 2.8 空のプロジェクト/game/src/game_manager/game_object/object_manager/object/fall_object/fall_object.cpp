#include "fall_object.h"
#include "..\..\..\ui_manager\ui_manager.h"
const	std::string		CFallObject::m_file_name_list[] = {"data\\fallout_floor_circle.mv1","data\\fallout_floor_cross.mv1" ,"data\\fallout_floor_moon.mv1" ,
"data\\fallout_floor_square.mv1" ,"data\\fallout_floor_sun.mv1" ,"data\\fallout_floor_triangle.mv1" };


CFallObject::CFallObject()
	: IObject()
	, m_MarkID()
{
}

CFallObject::~CFallObject()
{
}

void CFallObject::Initialize(OBJECT_ID id, const CTransform& transform)
{
	m_Transform = transform;
	IObject::Initialize(id, m_Transform);

	switch (id)
	{
	case OBJECT_ID::CIRCLE_FALL_OBJECT:		m_MarkID = MARK_ID::CIRCLE;		m_Transform.rotation.y = 30;	break;
	case OBJECT_ID::CROSS_FALL_OBJECT:		m_MarkID = MARK_ID::CROSS;		m_Transform.rotation.y = 30;	break;
	case OBJECT_ID::MOON_FALL_OBJECT:		m_MarkID = MARK_ID::MOON;		m_Transform.rotation.y = 90;	break;
	case OBJECT_ID::SQUARE_FALL_OBJECT:		m_MarkID = MARK_ID::SQUARE;		m_Transform.rotation.y = -30;	break;
	case OBJECT_ID::SUN_FALL_OBJECT:		m_MarkID = MARK_ID::SUN;		m_Transform.rotation.y = 90;	break;
	case OBJECT_ID::TRIANGLE_FALL_OBJECT:	m_MarkID = MARK_ID::TRIANGLE;	m_Transform.rotation.y = -30;	break;
	}
	m_FileName = m_file_name_list[static_cast<int>(m_MarkID)];
	m_Model.Initialize(m_FileName, m_Transform);
	m_Tag = "Floor";
	MV1SetMeshBackCulling(m_Model.GetModelHandle(), 0, TRUE);

}

void CFallObject::Update(void)
{

	IObject::Update();
	m_Model.Update(m_Transform);
}

void CFallObject::Draw(void)
{
	IObject::Draw();

	m_Model.Draw();

}

void CFallObject::Finalize(void)
{
	IObject::Finalize();

	m_Model.Finalize();
}

bool CFallObject::GetActive(void)
{
	return m_ActiveFlag;
}

void CFallObject::SetActive(bool active)
{
	m_ActiveFlag = active;
}

MARK_ID CFallObject::GetID(void)
{
	return m_MarkID;
}