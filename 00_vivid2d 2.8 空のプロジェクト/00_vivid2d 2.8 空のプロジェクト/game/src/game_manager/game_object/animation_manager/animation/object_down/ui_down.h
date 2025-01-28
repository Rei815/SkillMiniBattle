#pragma once
#include "..\animation.h"
#include "../../../ui_manager/ui/ui.h"
class CUIDown: public IAnimation
{
public:
	CUIDown();

	~CUIDown();

	/*!
	 *  @brief      ������
	 *
	 *  @param[in]  key_pointer    UI�̃|�C���^
	*/
	void Initialize(void* ui_pointer);

	/*!
	 *  @brief      �X�V
	 */
	void Update();

	/*!
	 *  @brief      ���
	 */
	void Finalize();
private:

	static const float			m_down_final_height;		//!< �~���Ƃ��̍ŏI���x
	static const float			m_speed;					//!< �����̑���
	CTimer						m_Timer;					//!< �^�C�}�[

	static const float          m_end_time;         //!< �I������
	float                       m_EaseTimer;        //!< �o�ߎ���
	float                       m_StartValue;       //!< �J�n�l
	float                       m_FinishValue;      //!< �I���l
	CUI*						m_UI;
};