#include "speed_up.h"
#include "../../../unit_manager/unit_manager.h"

const float CSpeedUp::speed_up_rate = 1.25f;

CSpeedUp::CSpeedUp(void)
	:CSkill()
{

}

CSpeedUp::~CSpeedUp(void)
{

}

/*!
 *  @brief      初期化
 */
void
CSpeedUp::
Initialize(CPlayer* player)
{
	CSkill::Initialize(player);

	player->SetMoveSpeedRate(speed_up_rate);
}

/*!
 *  @brief      更新
 */
void
CSpeedUp::
Update(void)
{
	CSkill::Update();


}

/*!
 *  @brief      描画
 */
void
CSpeedUp::
Draw(void)
{
	CSkill::Draw();


}

/*!
 *  @brief      解放
 */
void
CSpeedUp::
Finalize(void)
{
	CSkill::Finalize();


}


/*!
 *  @brief      アクション呼び出し
 */
void
CSpeedUp::
Action(void)
{

}