#include "fall_object.h"





CFallObject::CFallObject()
	: m_Model()
	, m_Transform()
	, m_FileName()
{
}

CFallObject::~CFallObject()
{
}

void CFallObject::Initialize(MARK_ID id)
{
	switch (id)
	{
	case MARK_ID::CIRCLE:	m_FileName = "circle";	break;
	case MARK_ID::STAR:		m_FileName = "star";	break;
	}
	m_Model.Initialize(m_FileName, CVector3());
}

void CFallObject::Update(void)
{
}

void CFallObject::Draw(void)
{
}

void CFallObject::Finalize(void)
{
}
