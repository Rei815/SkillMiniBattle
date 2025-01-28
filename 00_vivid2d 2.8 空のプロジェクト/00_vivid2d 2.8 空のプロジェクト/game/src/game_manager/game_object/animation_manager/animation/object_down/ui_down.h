#pragma once
#include "..\animation.h"
#include "../../../ui_manager/ui/ui.h"
class CUIDown: public IAnimation
{
public:
	CUIDown();

	~CUIDown();

	/*!
	 *  @brief      初期化
	 *
	 *  @param[in]  key_pointer    UIのポインタ
	*/
	void Initialize(void* ui_pointer);

	/*!
	 *  @brief      更新
	 */
	void Update();

	/*!
	 *  @brief      解放
	 */
	void Finalize();
private:

	static const float			m_down_final_height;		//!< 降りるときの最終高度
	static const float			m_speed;					//!< 動きの速さ
	CTimer						m_Timer;					//!< タイマー

	static const float          m_end_time;         //!< 終了時間
	float                       m_EaseTimer;        //!< 経過時間
	float                       m_StartValue;       //!< 開始値
	float                       m_FinishValue;      //!< 終了値
	CUI*						m_UI;
};