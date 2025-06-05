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
	 *  @brief      初期化
	 *
	*/
	void Initialize(std::shared_ptr<void> plane_pointer)override;

	/*!
	 *  @brief      更新
	 */
	void Update();

	/*!
	 *  @brief      解放
	 */
	void Finalize();
private:
	static const CVector3				m_min_scale;	//!< 拡大率の最小値
	static const float					m_speed;		//!< アニメーション速度

	std::shared_ptr<CPlaneGameImage>	m_Plane;		//!< 平面のポインタ
};