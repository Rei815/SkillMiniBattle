#include "skill_mimicry.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../../components/model_component/model_component.h"
#include "../../../../../game/components/player_component/player_component.h"

const float CSkillMimicry::m_cool_time = 10.0f;
const float CSkillMimicry::m_duration_time = 5.0f;
const float CSkillMimicry::m_mimicry_speed_rate = 0.5f;
const float CSkillMimicry::m_effect_scale = 3.0f;

const CVector3 CSkillMimicry::m_model_pos = CVector3(100.0f, 0, 0);
const CVector3 CSkillMimicry::m_model_rot = CVector3(0, 90.0f, 0);
const float CSkillMimicry::m_model_scale = 0.1f;

CSkillMimicry::CSkillMimicry(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, m_duration_time, m_cool_time)
	,m_SkillEffect(nullptr)
{
}

CSkillMimicry::~CSkillMimicry(void)
{
}

void CSkillMimicry::Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);

	m_GameObject->AddComponent<ModelComponent>(MODEL_ID::SKILL_MIMICRY_OBJ);
	// TransformComponent���擾���A�����ݒ���s��
	if (auto transformComp = m_GameObject->GetComponent<TransformComponent>())
	{
		transformComp->SetScale(CVector3(m_model_scale, m_model_scale, m_model_scale));
		transformComp->SetRotation(CVector3(m_model_rot.x, m_model_rot.y, m_model_rot.z));
		m_TransformComponent = transformComp;
	}
}

void CSkillMimicry::Update(void)
{
	CSkill::Update();

	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		//m_Player.lock()->SetAlpha(1.0f);
		break;

	case SKILL_STATE::ACTIVE:
		//m_Player.lock()->DecAlpha(0.5f);
		break;

	case SKILL_STATE::COOLDOWN:
		//m_Player.lock()->RevertAlpha(1.0f);
		break;
	}

	m_TransformComponent->SetPosition(m_TransformComponent->GetPosition() + m_model_pos);
	m_GameObject->Update(vivid::GetDeltaTime());
}

void CSkillMimicry::Draw(void)
{
	CSkill::Draw();

	if (m_State == SKILL_STATE::ACTIVE)
	{
		m_GameObject->Draw();
	}
}

void CSkillMimicry::Finalize(void)
{
	CSkill::Finalize();
}

void CSkillMimicry::Action()
{
	if (m_State != SKILL_STATE::WAIT)	return;

	CSoundManager::GetInstance().Play_SE(SE_ID::MIMICRY, false);

	auto PlayerComp = m_GameObject->GetComponent<PlayerComponent>();
	PlayerComp->MulMoveSpeedRate(m_mimicry_speed_rate);
	PlayerComp->StartInvincible(m_duration_time);
	m_State = SKILL_STATE::ACTIVE;
	CVector3 effect_position = m_TransformComponent->GetPosition();


	m_SkillEffect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_STAR, effect_position, CVector3(), m_effect_scale);
	m_SkillEffect->SetParent(m_Player.lock());
}

/*!
 *  @brief      �A�N�V�����I��
 */
void CSkillMimicry::ActionEnd(void)
{
	auto PlayerComp = m_GameObject->GetComponent<PlayerComponent>();

	PlayerComp->DivMoveSpeedRate(m_mimicry_speed_rate);
}
