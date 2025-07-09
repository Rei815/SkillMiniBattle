#include "skill_strong_wind.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../object_manager/object_manager.h"
#include "../../../../../game/components/player_component/player_component.h"


const float CSkillStrongWind::m_wind_strength = 0.15f;
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
 *  @brief      ������
 */
void
CSkillStrongWind::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
}

/*!
 *  @brief      �X�V
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
			if (playerComponent && playerComponent->GetPlayerID() == m_Player.lock()->GetComponent<PlayerComponent>()->GetPlayerID())
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
 *  @brief      �`��
 */
void
CSkillStrongWind::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      ���
 */
void
CSkillStrongWind::
Finalize(void)
{
	CSkill::Finalize();


}

/*!
 *  @brief      �A�N�V�����Ăяo��
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
 *  @brief      �A�N�V�����I��
 */
void
CSkillStrongWind::
ActionEnd(void)
{
	//�G�t�F�N�g������
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