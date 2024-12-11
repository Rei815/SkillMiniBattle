#include "skill_barrier.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../bullet_manager/bullet_manager.h"

const float CSkillBarrier::m_barrier_exist_time = 3000.0f;
const float CSkillBarrier::m_barrier_max_cool_time = 17.0f;
const float CSkillBarrier::m_barrier_min_cool_time = 7.0f;
const std::string CSkillBarrier::m_collider_model_file_name = "data\\Models\\skill_barrier_collider.mv1";

CSkillBarrier::CSkillBarrier(void)
	:CSkill(SKILL_CATEGORY::ACTIVE)
	, m_ColliderModel()
	, m_Effect(nullptr)
	, m_NowBarrierState(BARRIER_STATE::IS_COOL_TIME)
	, m_Timer(0)
{

}

CSkillBarrier::~CSkillBarrier(void)
{

}

/*!
 *  @brief      ������
 */
void
CSkillBarrier::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);

	m_ColliderModel.Initialize(m_collider_model_file_name, m_Player->GetPosition());
	m_NowBarrierState = BARRIER_STATE::IS_COOL_TIME;

	if (m_barrier_max_cool_time - m_barrier_min_cool_time > 0)
		m_Timer.SetUp(m_barrier_min_cool_time + (float)(rand() % (int)((m_barrier_max_cool_time - m_barrier_min_cool_time) * 10)) / 10.0f);
	else
		m_Timer.SetUp(m_barrier_min_cool_time);
}

/*!
 *  @brief      �X�V
 */
void
CSkillBarrier::
Update(void)
{
	CSkill::Update();

	m_ColliderModel.Update(m_Player->GetPosition());
	m_Timer.Update();

	switch (m_NowBarrierState)
	{
	case CSkillBarrier::BARRIER_STATE::BARRIER:
		if (m_Timer.Finished())
		{
			if (m_barrier_max_cool_time - m_barrier_min_cool_time > 0)
				m_Timer.SetUp(m_barrier_min_cool_time + (float)(rand() % (int)((m_barrier_max_cool_time - m_barrier_min_cool_time) * 10)) / 10.0f);
			else
				m_Timer.SetUp(m_barrier_min_cool_time);
			
			if (m_Effect != nullptr)
			{
				m_Effect->SetActive(false);
				m_Effect = nullptr;
			}
			m_NowBarrierState = BARRIER_STATE::IS_COOL_TIME;
		}
		else
		{
			if (m_Effect != nullptr)
			{
				m_Effect->SetPosition(m_Player->GetPosition());
				CBulletManager::GetInstance().CheckReflectModel(m_ColliderModel);
			}
		}
		break;

	case CSkillBarrier::BARRIER_STATE::IS_COOL_TIME:
		if (m_Timer.Finished())
		{
			m_Timer.SetUp(m_barrier_exist_time);
			m_Player->StartInvincible(m_barrier_exist_time);
			m_Effect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_BARRIER, m_Player->GetPosition(),1.0f);
			m_NowBarrierState = BARRIER_STATE::BARRIER;
		}
		break;
	}
}

/*!
 *  @brief      �`��
 */
void
CSkillBarrier::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      ���
 */
void
CSkillBarrier::
Finalize(void)
{
	CSkill::Finalize();

	m_ColliderModel.Finalize();
}


/*!
 *  @brief      �A�N�V�����Ăяo��
 */
void
CSkillBarrier::
Action(void)
{

}