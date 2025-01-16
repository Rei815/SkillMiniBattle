#pragma once
#include "..\animation.h"
#include "../../../ui_manager/ui/ui.h"
class CKeyScale : public IAnimation
{
public:
	CKeyScale();

	~CKeyScale();

	/*!
	 *  @brief      初期化
	 *
	 *  @param[in]  key_pointer    鍵のポインタ
	*/
	void Initialize(void* key_pointer);

	/*!
	 *  @brief      更新
	 */
	void Update();

	/*!
	 *  @brief      解放
	 */
	void Finalize();
private:
	CUI*	m_key;	//!< 鍵のポインタ
	static const vivid::Vector2 m_min_scale;	//!< 拡大率の最小値
	static const vivid::Vector2 m_max_scale;	//!< 拡大率の最大値
	static const float	m_speed;
};