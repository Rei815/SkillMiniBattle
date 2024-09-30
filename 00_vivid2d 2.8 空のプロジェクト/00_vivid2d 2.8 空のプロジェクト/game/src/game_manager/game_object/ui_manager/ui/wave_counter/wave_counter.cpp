#include "wave_counter.h"
#include "../../../unit_manager/unit_manager.h"

const int    CWaveCounter::m_font_size = 30;
const vivid::Vector2    CWaveCounter::m_position = vivid::Vector2(vivid::WINDOW_WIDTH - m_font_size, m_font_size);

/*
 *  �R���X�g���N�^
 */
CWaveCounter::
CWaveCounter(void)
	: CUI(m_font_size, m_font_size)
	, m_MaxWave(0)
	, m_CurrentWave(0)
{
}

/*
 *  �f�X�g���N�^
 */
CWaveCounter::
~CWaveCounter(void)
{
}

/*
 *  ������
 */
void
CWaveCounter::
Initialize(void)
{
	m_MaxWave = CUnitManager::GetInstance().GetMaxWave();

	m_CurrentWave = 0;

	m_Text = std::to_string(m_CurrentWave) + "  /  " + std::to_string(m_MaxWave);

	m_Position = m_position;
}

/*
 *  �X�V
 */
void
CWaveCounter::
Update(vivid::Vector2 position)
{
	m_CurrentWave = CUnitManager::GetInstance().GetCurrentWave();

	m_Text = std::to_string(m_CurrentWave) + " / " + std::to_string(m_MaxWave);

	m_Position = position;
	m_Position.x = m_Position.x - vivid::GetTextWidth(m_font_size, m_Text) / 2.0f;
	m_Position.y = m_Position.y + 60;
}

/*
 *  �`��
 */
void
CWaveCounter::
Draw(void)
{
	vivid::DrawText(m_font_size, m_Text, m_Position);
}

/*
 *  ���
 */
void
CWaveCounter::
Finalize(void)
{
}

void CWaveCounter::SetPosition(vivid::Vector2 position)
{
	m_Position = position;
}