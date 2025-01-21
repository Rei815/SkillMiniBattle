#pragma once
#include "..\animation.h"
#include "../../../ui_manager/ui/ui.h"
class CKeyScale : public IAnimation
{
public:
	CKeyScale();

	~CKeyScale();

	/*!
	 *  @brief      ������
	 *
	 *  @param[in]  key_pointer    ���̃|�C���^
	*/
	void Initialize(void* key_pointer);

	/*!
	 *  @brief      �X�V
	 */
	void Update();

	/*!
	 *  @brief      ���
	 */
	void Finalize();
private:
	static const vivid::Vector2 m_min_scale;	//!< �g�嗦�̍ŏ��l
	static const vivid::Vector2 m_max_scale;	//!< �g�嗦�̍ő�l
	static const float			m_speed;
	CUI*						m_Key;	//!< ���̃|�C���^
};