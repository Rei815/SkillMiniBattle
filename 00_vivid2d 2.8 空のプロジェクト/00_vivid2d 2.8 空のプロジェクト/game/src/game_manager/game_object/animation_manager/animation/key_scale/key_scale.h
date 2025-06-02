#pragma once
#include "..\animation.h"
#include "../../../ui_manager/ui/ui.h"
#include <memory>
class CKeyScale : public IAnimation
{
public:
	CKeyScale();

	~CKeyScale();

	/*!
	 *  @brief      ������
	 *
	*/
	void Initialize();

	/*!
	 *  @brief      �X�V
	 */
	void Update();

	/*!
	 *  @brief      ���
	 */
	void Finalize();
private:
	static const vivid::Vector2 m_max_scale;	//!< �g�嗦�̍ő�l
	static const float			m_speed;
	vivid::Vector2				m_MinScale;	//!< �g�嗦�̍ŏ��l
	std::unique_ptr<CUI>		m_Key;	//!< ���̃|�C���^
};