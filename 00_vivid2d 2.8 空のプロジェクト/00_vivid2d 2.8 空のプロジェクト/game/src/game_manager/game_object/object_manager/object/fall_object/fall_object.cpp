#include "fall_object.h"
#include "..\..\..\ui_manager\ui_manager.h"
const	std::string		CFallObject::m_file_name_list[] = {
	"data\\Textures\\fall_out_circle.png",
	"data\\Textures\\fall_out_cross.png",
	"data\\Textures\\fall_out_moon.png",
	"data\\Textures\\fall_out_square.png",
	"data\\Textures\\fall_out_sun.png",
	"data\\Textures\\fall_out_triangle.png",
};


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
	m_Model.Initialize("data\\fallout_floor.mv1", m_Transform);
	vivid::LoadTexture(m_FileName);
	int grHandle = vivid::core::FindLoadedTexture(m_FileName);
	MV1SetTextureGraphHandle(m_Model.GetModelHandle(), 0, grHandle, true);
	unsigned int color = m_Model.GetMaterialDif(0);
	color = (color & 0x00ffffff) | (100 & 0xff) << 24;
	m_Model.SetMaterialDif(0, color);
	m_Tag = "Floor";

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

MARK_ID CFallObject::GetID(void)
{
	return m_MarkID;
}