#include "skill_gravity_area.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../data_manager/data_manager.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../../../game/components/player_component/player_component.h"
#include "../../../../../engine/components/transform_component/transform_component.h"
#include "../../../object_manager/object_manager.h"
const float CSkillGravityArea::m_gravity_speed_down_rate = 0.7f;
const float CSkillGravityArea::m_gravity_jump_down_rate = 0.7f;
const float CSkillGravityArea::m_duration_time = 7.5f;
const float CSkillGravityArea::m_cool_time = 15.0f;
const float CSkillGravityArea::m_gravity_area_radius = 360.0f;
const float CSkillGravityArea::m_effect_scale = 2.0f;
const int   CSkillGravityArea::m_se_volume = 11000;

CSkillGravityArea::CSkillGravityArea(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, m_duration_time, m_cool_time)
	, m_Effect(nullptr)
	, m_SkillEffect(nullptr)
	, m_PlayerAffectedEffect{nullptr}
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

	for (int i = 0; i < (int)PLAYER_ID::NONE; i++)
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

	auto allPlayers = CObjectManager::GetInstance().GetObjectsWithComponent<PlayerComponent>();
	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		break;

	case SKILL_STATE::ACTIVE:

		for (auto& targetPlayerObject : allPlayers)
		{
			if (auto targetComp = targetPlayerObject->GetComponent<PlayerComponent>())
			{

				if (targetComp->GetPlayerID() == m_PlayerID)
					continue;

				int	index = (int)targetComp->GetPlayerID();
				auto targetTransform = targetPlayerObject->GetComponent<TransformComponent>();
				switch (m_PlayerAffectedGravity[index])
				{
				case GRAVITY_AFFECTED::NONE:
					if ((m_Player.lock()->GetComponent<TransformComponent>()->GetPosition() - targetTransform->GetPosition()).Length() < m_gravity_area_radius)
					{
						m_PlayerAffectedGravity[index] = GRAVITY_AFFECTED::AFFECTED;
						targetComp->MulMoveSpeedRate(m_gravity_speed_down_rate);
						targetComp->MulJumpPowerRate(m_gravity_jump_down_rate);

						//エフェクトの生成（仮置き、エフェクトが完成したらセットする）
						//if (false)
						m_PlayerAffectedEffect[index] = CEffectManager::GetInstance().Create(EFFECT_ID::DEBUFF, targetTransform->GetPosition(), CVector3(), 3.0f);
					}
					break;

				case GRAVITY_AFFECTED::AFFECTED:
					if (m_PlayerAffectedEffect[index] != nullptr)
						m_PlayerAffectedEffect[index]->SetPosition(targetTransform->GetPosition());

					if ((m_Player.lock()->GetComponent<TransformComponent>()->GetPosition() - targetTransform->GetPosition()).Length() > m_gravity_area_radius)
					{
						m_PlayerAffectedGravity[index] = GRAVITY_AFFECTED::NONE;
						targetComp->DivMoveSpeedRate(m_gravity_speed_down_rate);
						targetComp->DivJumpPowerRate(m_gravity_jump_down_rate);

						//エフェクトを消す
						if (m_PlayerAffectedEffect[index] != nullptr)
						{
							m_PlayerAffectedEffect[index]->Delete();
							m_PlayerAffectedEffect[index] = nullptr;
						}
					}
					break;
				}
			}
		}

		//エフェクトの位置調整
		if (m_Effect != nullptr)
		{
			m_Effect->SetPosition(m_Player.lock()->GetComponent<TransformComponent>()->GetPosition());
		}
		break;

	case SKILL_STATE::COOLDOWN:
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

	CSoundManager::GetInstance().Play_SE(SE_ID::GRAVITYAREA, false);
	CSoundManager::GetInstance().SetSEVolume(SE_ID::GRAVITYAREA, m_se_volume);
	//エフェクトの生成（仮置き、エフェクトが完成したらセットする）


	CVector3 effectPosition = m_Player.lock()->GetComponent<TransformComponent>()->GetPosition();
	effectPosition.y -= m_Player.lock()->GetComponent<PlayerComponent>()->GetHeight()/2;

	m_Effect = CEffectManager::GetInstance().Create(EFFECT_ID::GRAVITY_AREA, effectPosition,CVector3(),m_effect_scale);
	m_SkillEffect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_STAR, effectPosition, CVector3(), m_effect_scale);
	m_SkillEffect->SetParent(m_Player.lock());

	m_State = SKILL_STATE::ACTIVE;
}

/*!
 *  @brief      アクション終了
 */
void
CSkillGravityArea::
ActionEnd(void)
{
	//エフェクトを消す
	if (m_Effect != nullptr)
	{
		m_Effect->Delete();
		m_Effect = nullptr;
	}

	if (m_SkillEffect != nullptr)
	{
		m_SkillEffect->Delete();
		m_SkillEffect = nullptr;
	}

	std::shared_ptr<CGameObject> TempPlayer;
	auto allPlayers = CObjectManager::GetInstance().GetObjectsWithComponent<PlayerComponent>();
	//全てのプレイヤーに対して重力の影響を消す
	for (auto& targetPlayerObject : allPlayers)
	{
		if (auto targetComp = targetPlayerObject->GetComponent<PlayerComponent>())
		{
			int	index = (int)targetComp->GetPlayerID();
			if (auto targetComp = targetPlayerObject->GetComponent<PlayerComponent>())
			{
				if (targetComp->GetPlayerID() == m_PlayerID)
					continue;
				//重力の影響を消す
				if (m_PlayerAffectedGravity[index] == GRAVITY_AFFECTED::AFFECTED)
				{
					m_PlayerAffectedGravity[index] = GRAVITY_AFFECTED::NONE;
					targetComp->DivMoveSpeedRate(m_gravity_speed_down_rate);
					targetComp->DivJumpPowerRate(m_gravity_jump_down_rate);
				}

				//エフェクトを消す
				if (m_PlayerAffectedEffect[index] != nullptr)
				{
					m_PlayerAffectedEffect[index]->Delete();
					m_PlayerAffectedEffect[index] = nullptr;
				}
			}
		}
	}
	CSoundManager::GetInstance().Stop_SE(SE_ID::GRAVITYAREA);
}