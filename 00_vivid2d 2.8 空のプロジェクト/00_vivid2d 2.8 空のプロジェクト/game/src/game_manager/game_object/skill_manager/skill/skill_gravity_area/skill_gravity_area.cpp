#include "skill_gravity_area.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../data_manager/data_manager.h"

const float CSkillGravityArea::m_gravity_speed_down_rate = 0.5f;
const float CSkillGravityArea::m_gravity_jump_down_rate = 0.5f;
const float CSkillGravityArea::m_gravity_time = 10.0f;
const float CSkillGravityArea::m_gravity_cool_time = 15.0f;
const float CSkillGravityArea::m_gravity_area_radius = 500.0f;

CSkillGravityArea::CSkillGravityArea(void)
	:CSkill(SKILL_CATEGORY::ACTIVE)
	, m_Effect(nullptr)
	, m_PlayerAffectedEffect{nullptr}
	, m_Timer()
{
}

CSkillGravityArea::~CSkillGravityArea(void)
{

}

/*!
 *  @brief      初期化
 */
void
CSkillGravityArea::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);

	m_State = SKILL_STATE::WAIT;

	m_Timer.SetUp(m_gravity_time);

	for (int i = 0; i < (int)UNIT_ID::NONE; i++)
	{
		m_PlayerAffectedGravity[i] = GRAVITY_AFFECTED::NONE;
	}
}

/*!
 *  @brief      更新
 */
void
CSkillGravityArea::
Update(void)
{
	CSkill::Update();

	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		break;

	case SKILL_STATE::ACTIVE:
		m_Timer.Update();
		m_GaugePercent = (m_gravity_time - m_Timer.GetTimer()) / m_gravity_time * 100.0f;

		//持続時間が終わったかどうか
		if (m_Timer.Finished())
		{
			m_Timer.SetUp(m_gravity_cool_time);
			m_State = SKILL_STATE::COOLDOWN;

			//エフェクトを消す
			if (m_Effect != nullptr)
			{
				m_Effect->SetActive(false);
				m_Effect = nullptr;
			}

			CPlayer* TempPlayer;
			for (int i = 0; i < (int)UNIT_ID::NONE; i++)
			{
				//重力の影響を消す
				if (m_PlayerAffectedGravity[i] == GRAVITY_AFFECTED::AFFECTED)
				{
					m_PlayerAffectedGravity[i] = GRAVITY_AFFECTED::NONE;
					TempPlayer = CUnitManager::GetInstance().GetPlayer((UNIT_ID)i);
					TempPlayer->DivMoveSpeedRate(m_gravity_speed_down_rate);
					TempPlayer->DivJumpPowerRate(m_gravity_jump_down_rate);
				}

				//エフェクトを消す
				if (m_PlayerAffectedEffect[i] != nullptr)
				{
					m_PlayerAffectedEffect[i]->SetActive(false);
					m_PlayerAffectedEffect[i] = nullptr;
				}
			}
		}
		else
		{
			for (int i = 0; i < (int)UNIT_ID::NONE; i++)
			{
				if (i >= CDataManager::GetInstance().GetCurrentPlayer())
					break;

				if ((UNIT_ID)i == m_PlayerID)
					continue;
				
				CPlayer* TempPlayer = CUnitManager::GetInstance().GetPlayer((UNIT_ID)i);

				if (TempPlayer == nullptr)
					continue;

				switch (m_PlayerAffectedGravity[i])
				{
				case GRAVITY_AFFECTED::NONE:
					if ((m_Player->GetPosition() - TempPlayer->GetPosition()).Length() < m_gravity_area_radius)
					{
						m_PlayerAffectedGravity[i] = GRAVITY_AFFECTED::AFFECTED;
						TempPlayer->MulMoveSpeedRate(m_gravity_speed_down_rate);
						TempPlayer->MulJumpPowerRate(m_gravity_jump_down_rate);

						//エフェクトの生成（仮置き、エフェクトが完成したらセットする）
						if (false)
							m_PlayerAffectedEffect[i] = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_BARRIER, m_Player->GetPosition(), 1.0f);
					}
					break;

				case GRAVITY_AFFECTED::AFFECTED:
					if (m_PlayerAffectedEffect[i] != nullptr)
						m_PlayerAffectedEffect[i]->SetPosition(TempPlayer->GetPosition());

					if ((m_Player->GetPosition() - TempPlayer->GetPosition()).Length() > m_gravity_area_radius)
					{
						m_PlayerAffectedGravity[i] = GRAVITY_AFFECTED::NONE;
						TempPlayer->DivMoveSpeedRate(m_gravity_speed_down_rate);
						TempPlayer->DivJumpPowerRate(m_gravity_jump_down_rate);

						//エフェクトを消す
						if (m_PlayerAffectedEffect[i] != nullptr)
						{
							m_PlayerAffectedEffect[i]->SetActive(false);
							m_PlayerAffectedEffect[i] = nullptr;
						}
					}
					break;
				}
			}
		}

		//エフェクトの位置調整
		if (m_Effect != nullptr)
		{
			m_Effect->SetPosition(m_Player->GetPosition());
		}
		break;

	case SKILL_STATE::COOLDOWN:
		m_Timer.Update();
		m_GaugePercent = m_Timer.GetTimer() / m_gravity_cool_time * 100.0f;
		if (m_Timer.Finished())
		{
			m_Timer.SetUp(m_gravity_time);
			m_State = SKILL_STATE::WAIT;
		}
		break;
	}
}

/*!
 *  @brief      描画
 */
void
CSkillGravityArea::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      解放
 */
void
CSkillGravityArea::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      アクション呼び出し
 */
void
CSkillGravityArea::
Action(void)
{
	if (m_State != SKILL_STATE::WAIT)
		return;

	//エフェクトの生成（仮置き、エフェクトが完成したらセットする）
	if (false)
		m_Effect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_BARRIER, m_Player->GetPosition(), 1.0f);

	m_Timer.SetUp(m_gravity_time);
	m_State = SKILL_STATE::ACTIVE;
}