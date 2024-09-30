#include "add_shot.h"
#include "../../../../../unit_manager/unit_manager.h"

const std::string CAddShot::m_text = "���U���ǉ�";

/*
 *  �R���X�g���N�^
 */
CAddShot::
CAddShot()
	: CReward(m_text)
{
}

/*
 *  �f�X�g���N�^
 */
CAddShot::
~CAddShot(void)
{
}

void CAddShot::Update(const vivid::Vector2& position, float offset)
{
    CReward::Update(position, offset);
    if (m_OnClick)
    {
        IUnit* player = CUnitManager::GetInstance().GetPlayer();

        if (player)
            player->AddShot();
    }
}
