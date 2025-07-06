#include "skill_floating.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../../components/transform_component/transform_component.h"
#include "../../../../../game/components/player_component/player_component.h"
const float		CSkillFloating::m_duration_time = 5.0f;
const float		CSkillFloating::m_cool_time = 10.0f;
const CVector3	CSkillFloating::m_scale = CVector3(4.0f, 1.0f, 4.0f);
const float		CSkillFloating::m_effect_scale = 2.0;

CSkillFloating::CSkillFloating(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, m_duration_time, m_cool_time)
	, m_Effect(nullptr)
	, m_SkillEffect(nullptr)
{

}

CSkillFloating::~CSkillFloating(void)
{

}

/*!
 *  @brief      ������
 */
void
CSkillFloating::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
}

/*!
 *  @brief      �X�V
 */
void
CSkillFloating::
Update(void)
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

	if (m_Effect != nullptr)
	{
		CVector3 effectPosition = m_Player.lock()->GetComponent<TransformComponent>()->GetPosition();
		effectPosition.y -= m_Player.lock()->GetComponent<PlayerComponent>()->GetHeight() / 2;
		m_Effect->SetPosition(effectPosition);
	}

}

/*!
 *  @brief      �`��
 */
void
CSkillFloating::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      ���
 */
void
CSkillFloating::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      �A�N�V�����Ăяo��
 */
void
CSkillFloating::
Action()
{
	if (m_State != SKILL_STATE::WAIT) return;
	auto player = m_Player.lock()->GetComponent<PlayerComponent>();
	auto transform = m_Player.lock()->GetComponent<TransformComponent>();
	CSoundManager::GetInstance().Play_SE(SE_ID::FLOATING, false);
	CVector3 velocity = player->GetVelocity();

	player->SetGravity(CVector3::ZERO);
	player->SetVelocity(CVector3(velocity.x, 0.1f, velocity.z));
	player->SetGroundObject(nullptr);
	player->SetIsGround(false);
	CVector3 effectPosition = transform->GetPosition();
	effectPosition.y -= player->GetHeight() / 2;

	m_Effect = CEffectManager::GetInstance().Create(EFFECT_ID::FLOATING, effectPosition, CVector3::UP, m_scale);
	m_State = SKILL_STATE::ACTIVE;

	m_SkillEffect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_STAR, effectPosition, CVector3(), m_effect_scale);
	m_SkillEffect->SetParent(m_Player.lock());

}

/*!
 *  @brief      �A�N�V�����I��
 */
void
CSkillFloating::
ActionEnd(void)
{
	auto player = m_Player.lock()->GetComponent<PlayerComponent>();

	player->SetGravity(player->GetDefaultGravity());
	if (m_Effect != nullptr )
	{
		m_Effect->Delete();
		m_Effect = nullptr;
	}
	if (m_SkillEffect != nullptr)
	{
		m_SkillEffect->Delete();
		m_SkillEffect = nullptr;
	}

}
		