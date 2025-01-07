#include "stomp.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../../effect_manager/effect_manager.h"

const float CStomp::m_floating_time = 3.0f;

CStomp::CStomp(void)
	:CSkill()
{

}

CStomp::~CStomp(void)
{

}

/*!
 *  @brief      ������
 */
void
CStomp::
Initialize(CPlayer* player)
{
	CSkill::Initialize(player);
}

/*!
 *  @brief      �X�V
 */
void
CStomp::
Update(void)
{
	CSkill::Update();
	if (m_Timer.Finished())
	{
		m_Timer.Reset();
	}
}

/*!
 *  @brief      �`��
 */
void
CStomp::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      ���
 */
void
CStomp::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      �A�N�V�����Ăяo��
 */
void
CStomp::
Action(UNIT_CATEGORY category)
{
	CBulletManager::GetInstance().Create(m_Player->GetUnitCategory(), BULLET_ID::SHOCK_WAVE, m_Player->GetPosition(), CVector3::UP);
	CEffectManager::GetInstance().Create(EFFECT_ID::SHOCK_WAVE, m_Player->GetPosition());
}