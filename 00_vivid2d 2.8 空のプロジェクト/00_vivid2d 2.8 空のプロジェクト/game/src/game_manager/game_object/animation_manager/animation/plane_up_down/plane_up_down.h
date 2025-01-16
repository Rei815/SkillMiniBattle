#pragma once
#include "..\animation.h"
#include "../../../ui_manager/ui/ui.h"
class CPlaneUpDown : public IAnimation
{
public:
	CPlaneUpDown();

	~CPlaneUpDown();

	/*!
	 *  @brief      ������
	 *
	 *  @param[in]  key_pointer    ���̃|�C���^
	*/
	void Initialize(void* plane_pointer);

	/*!
	 *  @brief      �X�V
	 */
	void Update();

	/*!
	 *  @brief      ���
	 */
	void Finalize();
private:
	static const vivid::Vector2 m_min_position;	//!< �g�嗦�̍ŏ��l
	static const vivid::Vector2 m_max_position;	//!< �g�嗦�̍ő�l
	static const float			m_speed;
	CUI*						m_Plane;	//!< ���ʂ̃|�C���^
};