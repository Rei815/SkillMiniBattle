#include "skill_resurrect_fallout.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../object_manager/object_manager.h"
#include "../../../sound_manager/sound_manager.h"

const float		CSkillResurrectFallout::m_resurrect_height = 200.0f;
const float		CSkillResurrectFallout::m_effect_scale = 2.0f;
const CVector3	CSkillResurrectFallout::m_initial_position = CVector3();

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

	CObjectManager::OBJECT_LIST objectList = CObjectManager::GetInstance().GetList();
	CObjectManager::OBJECT_LIST::iterator it = objectList.begin();
	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		break;
	case SKILL_STATE::ACTIVE:

		while (it != objectList.end())
		{
			if ((*it)->GetGimmick()->GetState() == GIMMICK_STATE::WAIT)
			{
				CSoundManager::GetInstance().Play_SE(SE_ID::RESURECT, false);
				CVector3 resurrectPos = (*it)->GetPosition();
				resurrectPos.y += m_resurrect_height;
				m_Player->SetPosition(resurrectPos);
				m_SkillEffect = CEffectManager::GetInstance().Create(EFFECT_ID::SKILL_STAR, CVector3().ZERO, CVector3(), m_effect_scale);
				m_ResurrectEffect = CEffectManager::GetInstance().Create(EFFECT_ID::RESURRECT, CVector3().ZERO, CVector3(), m_effect_scale);
				m_SkillEffect->SetParent(m_Player);
				m_ResurrectEffect->SetParent(m_Player);

				m_State = SKILL_STATE::COOLDOWN;
				break;
			}

			++it;
		}

		if (it == objectList.end())
		{
			m_Player->SetPosition(m_initial_position);
			m_State = SKILL_STATE::COOLDOWN;

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
		m_SkillEffect->SetActive(false);
		m_SkillEffect = nullptr;
	}
	if (m_ResurrectEffect != nullptr)
	{
		m_ResurrectEffect->SetActive(false);
		m_ResurrectEffect = nullptr;
	}
}