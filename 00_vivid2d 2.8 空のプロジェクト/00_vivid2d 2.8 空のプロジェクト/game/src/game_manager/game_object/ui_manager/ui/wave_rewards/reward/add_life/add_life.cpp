#include "add_life.h"
#include "../../../../../unit_manager/unit_manager.h"
#include "../../../../../unit_manager/unit/player/player.h"

const std::string CAddLife::m_text = "���C�t�ǉ�";
/*
 *  �R���X�g���N�^
 */
 CAddLife::
 CAddLife()
	: CReward(m_text)
 {
}

/*
 *  �f�X�g���N�^
 */
 CAddLife::
~ CAddLife(void)
{
}

 void CAddLife::Update(const vivid::Vector2& position, float offset)
 {
     CReward::Update(position, offset);
     if (m_OnClick)
     {
         m_OnClick = false;
         IUnit* player = CUnitManager::GetInstance().GetPlayer();

         if (player)
             player->AddLife();
     }
 }
