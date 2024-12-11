#include "resurrect_fallout.h"
#include "../../../unit_manager/unit_manager.h"
#include "../../../effect_manager/effect_manager.h"
#include "../../../object_manager/object_manager.h"

const float		CResurrectFallout::m_floating_time = 3.0f;
const float		CResurrectFallout::m_cool_time = 3.0f;
const float		CResurrectFallout::m_resurrect_height = 200.0f;
const CVector3	CResurrectFallout::m_scale = CVector3(4.0f, 1.0f, 4.0f);

CResurrectFallout::CResurrectFallout(void)
	:CSkill(SKILL_CATEGORY::RESURRECT)
	, m_Effect(nullptr)

{

}

CResurrectFallout::~CResurrectFallout(void)
{

}

/*!
 *  @brief      初期化
 */
void
CResurrectFallout::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
}

/*!
 *  @brief      更新
 */
void
CResurrectFallout::
Update(void)
{
	CSkill::Update();
}

/*!
 *  @brief      描画
 */
void
CResurrectFallout::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      解放
 */
void
CResurrectFallout::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      アクション呼び出し
 */
void
CResurrectFallout::
Action()
{
	if (m_CoolTime.Finished() == false) return;

	CObjectManager::OBJECT_LIST objectList = CObjectManager::GetInstance().GetList();
	CObjectManager::OBJECT_LIST::iterator it = objectList.begin();

	while (it != objectList.end())
	{
		if ((*it)->GetGimmick()->GetState() == GIMMICK_STATE::WAIT)
		{
			CVector3 resurrectPos = (*it)->GetPosition();
			resurrectPos.y += m_resurrect_height;
			m_Player->SetPosition(resurrectPos);
			return;
		}
		++it;
	}
}