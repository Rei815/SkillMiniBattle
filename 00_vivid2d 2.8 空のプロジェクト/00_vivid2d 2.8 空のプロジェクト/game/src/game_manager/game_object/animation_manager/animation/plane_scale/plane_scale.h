#pragma once
#include "..\animation.h"
#include "../../../ui_manager/ui/ui.h"
#include "../../../ui_manager/ui/plane_game_image/plane_game_image.h"
#include <memory>

class CPlaneScale : public IAnimation
{
public:
	CPlaneScale();

	~CPlaneScale();

	/*!
	 *  @brief      ������
	 *
	*/
	void Initialize(void* plane_pointer)override;

	/*!
	 *  @brief      �X�V
	 */
	void Update();

	/*!
	 *  @brief      ���
	 */
	void Finalize();
private:
	static const CVector3				m_min_scale;	//!< �g�嗦�̍ŏ��l
	static const float					m_speed;		//!< �A�j���[�V�������x

	std::shared_ptr<CPlaneGameImage>	m_Plane;		//!< ���ʂ̃|�C���^
};