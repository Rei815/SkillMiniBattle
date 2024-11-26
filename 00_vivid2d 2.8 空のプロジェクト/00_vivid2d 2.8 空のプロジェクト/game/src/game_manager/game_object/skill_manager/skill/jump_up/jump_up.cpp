#include "jump_up.h"
#include "../../../unit_manager/unit_manager.h"

const float CJumpUp::jump_up_rate = 1.5f;

CJumpUp::CJumpUp(void)
	:CSkill()
{

}

CJumpUp::~CJumpUp(void)
{

}

/*!
 *  @brief      初期化
 */
void
CJumpUp::
Initialize(CPlayer* player)
{
	CSkill::Initialize(player);

	player->SetJumpPowerRate(jump_up_rate);
}

/*!
 *  @brief      更新
 */
void
CJumpUp::
Update(void)
{
	CSkill::Update();


}

/*!
 *  @brief      描画
 */
void
CJumpUp::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      解放
 */
void
CJumpUp::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      アクション呼び出し
 */
void
CJumpUp::
Action(void)
{

}