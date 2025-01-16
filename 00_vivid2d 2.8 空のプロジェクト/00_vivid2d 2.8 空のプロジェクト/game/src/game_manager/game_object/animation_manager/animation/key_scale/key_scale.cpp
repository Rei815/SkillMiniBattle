#include "key_scale.h"

const float CKeyScale::m_speed = 1.0f;
const vivid::Vector2 CKeyScale::m_min_scale = vivid::Vector2(0.5f,0.7f);
CKeyScale::CKeyScale()
{
}

CKeyScale::~CKeyScale()
{
}

void CKeyScale::Initialize(void* key_pointer)
{
	m_key = (CUI*)key_pointer;
}

void CKeyScale::Update()
{
	vivid::Vector2 scale = m_key->GetScale();
	scale.x -= m_speed;
	scale.y -= m_speed;
	if (scale.x <= m_min_scale.x || scale.y <= m_min_scale.y)
		scale = m_min_scale;
	m_key->SetScale(scale);
}

void CKeyScale::Finalize()
{
	m_key = nullptr;
}
