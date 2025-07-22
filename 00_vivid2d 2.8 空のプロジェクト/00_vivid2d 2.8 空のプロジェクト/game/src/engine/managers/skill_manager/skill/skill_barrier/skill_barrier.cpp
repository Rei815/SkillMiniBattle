#include "skill_barrier.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../bullet_manager/bullet_manager.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../../components/transform_component/transform_component.h"
#include "../../../object_manager/object_manager.h"

const float CSkillBarrier::m_duration_time = 5.0f;
const float CSkillBarrier::m_cool_time = 25.0f;
const float CSkillBarrier::m_effect_scale = 3.0f;


CSkillBarrier::CSkillBarrier(void)
	:CSkill(SKILL_CATEGORY::ACTIVE, m_duration_time, m_cool_time)
	, m_Effect(nullptr)
	, m_SkillEffect(nullptr)
{

}

CSkillBarrier::~CSkillBarrier(void)
{

}

/*!
 *  @brief      初期化
 */
void
CSkillBarrier::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
}

/*!
 *  @brief      更新
 */
void
CSkillBarrier::
Update(void)
{
	CSkill::Update();

	auto colliderModel = m_BarrierCollider->GetComponent<ModelComponent>();
	auto transform = m_Player.lock()->GetComponent<TransformComponent>();
	transform->SetPosition(transform->GetPosition());
	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		break;

	case SKILL_STATE::ACTIVE:
		if (m_Effect != nullptr)
		{
			m_Effect->SetPosition(transform->GetPosition());
			CBulletManager::GetInstance().CheckReflectModel(colliderModel->GetHandle());
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
CSkillBarrier::
Draw(void)
{
	CSkill::Draw();
	m_BarrierCollider->Draw();
}

/*!
 *  @brief      解放
 */
void
CSkillBarrier::
Finalize(void)
{
	CSkill::Finalize();

	m_BarrierCollider->Finalize();
}

/*!
 *  @brief      プレイヤーのセット
 */
void CSkillBarrier::SetPlayer(std::shared_ptr<CGameObject> player)
{
	CSkill::SetPlayer(player);

	auto transform = m_Player.lock()->GetComponent<TransformComponent>();
	m_BarrierCollider = CObjectManager::GetInstance().Create(OBJECT_ID::SKILL_BARRIER_OBJECT, transform->GetPosition());
}

/*!
 *  @brief      アクション呼び出し
 */
void
CSkillBarrier::
Action(void)
{
	if (m_State != SKILL_STATE::WAIT)
		return;

	CSoundManager::GetInstance().Play_SE(SE_ID::BARRIER, false);
	auto transform = m_Player.lock()->GetComponent<TransformComponent>();
	auto playerComp = m_Player.lock()->GetComponent<PlayerComponent>();
	playerComp->StartInvincible(m_duration_time);
	//m_Effect = CEffectManager::GetInstance().Create(EFFECT_ID::BARRIER, transform->GetPosition(), 0.04f);
	m_SkillEffect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_STAR, CVector3().ZERO,CVector3(), m_effect_scale);
	m_SkillEffect->SetParent(m_Player.lock());

	m_State = SKILL_STATE::ACTIVE;
}



/*!
 *  @brief      アクション終了
 */
void
CSkillBarrier::
ActionEnd(void)
{
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
}