#pragma once
#include "..\animation.h"
#include "../../../ui_manager/ui/ui.h"
#include "../../../ui_manager/ui/plane_game_image/plane_game_image.h"
#include <memory>
class CPlaneUp : public IAnimation
{
public:
	CPlaneUp();

	~CPlaneUp();

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

	enum class STATE
	{
		WAIT,
		UP,
		DOWN,
	};
	static const CVector3				m_scale;					//!< 拡大率
	static const float					m_up_final_height;			//!< 上がるときの最終高度
	static const CVector3				m_down_initial_position;	//!< 降りるときの初期位置
	static const float					m_up_time;					//!< 上がっている時間
	static const float					m_speed;					//!< 動きの速さ
	static const float					m_end_time;					//!< 終了時間

	std::shared_ptr<CPlaneGameImage>	m_Plane;					//!< 平面のポインタ
	CTimer								m_Timer;					//!< タイマー
	STATE								m_State;					//!< 状態
	
	float								m_EaseTimer;				//!< 経過時間
	float								m_StartValue;				//!< 開始値
	float								m_FinishValue;				//!< 終了値

};