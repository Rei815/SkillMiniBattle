#include "skill_barrier.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../../sound_manager/sound_manager.h"


const float CSkillBarrier::m_duration_time = 5.0f;
const float CSkillBarrier::m_cool_time = 25.0f;
const std::string CSkillBarrier::m_collider_model_file_name = "data\\Models\\skill_barrier_collider.mv1";

CSkillBarrier::CSkillBarrier(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, m_duration_time, m_cool_time)
	, m_ColliderModel()
	, m_Effect(nullptr)
{

}

CSkillBarrier::~CSkillBarrier(void)
{

}

/*!
 *  @brief      ������
 */
void
CSkillBarrier::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
}

/*!
 *  @brief      �X�V
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
		if (m_Effect != nullptr)
		{
			m_Effect->SetPosition(m_Player->GetPosition());
			CBulletManager::GetInstance().CheckReflectModel(m_ColliderModel);
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
CSkillBarrier::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      ���
 */
void
CSkillBarrier::
Finalize(void)
{
	CSkill::Finalize();

	m_ColliderModel.Finalize();
}

/*!
 *  @brief      �v���C���[�̃Z�b�g
 */
void CSkillBarrier::SetPlayer(CPlayer* player)
{
	CSkill::SetPlayer(player);

	m_ColliderModel.Initialize(m_collider_model_file_name, m_Player->GetPosition());
}

/*!
 *  @brief      �A�N�V�����Ăяo��
 */
void
CSkillBarrier::
Action(void)
{
	if (m_State != SKILL_STATE::WAIT)
		return;

	CSoundManager::GetInstance().Play_SE(SE_ID::BARRIER, false);

	m_Player->StartInvincible(m_duration_time);
	m_Effect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_BARRIER, m_Player->GetPosition(), 0.04f);
	m_State = SKILL_STATE::ACTIVE;
}



/*!
 *  @brief      �A�N�V�����I��
 */
void
CSkillBarrier::
ActionEnd(void)
{
	if (m_Effect != nullptr)
	{
		m_Effect->SetActive(false);
		m_Effect = nullptr;
	}
}