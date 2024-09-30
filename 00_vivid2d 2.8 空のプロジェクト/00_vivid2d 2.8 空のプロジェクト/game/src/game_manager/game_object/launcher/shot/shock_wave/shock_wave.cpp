#include "shock_wave.h"
#include "../../../bullet_manager/bullet_manager.h"
const CShockWave::BulletParameters CShockWave::m_bullet_parameters =
//          �e��ID   ���ˑ��x  �U�����x ���U�� ���ː�       ���x     �u��       ���a     �U���� �U�����x������  ������
{ BULLET_ID::SHOCK_WAVE,        0,       10,     1,    1,      20.0f,      0,      45.0f,      1.0,             0,      0};  // �~��Ɍ���

CShockWave::CShockWave()
	: CShot(m_bullet_parameters)
{

}

CShockWave::~CShockWave()
{
}