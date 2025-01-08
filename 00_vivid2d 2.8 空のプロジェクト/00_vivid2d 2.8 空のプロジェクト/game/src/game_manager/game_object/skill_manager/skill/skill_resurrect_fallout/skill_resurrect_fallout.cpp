#include "skill_resurrect_fallout.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../object_manager/object_manager.h"

const float		CSkillResurrectFallout::m_resurrect_height = 200.0f;

CSkillResurrectFallout::CSkillResurrectFallout(void)
	:CSkill(SKILL_CATEGORY::RESURRECT)
	, m_Effect(nullptr)

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
	
	m_State = SKILL_STATE::WAIT;
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
				CVector3 resurrectPos = (*it)->GetPosition();
				resurrectPos.y += m_resurrect_height;
				m_Player->SetPosition(resurrectPos);
				m_State = SKILL_STATE::COOLDOWN;
				break;
			}
			++it;
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