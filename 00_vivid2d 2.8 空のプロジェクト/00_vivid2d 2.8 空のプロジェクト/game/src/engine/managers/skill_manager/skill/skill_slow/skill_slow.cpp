#include "skill_slow.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../../../game/components/player_component/player_component.h"

const float CSkillSlow::m_cool_time = 20.0f;
const float CSkillSlow::m_duration_time = 3.0f;
const float CSkillSlow::m_effect_scale = 2.0f;

CSkillSlow::CSkillSlow(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, m_duration_time, m_cool_time)
	,m_SkillEffect(nullptr)
	,m_DebuffEffect(nullptr)
	, m_EffectList()
{
}

CSkillSlow::~CSkillSlow(void)
{
}

void CSkillSlow::Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);

}

void CSkillSlow::Update(void)
{
	CSkill::Update();

	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		break;

	case SKILL_STATE::ACTIVE:
		break;

	case SKILL_STATE::COOLDOWN:
		break;
	}
}

void CSkillSlow::Draw(void)
{
	CSkill::Draw();
}

void CSkillSlow::Finalize(void)
{
	CSkill::Finalize();
}

void CSkillSlow::Action()
{
	if (m_State != SKILL_STATE::WAIT)	return;

	CSoundManager::GetInstance().Play_SE(SE_ID::SLOW, false);

	
	// 1. 全てのプレイヤーオブジェクトを取得
	auto allPlayers = om.GetObjectsWithComponent<PlayerComponent>();
	// 2. 自分以外の全プレイヤーに効果を適用
	for (auto& targetPlayerObject : allPlayers)
	{
		if (targetPlayerObject == m_Player.lock())
		{
			continue; // 自分自身はスキップ
		}
		// ターゲットのPlayerComponentを取得して、速度低下を適用
		if (auto targetComp = targetPlayerObject->GetComponent<PlayerComponent>())
		{
			targetComp->MulMoveSpeedRate(0.5f);
		}
		m_EffectList.push_front(CEffectManager::GetInstance().Create(EFFECT_ID::DEBUFF, CVector3().ZERO, CVector3(), m_effect_scale));
		m_EffectList.front()->SetParent(targetPlayerObject);
	}

	m_SkillEffect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_STAR, CVector3().ZERO, CVector3(), m_effect_scale);
	m_SkillEffect->SetParent(m_Player.lock());
	m_State = SKILL_STATE::ACTIVE;
}

void CSkillSlow::ActionEnd(void)
{
	if (m_SkillEffect != nullptr)
	{
		m_SkillEffect->Delete();
		m_SkillEffect = nullptr;
	}

	if (m_EffectList.empty() == false)
	{
		std::list<std::shared_ptr<IEffect>>::iterator it = m_EffectList.begin();
		while (it != m_EffectList.end())
		{
			(*it)->Delete();

			it++;
		}
		m_EffectList.clear();
	}
	auto allPlayers = om.GetObjectsWithComponent<PlayerComponent>();
	for (auto& targetPlayerObject : allPlayers)
	{
		if (targetPlayerObject == m_Player.lock())
		{
			continue; // 自分自身はスキップ
		}
		// ターゲットのPlayerComponentを取得して、速度低下を適用
		if (auto targetComp = targetPlayerObject->GetComponent<PlayerComponent>())
		{
			targetComp->DivMoveSpeedRate(0.5f);
		}
	}
}