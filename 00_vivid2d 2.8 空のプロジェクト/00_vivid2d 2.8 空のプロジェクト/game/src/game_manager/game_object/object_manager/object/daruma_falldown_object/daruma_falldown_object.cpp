#include "daruma_falldown_object.h"

const	float			CDaruma_FallDownObject::m_remove_height = -500.0f;
const	float			CDaruma_FallDownObject::m_start_height = -100.0f;
const	float			CDaruma_FallDownObject::m_invisible_alpha = 0.0f;
const	std::string		CDaruma_FallDownObject::m_file_name_list[] = { "data\\circle.mv1","data\\cross.mv1" ,"data\\moon.mv1" ,
"data\\square.mv1" ,"data\\sun.mv1" ,"data\\triangle.mv1" };


CDaruma_FallDownObject::CDaruma_FallDownObject()
	: IObject()
	, m_FallSpeed()
	, m_Daruma_FallDownObjectState()
{
}

CDaruma_FallDownObject::~CDaruma_FallDownObject()
{
}

void CDaruma_FallDownObject::Initialize(OBJECT_ID id, const CTransform& transform)
{
	IObject::Initialize(id, transform);

	
	m_Transform = transform;
	m_Model.Initialize(m_FileName, m_Transform.position);
	m_Timer.SetUp(1.0f);
	m_State = OBJECT_STATE::WAIT;

}

void CDaruma_FallDownObject::Update(void)
{
	IObject::Update();
	m_Model.Update(m_Transform);
	if (m_Transform.position.y <= m_remove_height)
	{
		m_Transform.position.y = m_remove_height;
		m_Alpha = m_invisible_alpha;
	}
	if (m_Alpha == m_invisible_alpha)
	{
		m_State = OBJECT_STATE::FALL_FINISH;
		m_Timer.Update();
	}

	if (m_Timer.Finished())
	{
		m_Timer.Reset();
		m_Transform.position.y = m_start_height;
		m_Alpha = m_limit_alpha;
		m_Velocity = CVector3::ZERO;
		m_State = OBJECT_STATE::WAIT;
	}
}

void CDaruma_FallDownObject::Draw(void)
{
	IObject::Draw();

	m_Model.Draw();

}

void CDaruma_FallDownObject::Finalize(void)
{
	IObject::Finalize();

	m_Model.Finalize();
}

bool CDaruma_FallDownObject::GetActive(void)
{
	return m_ActiveFlag;
}

void CDaruma_FallDownObject::SetActive(bool active)
{
	m_ActiveFlag = active;
}