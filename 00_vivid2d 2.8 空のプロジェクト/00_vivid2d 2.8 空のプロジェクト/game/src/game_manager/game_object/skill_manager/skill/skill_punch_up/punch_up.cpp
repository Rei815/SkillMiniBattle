#include "punch_up.h"
#include "../../../unit_manager/unit_manager.h"

const float CPunchUp::speed_up_rate = 1.25f;

CPunchUp::CPunchUp(void)
	:CSkill()
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

	m_State = SKILL_STATE::WAIT;

	//player->SetMoveSpeedRate(speed_up_rate);
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