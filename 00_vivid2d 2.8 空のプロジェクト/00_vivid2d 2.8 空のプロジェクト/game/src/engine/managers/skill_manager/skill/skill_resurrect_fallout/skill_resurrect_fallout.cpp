#include "skill_resurrect_fallout.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../object_manager/object_manager.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../../../game/components/gimmick_component/fall_gimmick_component/fall_gimmick_component.h"
#include "../../../../../engine/components/transform_component/transform_component.h"
#include <game/components/player_component/player_component.h>

const float		CSkillResurrectFallout::m_resurrect_height = 200.0f;
const float		CSkillResurrectFallout::m_effect_scale = 2.0f;
const CVector3	CSkillResurrectFallout::m_position = CVector3();

CSkillResurrectFallout::CSkillResurrectFallout(void)
	:CSkill(SKILL_CATEGORY::PASSIVE)
	, m_ResurrectEffect(nullptr)
	, m_SkillEffect(nullptr)

{

}

CSkillResurrectFallout::~CSkillResurrectFallout(void)
{

}

/*!
 *  @brief      初期化
 */
void
CSkillResurrectFallout::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
}

/*!
 *  @brief      更新
 */
void
CSkillResurrectFallout::
Update(void)
{
	CSkill::Update();

	auto allGimmickObject = CObjectManager::GetInstance().GetObjectsWithComponent<FallGimmickComponent>();
	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		break;
	case SKILL_STATE::ACTIVE:
	{
		for (auto& gimmickObject : allGimmickObject)
		{
			if (auto& gimmick = gimmickObject->GetComponent<FallGimmickComponent>())
			{
				if (gimmick->GetState() == GIMMICK_STATE::WAIT)
				{
					CSoundManager::GetInstance().Play_SE(SE_ID::RESURECT, false);
					CVector3 resurrectPos = gimmickObject->GetComponent<TransformComponent>()->GetPosition();
					resurrectPos.y += m_resurrect_height;
					auto& transform = m_Player.lock()->GetComponent<TransformComponent>();
					transform->SetPosition(resurrectPos);
					auto& playerComp = m_Player.lock()->GetComponent<PlayerComponent>();
					playerComp->SetVelocity(CVector3::ZERO);
					m_SkillEffect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_STAR, CVector3().ZERO, CVector3(), m_effect_scale);
					m_ResurrectEffect = CEffectManager::GetInstance().Create(EFFECT_ID::RESURRECT, CVector3().ZERO, CVector3(), m_effect_scale);
					m_SkillEffect->SetParent(m_Player.lock());
					m_ResurrectEffect->SetParent(m_Player.lock());

					m_State = SKILL_STATE::COOLDOWN;
					break;

				}
			}
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
CSkillResurrectFallout::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      解放
 */
void
CSkillResurrectFallout::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      アクション呼び出し
 */
void
CSkillResurrectFallout::
Action()
{
}

/*!
 *  @brief      アクション終了
 */
void
CSkillResurrectFallout::
ActionEnd(void)
{
	if (m_SkillEffect != nullptr)
	{
		m_SkillEffect->Delete();
		m_SkillEffect = nullptr;
	}
	if (m_ResurrectEffect != nullptr)
	{
		m_ResurrectEffect->Delete();
		m_ResurrectEffect = nullptr;
	}
}