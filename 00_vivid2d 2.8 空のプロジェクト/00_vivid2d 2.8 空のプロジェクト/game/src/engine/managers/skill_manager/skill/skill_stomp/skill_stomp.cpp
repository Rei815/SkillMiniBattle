#include "skill_stomp.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../../components/model_component/model_component.h"
#include "../../../../components/transform_component/transform_component.h"

const float CSkillStomp::m_cool_time = 10.0f;
const float CSkillStomp::m_effect_scale = 2.0f;

CSkillStomp::CSkillStomp(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, 0.0f, m_cool_time)
	,m_SkillEffect(nullptr)
{

}

CSkillStomp::~CSkillStomp(void)
{

}

/*!
 *  @brief      ������
 */
void
CSkillStomp::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);

}

/*!
 *  @brief      �X�V
 */
void
CSkillStomp::
Update(void)
{
	CSkill::Update();
}

/*!
 *  @brief      �`��
 */
void
CSkillStomp::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      ���
 */
void
CSkillStomp::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      �A�N�V�����Ăяo��
 */
void
CSkillStomp::
Action()
{
	
	if (m_State == SKILL_STATE::COOLDOWN) return;

	CSoundManager::GetInstance().Play_SE(SE_ID::STOMP, false);
	auto transform = m_Player.lock()->GetComponent<TransformComponent>();
	m_Bullet = CBulletManager::GetInstance().Create(m_Player.lock()->GetCategory(), BULLET_ID::SHOCK_WAVE, transform->GetPosition(), CVector3::UP);
	m_Bullet->AddComponent<ModelComponent>(MODEL_ID::STOMP_COLL);

	CEffectManager::GetInstance().Create(EFFECT_ID::SHOCK_WAVE, transform->GetPosition());
	m_Timer.SetUp(m_cool_time);
	m_State = SKILL_STATE::COOLDOWN;

	m_SkillEffect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_STAR, CVector3().ZERO, CVector3(), m_effect_scale);
	m_SkillEffect->SetParent(m_Player.lock());
}

/*!
 *  @brief      �A�N�V�����I��
 */
void
CSkillStomp::
ActionEnd(void)
{
	if (m_SkillEffect != nullptr)
	{
		m_SkillEffect->Delete();
		m_SkillEffect = nullptr;
	}
}