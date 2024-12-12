#include "skill_barrier.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../bullet_manager/bullet_manager.h"

const float CSkillBarrier::m_barrier_exist_time = 5.0f;
const float CSkillBarrier::m_barrier_max_cool_time = 15.0f;
const float CSkillBarrier::m_barrier_min_cool_time = 5.0f;
const std::string CSkillBarrier::m_collider_model_file_name = "data\\Models\\skill_barrier_collider.mv1";

CSkillBarrier::CSkillBarrier(void)
	:CSkill(SKILL_CATEGORY::ACTIVE)
	, m_ColliderModel()
	, m_Effect(nullptr)
	, m_Timer(0)
	, m_NowCoolTime(0)
{

}

CSkillBarrier::~CSkillBarrier(void)
{

}

/*!
 *  @brief      初期化
 */
void
CSkillBarrier::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);

	m_State = SKILL_STATE::COOLDOWN;

	if (m_barrier_max_cool_time - m_barrier_min_cool_time > 0)
		m_NowCoolTime = m_barrier_min_cool_time + (float)(rand() % (int)((m_barrier_max_cool_time - m_barrier_min_cool_time) * 10)) / 10.0f;
	else
		m_NowCoolTime = m_barrier_min_cool_time;

	m_Timer.SetUp(m_NowCoolTime);
}

/*!
 *  @brief      更新
 */
void
CSkillBarrier::
Update(void)
{
	CSkill::Update();

	m_ColliderModel.Update(m_Player->GetPosition());
	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		break;

	case SKILL_STATE::ACTIVE:
		m_Timer.Update();
		m_GaugePercent = (m_barrier_exist_time - m_Timer.GetTimer()) / m_barrier_exist_time * 100.0f;
		if (m_Timer.Finished())
		{
			if (m_barrier_max_cool_time - m_barrier_min_cool_time > 0)
				m_NowCoolTime = m_barrier_min_cool_time + (float)(rand() % (int)((m_barrier_max_cool_time - m_barrier_min_cool_time) * 10)) / 10.0f;
			else
				m_NowCoolTime = m_barrier_min_cool_time;

			m_Timer.SetUp(m_NowCoolTime);
			
			if (m_Effect != nullptr)
			{
				m_Effect->SetActive(false);
				m_Effect = nullptr;
			}
			m_State = SKILL_STATE::COOLDOWN;
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

	case SKILL_STATE::COOLDOWN:
		m_Timer.Update();
		m_GaugePercent =  m_Timer.GetTimer() / m_NowCoolTime * 100.0f;
		if (m_Timer.Finished())
		{
			m_Timer.SetUp(m_barrier_exist_time);
			m_Player->StartInvincible(m_barrier_exist_time);
			m_Effect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_BARRIER, m_Player->GetPosition(),1.0f);
			m_State = SKILL_STATE::ACTIVE;
		}
		break;
	}
}

/*!
 *  @brief      描画
 */
void
CSkillBarrier::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      解放
 */
void
CSkillBarrier::
Finalize(void)
{
	CSkill::Finalize();

	m_ColliderModel.Finalize();
}

/*!
 *  @brief      プレイヤーのセット
 */
void CSkillBarrier::SetPlayer(CPlayer* player)
{
	CSkill::SetPlayer(player);

	m_ColliderModel.Initialize(m_collider_model_file_name, m_Player->GetPosition());
}

/*!
 *  @brief      アクション呼び出し
 */
void
CSkillBarrier::
Action(void)
{

}