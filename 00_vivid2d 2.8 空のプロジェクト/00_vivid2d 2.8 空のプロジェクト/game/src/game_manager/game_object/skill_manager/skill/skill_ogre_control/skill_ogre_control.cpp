#include "skill_ogre_control.h"
#include "../../../object_manager/object_manager.h"

const float CSkillOgreControl::m_cool_time = 30.0f;
const float CSkillOgreControl::m_duration_time = 10.0f;

CSkillOgreControl::CSkillOgreControl(void)
	:CSkill(SKILL_CATEGORY::ACTIVE)
{
}


CSkillOgreControl::~CSkillOgreControl(void)
{
}

void CSkillOgreControl::Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
	m_Target = nullptr;
}

void CSkillOgreControl::Update(void)
{
	CSkill::Update();

	switch (m_State)
	{
	case SKILL_STATE::WAIT:
		break;

	case SKILL_STATE::ACTIVE:
		if (!m_Player->GetPlayerMoving())
		{
			m_Gimmick->OgreControlTurn();
			m_State = SKILL_STATE::COOLDOWN;
			m_Timer.SetUp(m_cool_time);
		}
		break;

	case SKILL_STATE::COOLDOWN:
		break;
	}
}

void CSkillOgreControl::Draw(void)
{
	CSkill::Draw();
}

void CSkillOgreControl::Finalize(void)
{
	CSkill::Finalize();
}

void CSkillOgreControl::Action()
{
	if (m_State == SKILL_STATE::WAIT)
	{
		m_Gimmick = (CDaruma_FallDownGimmick*)(*CObjectManager::GetInstance().GetList().begin())->GetGimmick();
		m_State = SKILL_STATE::ACTIVE;
	}
}

/*!
 *  @brief      アクション終了
 */
void CSkillOgreControl::ActionEnd(void)
{

}