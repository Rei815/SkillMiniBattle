#include "skill_mimicry.h"
#include "../../../sound_manager/sound_manager.h"

const float CSkillMimicry::m_cool_time = 10.0f;
const float CSkillMimicry::m_duration_time = 5.0f;
const float CSkillMimicry::m_mimicry_speed_rate = 0.5f;
const float CSkillMimicry::m_effect_scale = 3.0f;

const CVector3 CSkillMimicry::m_model_pos = CVector3(100.0f, 0, 0);
const CVector3 CSkillMimicry::m_model_rot = CVector3(0, 90.0f, 0);
const float CSkillMimicry::m_model_scale = 0.1f;
const std::string CSkillMimicry::m_model_name = "data\\Models\\skill_mimicry_obj.mv1";

CSkillMimicry::CSkillMimicry(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, m_duration_time, m_cool_time)
	,m_SkillEffect(nullptr)
	,m_ObjModel()
{
}

CSkillMimicry::~CSkillMimicry(void)
{
}

void CSkillMimicry::Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);

	m_ObjModel.Initialize(m_model_name,CVector3::ZERO, CVector3(m_model_scale, m_model_scale, m_model_scale));
	
	m_ObjTransform.rotation = m_model_rot;
	m_ObjTransform.scale = CVector3(m_model_scale, m_model_scale, m_model_scale);
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

	m_ObjTransform.position = m_Player.lock()->GetPosition() + m_model_pos;
	m_ObjModel.Update(m_ObjTransform);
}

void CSkillMimicry::Draw(void)
{
	CSkill::Draw();

	if (m_State == SKILL_STATE::ACTIVE)
	{
		m_ObjModel.Draw();
	}
}

void CSkillMimicry::Finalize(void)
{
	CSkill::Finalize();
	m_ObjModel.Finalize();
}

void CSkillMimicry::Action()
{
	if (m_State != SKILL_STATE::WAIT)	return;

	CSoundManager::GetInstance().Play_SE(SE_ID::MIMICRY, false);
	m_Player.lock()->MulMoveSpeedRate(m_mimicry_speed_rate);
	m_Player.lock()->StartInvincible(m_duration_time);
	m_State = SKILL_STATE::ACTIVE;
	CVector3 effect_position = m_Player.lock()->GetPosition();


	m_SkillEffect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_STAR, effect_position, CVector3(), m_effect_scale);
	m_SkillEffect->SetParent(m_Player.lock());
}

/*!
 *  @brief      アクション終了
 */
void CSkillMimicry::ActionEnd(void)
{
	m_Player.lock()->DivMoveSpeedRate(m_mimicry_speed_rate);
}
