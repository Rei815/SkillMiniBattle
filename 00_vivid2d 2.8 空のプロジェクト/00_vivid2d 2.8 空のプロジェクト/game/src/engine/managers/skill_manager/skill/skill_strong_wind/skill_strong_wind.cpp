#include "skill_strong_wind.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../object_manager/object_manager.h"
#include "../../../../../game/components/player_component/player_component.h"


const float CSkillStrongWind::m_wind_strength = 90.0f;
const float CSkillStrongWind::m_cool_time = 5.0f;
const float CSkillStrongWind::m_duration_time = 5.0f;
const float CSkillStrongWind::m_effect_scale = 2.0f;
const int   CSkillStrongWind::m_se_volume = 10000;

CSkillStrongWind::CSkillStrongWind(void)
	:CSkill(SKILL_CATEGORY::ACTIVE ,m_duration_time, m_cool_time)
	,m_Effect(nullptr)
	,m_SkillEffect(nullptr)
{

}

CSkillStrongWind::~CSkillStrongWind(void)
{

}

/*!
 *  @brief      初期化
 */
void
CSkillStrongWind::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
}

/*!
 *  @brief      更新
 */
void
CSkillStrongWind::
Update(void)
{
	CSkill::Update();
	auto allPlayers = CObjectManager::GetInstance().GetObjectsWithComponent<PlayerComponent>();
	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		break;

	case SKILL_STATE::ACTIVE:
		for (auto& player : allPlayers)
		{
			auto playerComponent = player->GetComponent<PlayerComponent>();
			if (playerComponent && playerComponent->GetPlayerID() != m_Player.lock()->GetComponent<PlayerComponent>()->GetPlayerID())
			{
				playerComponent->AddAffectedVelocity(CVector3(0.0f, 0.0f, -m_wind_strength));
			}
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
CSkillStrongWind::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      解放
 */
void
CSkillStrongWind::
Finalize(void)
{
	CSkill::Finalize();


}

/*!
 *  @brief      アクション呼び出し
 */
void
CSkillStrongWind::
Action(void)
{
	if (m_State != SKILL_STATE::WAIT) return;

	CSoundManager::GetInstance().Play_SE(SE_ID::STRONG_WIND, false);
	CSoundManager::GetInstance().SetSEVolume(SE_ID::STRONG_WIND, m_se_volume);

	CVector3 effectPosition = CVector3().ZERO;

	m_Effect = CEffectManager::GetInstance().Create(EFFECT_ID::STRONG_WIND, effectPosition, CVector3(), 5.0f);
	m_SkillEffect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_STAR, CVector3().ZERO, CVector3(), m_effect_scale);
	m_SkillEffect->SetParent(m_Player.lock());

	m_State = SKILL_STATE::ACTIVE;
}

/*!
 *  @brief      アクション終了
 */
void
CSkillStrongWind::
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

	for (int i = 10000; i > 0; i--)
	{
		CSoundManager::GetInstance().SetSEVolume(SE_ID::STRONG_WIND, i);
	}
}