#pragma once
#include "..\animation.h"
#include "../../../ui_manager/ui/ui.h"
class CPlaneUpDown : public IAnimation
{
public:
	CPlaneUpDown();

	~CPlaneUpDown();

	/*!
	 *  @brief      初期化
	 *
	 *  @param[in]  key_pointer    鍵のポインタ
	*/
	void Initialize(void* plane_pointer);

	/*!
	 *  @brief      更新
	 */
	void Update();

	/*!
	 *  @brief      解放
	 */
	void Finalize();
private:
	static const vivid::Vector2 m_min_position;	//!< 拡大率の最小値
	static const vivid::Vector2 m_max_position;	//!< 拡大率の最大値
	static const float			m_speed;
	CUI*						m_Plane;	//!< 平面のポインタ
};