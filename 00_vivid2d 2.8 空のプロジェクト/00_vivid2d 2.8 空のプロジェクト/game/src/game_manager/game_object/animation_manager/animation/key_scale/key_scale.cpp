#include "key_scale.h"

const float CKeyScale::m_speed = 0.08f;
const vivid::Vector2 CKeyScale::m_max_scale = vivid::Vector2(5.0f,5.0f);
CKeyScale::CKeyScale()
	: m_Key(nullptr)
	, m_MinScale()
{
}

CKeyScale::~CKeyScale()
{
}

void CKeyScale::Initialize()
{
	m_Key = std::make_unique<CUI>();
	
	if (!m_Key) return;
	m_MinScale = m_Key->GetScale();
	m_Key->SetScale(m_max_scale);
}

void CKeyScale::Update()
{
	if (!m_Key) return;

	vivid::Vector2 scale = m_Key->GetScale();
	scale.x -= m_speed;
	scale.y -= m_speed;
	if (scale.x <= m_MinScale.x || scale.y <= m_MinScale.y)
		scale = m_MinScale;
	m_Key->SetScale(scale);
}

void CKeyScale::Finalize()
{
	m_Key = nullptr;
}
