#include "damage_up.h"
#include "../../../../../unit_manager/unit_manager.h"
const std::string CDamageUp::m_text = "ダメージ増加";

/*
 *  コンストラクタ
 */
CDamageUp::
CDamageUp()
	: CReward(m_text)
{
}

/*
 *  デストラクタ
 */
CDamageUp::
~CDamageUp(void)
{
}

void CDamageUp::Update(const vivid::Vector2& position, float offset)
{
    CReward::Update(position, offset);
    if (m_OnClick)
    {
        IUnit* player = CUnitManager::GetInstance().GetPlayer();

        if (player)
            player->DamageUp(0.5f);
    }
}
