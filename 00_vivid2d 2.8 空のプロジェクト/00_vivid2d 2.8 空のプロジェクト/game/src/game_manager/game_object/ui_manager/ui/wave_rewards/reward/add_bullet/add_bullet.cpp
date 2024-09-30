#include "add_bullet.h"
#include "../../../../../unit_manager/unit_manager.h"

const std::string CAddBullet::m_text = "���ː��ǉ�";

/*
 *  �R���X�g���N�^
 */
CAddBullet::
CAddBullet()
    : CReward(m_text)
{
}

/*
 *  �f�X�g���N�^
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
