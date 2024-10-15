#include "daruma_falldown_object.h"

CDaruma_FallDownObject::CDaruma_FallDownObject()
	: m_Model()
	, m_Transform()
	, m_FileName()
{
}

CDaruma_FallDownObject::~CDaruma_FallDownObject()
{
}

void CDaruma_FallDownObject::Initialize(void)
{
	m_Model.Initialize(m_FileName, CVector3());
}

void 




CDaruma_FallDownObject::Update(void)
{
}

void CDaruma_FallDownObject::Draw(void)
{
}

void CDaruma_FallDownObject::Finalize(void)
{
}
