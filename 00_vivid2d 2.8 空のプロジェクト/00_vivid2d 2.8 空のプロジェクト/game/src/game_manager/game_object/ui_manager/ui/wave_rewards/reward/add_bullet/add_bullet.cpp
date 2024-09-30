#include "add_bullet.h"
#include "../../../../../unit_manager/unit_manager.h"

const std::string CAddBullet::m_text = "発射数追加";

/*
 *  コンストラクタ
 */
CAddBullet::
CAddBullet()
    : CReward(m_text)
{
}

/*
 *  デストラクタ
 */
CAddBullet::
~CAddBullet(void)
{
}

void CAddBullet::Update(const vivid::Vector2& position, float offset)
{
    CReward::Update(position, offset);
    if (m_OnClick)
    {
        IUnit* player = CUnitManager::GetInstance().GetPlayer();

        if (player)
            player->AddBullet();
    }
}
