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
	static const vivid::Vector2 m_max_scale;	//!< 拡大率の最大値
	static const float			m_speed;
	vivid::Vector2				m_MinScale;	//!< 拡大率の最小値
	std::shared_ptr<CUI>		m_Key;	//!< 鍵のポインタ
};