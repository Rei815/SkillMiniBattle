#include "key_scale.h"

const float CKeyScale::m_speed = 0.08f;
const vivid::Vector2 CKeyScale::m_min_scale = vivid::Vector2(0.5f,0.5f);
const vivid::Vector2 CKeyScale::m_max_scale = vivid::Vector2(5.0f,5.0f);
CKeyScale::CKeyScale()
{
}

CKeyScale::~CKeyScale()
{
}

void CKeyScale::Initialize(void* key_pointer)
{
	m_key = (CUI*)key_pointer;
	if (!m_key) return;
	m_key->SetScale(m_max_scale);
}

void CKeyScale::Update()
{
	if (!m_key) return;

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
