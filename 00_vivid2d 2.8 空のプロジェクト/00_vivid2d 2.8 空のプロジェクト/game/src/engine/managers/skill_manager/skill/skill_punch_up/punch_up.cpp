#include "punch_up.h"
#include "../../../unit_manager/unit_manager.h"

CPunchUp::CPunchUp(void)
	:CSkill(SKILL_CATEGORY::PASSIVE)
{

}

CPunchUp::~CPunchUp(void)
{

}

/*!
 *  @brief      初期化
 */
void
CPunchUp::
Initialize(SKILL_ID skill_id)
{
	CSkill::Initialize(skill_id);
}

/*!
 *  @brief      更新
 */
void
CPunchUp::
Update(void)
{
	CSkill::Update();


}

/*!
 *  @brief      描画
 */
void
CPunchUp::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      解放
 */
void
CPunchUp::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      アクション呼び出し
 */
void
CPunchUp::
Action(void)
{

}

/*!
 *  @brief      アクション終了
 */
void
CPunchUp::
ActionEnd(void)
{

}