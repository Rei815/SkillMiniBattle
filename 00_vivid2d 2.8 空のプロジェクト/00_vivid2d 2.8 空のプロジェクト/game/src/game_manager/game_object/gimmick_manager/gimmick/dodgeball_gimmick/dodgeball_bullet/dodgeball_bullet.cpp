#include "dodgeball_bullet.h"

const std::string CDodgeBallBullet::m_file_name = "data\\Models\\Bullet.mv1";

CDodgeBallBullet::CDodgeBallBullet()
	: m_Model()
	, m_Transform()
{
}

CDodgeBallBullet::~CDodgeBallBullet()
{
}

void CDodgeBallBullet::Initialize()
{
	m_Model.Initialize(m_file_name, CVector3());
}

void CDodgeBallBullet::Update(void)
{
}

void CDodgeBallBullet::Draw(void)
{
}

void CDodgeBallBullet::Finalize(void)
{
}
