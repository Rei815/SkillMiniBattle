#include "skill_resurrect_belt.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../object_manager/object_manager.h"
#include "../../../sound_manager/sound_manager.h"

const CVector3	CSkillResurrectBelt::m_resurrect_position = CVector3(0.0f,0.0f,0.0f);
const float		CSkillResurrectBelt::m_effect_scale = 2.0f;

CSkillResurrectBelt::CSkillResurrectBelt(void)
	:CSkill(SKILL_CATEGORY::PASSIVE)
	, m_Effect(nullptr)
	, m_SkillEffect(nullptr)

{

}

CSkillResurrectBelt::~CSkillResurrectBelt(void)
{

}

/*!
 *  @brief      初期化
 */
void
CSkillResurrectBelt::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
}

/*!
 *  @brief      更新
 */
void
CSkillResurrectBelt::
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
		CSoundManager::GetInstance().Play_SE(SE_ID::RESURECT, false);
		m_Player->SetPosition(m_resurrect_position);
		m_State = SKILL_STATE::COOLDOWN;
		break;

	case SKILL_STATE::COOLDOWN:
		break;
	}
}

/*!
 *  @brief      描画
 */
void
CSkillResurrectBelt::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      解放
 */
void
CSkillResurrectBelt::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      アクション呼び出し
 */
void
CSkillResurrectBelt::
Action()
{
}

/*!
 *  @brief      アクション終了
 */
void
CSkillResurrectBelt::
ActionEnd(void)
{
	if (m_SkillEffect != nullptr)
	{
		m_SkillEffect->SetActive(false);
		m_SkillEffect = nullptr;
	}
}