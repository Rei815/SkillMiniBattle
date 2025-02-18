#include "light.h"

const float CLight::m_max_atten2 = 1.0f;
CLight::CLight()
	: m_Transform()
	, m_Direction()
	, m_Color()
	, m_Intensity()
	, m_LightType(LIGHT_TYPE::DIRECTIONAL)
	, m_Handle(VIVID_DX_ERROR)
	, m_OutAngle(DEG_TO_RAD(45))
	, m_InAngle(DEG_TO_RAD(30))
	, m_Range(200.0f)
	, m_Atten0(0.0f)
	, m_Atten1(0.002f)
	, m_Atten2(0.0f)
{
}

CLight::~CLight()
{
}

void CLight::Initialize(const CTransform& transform, const CVector3& direction, const COLOR_F& color, float intensity, LIGHT_TYPE light_type)
{
	m_Transform = transform;
	m_Direction = direction;
	m_Color = color;
	m_Intensity = intensity;
	m_LightType = light_type;
	switch (m_LightType)
	{
	case CLight::LIGHT_TYPE::DIRECTIONAL:
		m_Handle = CreateDirLightHandle(m_Direction);
		break;
	case CLight::LIGHT_TYPE::SPOT:
		m_Handle = CreateSpotLightHandle(m_Transform.position, m_Direction, m_OutAngle, m_InAngle, m_Range, m_Atten0, m_Atten1, m_Atten2);
		break;
	case CLight::LIGHT_TYPE::POINT:
		m_Handle = CreatePointLightHandle(m_Transform.position, m_Range, 0.0f, 0.002f, 0.0f);
		break;
	}
	SetLightDifColorHandle(m_Handle, m_Color);
	SetLightSpcColorHandle(m_Handle, m_Color);
	SetLightAmbColorHandle(m_Handle, m_Color);
}

void CLight::Update()
{
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::T))
	{
		m_Direction.x += 0.1f;
		if (m_Direction.x >= 1.0f)
			m_Direction.x = 1.0f;
	}
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::Y))
	{
		m_Direction.x -= 0.1f;
		if (m_Direction.x <= -1.0f)
			m_Direction.x = -1.0f;

	}

	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::U))
	{
		m_Transform.position.y += 1.0f;
	}
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::I))
	{
		m_Transform.position.y -= 1.0f;
	}
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::O))
	{
		m_Direction.z += 0.01f;
	}
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::P))
	{
		m_Direction.z -= 0.01f;
	}
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::H))
	{
		m_OutAngle += DEG_TO_RAD(5);
	}
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::J))
	{
		m_OutAngle -= DEG_TO_RAD(5);
	}
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::K))
	{
		m_InAngle += DEG_TO_RAD(5);
	}
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::L))
	{
		m_InAngle -= DEG_TO_RAD(5);
	}
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::N))
	{
		m_Range += 100.0f;
	}
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::M))
	{
		if (m_Range < 0)
			m_Range = 0;
		m_Range -= 100.0f;
	}
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::C))
	{
		m_Atten0 += 0.0001f;
	}
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::V))
	{
		m_Atten1 -= 0.0001f;
		if (m_Atten1 < 0)
			m_Atten1 = 0;

	}
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::B))
	{
		m_Atten2 += 0.000001f;
		if (m_Atten2 >= m_max_atten2)
			m_Atten2 = m_max_atten2;
	}
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::D))
	{
		m_Atten0 -= 0.0001f;
		if (m_Atten0 < 0)
			m_Atten0 = 0;

	}
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::F))
	{
		m_Atten1 += 0.0001f;
	}
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::G))
	{
		m_Atten2 -= 0.000001f;
		if (m_Atten2 < 0)
			m_Atten2 = 0;
	}

	switch (m_LightType)
	{
	case CLight::LIGHT_TYPE::DIRECTIONAL:
		break;
	case CLight::LIGHT_TYPE::SPOT:
		SetLightDirectionHandle(m_Handle, m_Direction);
		SetLightAngleHandle(m_Handle, m_OutAngle, m_InAngle);
		SetLightRangeAttenHandle(m_Handle, m_Range, m_Atten0, m_Atten1, m_Atten2);
		break;
	case CLight::LIGHT_TYPE::POINT:
		break;
	}
	SetLightPositionHandle(m_Handle,m_Transform.position);

}

void CLight::Draw()
{
	// ‚R‚c‹óŠÔã‚É‹…‚ð•`‰æ‚·‚é
	//DrawSphere3D(m_Transform.position, 80.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
}

void CLight::Finalize()
{
}

void CLight::SetDirection(const CVector3& direction)
{
	m_Direction = direction;
}

void CLight::SetRange(float range)
{
	m_Range = range;
}
