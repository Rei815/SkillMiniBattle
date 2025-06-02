#pragma once
#include "..\animation.h"
#include "../../../ui_manager/ui/ui.h"
#include "../../../ui_manager/ui/plane_game_image/plane_game_image.h"
class CPlaneUp : public IAnimation
{
public:
	CPlaneUp();

	~CPlaneUp();

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

	enum class STATE
	{
		WAIT,
		UP,
		DOWN,
	};
	static const CVector3				m_scale;					//!< �g�嗦
	static const float					m_up_final_height;			//!< �オ��Ƃ��̍ŏI���x
	static const CVector3				m_down_initial_position;	//!< �~���Ƃ��̏����ʒu
	static const float					m_up_time;					//!< �オ���Ă��鎞��
	static const float					m_speed;					//!< �����̑���
	static const float					m_end_time;					//!< �I������

	std::unique_ptr<CPlaneGameImage>	m_Plane;					//!< ���ʂ̃|�C���^
	CTimer								m_Timer;					//!< �^�C�}�[
	STATE								m_State;					//!< ���
	
	float								m_EaseTimer;				//!< �o�ߎ���
	float								m_StartValue;				//!< �J�n�l
	float								m_FinishValue;				//!< �I���l

};