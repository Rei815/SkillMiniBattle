#include "skill_select_icon.h"
#include "../../../unit_manager/unit/unit_id.h"

const vivid::Vector2    CSkillSelectIcon::m_positionList[] = 
	{
		vivid::Vector2(100, 348),		//Player1
		vivid::Vector2(367, 348),		//Player2
		vivid::Vector2(633, 348),		//Player3
		vivid::Vector2(900, 348)		//Player4
	};

const int               CSkillSelectIcon::m_height = 384;
const int               CSkillSelectIcon::m_width = 384;
const vivid::Rect       CSkillSelectIcon::m_rect = vivid::Rect{ 0, 0, m_width, m_height };
const vivid::Vector2    CSkillSelectIcon::m_scale = vivid::Vector2(0.5f, 0.5f);
const vivid::Vector2    CSkillSelectIcon::m_anchor = vivid::Vector2((m_width * m_scale.x) / 2, (m_height * m_scale.y) / 2);

const std::string CSkillSelectIcon::m_SkillIconFileName[] =
{
		"data\\Textures\\skill_icon_speedup_test.png",
		"data\\Textures\\skill_icon_jumpup_test.png",
		"data\\Textures\\skill_icon_floating.png",
		"data\\Textures\\skill_icon_stomp.png",
		"data\\Textures\\skill_icon_dash_test.png",
		"data\\Textures\\skill_icon_spawnwall_test.png",
		"data\\Textures\\skill_icon_barrier_test.png",
		"data\\Textures\\skill_icon_invisible.png",
		"data\\Textures\\skill_icon_resurrect.png",
		"data\\Textures\\skill_icon_null_test.png"
};

/*
 *  �R���X�g���N�^
 */
CSkillSelectIcon::
CSkillSelectIcon(UI_ID id)
	: CUI(m_width, m_height, id)
{
}

/*
 *  �f�X�g���N�^
 */
CSkillSelectIcon::
~CSkillSelectIcon(void)
{
}

/*
 *  ������
 */
void
CSkillSelectIcon::
Initialize(void)
{
	CUI::Initialize();
}

/*
 *  �X�V
 */
void
CSkillSelectIcon::
Update(void)
{
	CUI::Update();
}

/*
 *  �`��
 */
void
CSkillSelectIcon::
Draw(void)
{
	CUI::Draw();

	vivid::DrawTexture(m_FileName, m_Position, 0xffffffff, m_rect, m_anchor, m_scale);
}

/*
 *  ���
 */
void
CSkillSelectIcon::
Finalize(void)
{
	CUI::Finalize();
}

/*
void
CSkillSelectIcon::
SetIcon(SKILL_ID_FALLOUT skill_id, int PosNum)
{
	m_FileName = m_fallgameFileName[(int)skill_id];

	if (PosNum >= 0 && PosNum < (int)UNIT_ID::NONE)
		m_Position = m_positionList[PosNum];
	else
		m_Position = vivid::Vector2().ZERO;
}

void
CSkillSelectIcon::
SetIcon(SKILL_ID_DARUMA skill_id, int PosNum)
{
	m_FileName = m_darumaFileName[(int)skill_id];

	if (PosNum >= 0 && PosNum < (int)UNIT_ID::NONE)
		m_Position = m_positionList[PosNum];
	else
		m_Position = vivid::Vector2().ZERO;
}

void
CSkillSelectIcon::
SetIcon(SKILL_ID_DODGEBALL skill_id, int PosNum)
{
	m_FileName = m_dodgeballFileName[(int)skill_id];

	if (PosNum >= 0 && PosNum < (int)UNIT_ID::NONE)
		m_Position = m_positionList[PosNum];
	else
		m_Position = vivid::Vector2().ZERO;
}
*/

void
CSkillSelectIcon::
SetIcon(SKILL_ID skill_id, int PosNum)
{
	m_FileName = m_SkillIconFileName[(int)skill_id];

	if (PosNum >= 0 && PosNum < (int)UNIT_ID::NONE)
		m_Position = m_positionList[PosNum];
	else
		m_Position = vivid::Vector2().ZERO;
}