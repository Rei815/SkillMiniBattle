#pragma once
#include "../../../engine/core/component/component.h"
#include "../../../engine/utility/timer/timer.h"
// ギミックの状態を定義
enum class GIMMICK_STATE
{
    WAIT,
    PLAY,
    FINISH,
};

class GimmickComponent : public IComponent
{
public:
	/*!
	 *  @brief      コンストラクタ
	 */
    GimmickComponent();

	/*!
	 *       @brief      デストラクタ
     */
    virtual ~GimmickComponent() = default;

    /*!
	 *  @brief      コンポーネントの更新
     * 
	 *  @param[in] delta_time 前フレームからの経過時間
	 *  @param[in] owner      コンポーネントをアタッチしたオーナーオブジェクト
     */
    void Update(float delta_time, CGameObject* owner) override;

    /*!
	 *  @brief      ギミックの状態を取得
     */
    GIMMICK_STATE GetState() const { return m_State; }

    /*!
	 *  @brief      ギミックの状態を設定
     * 
	 *  @param[in]  state   ギミックの状態を設定する値
     */
    void SetState(GIMMICK_STATE state) { m_State = state; }

    /*!
	 *  @brief      タイマーを設定
     * 
	 *  @param[in]  time    タイマーの時間を設定する値
     */
    void SetTimer(float time);


protected:
	GIMMICK_STATE m_State;  //!< ギミックの状態
	CTimer        m_Timer;  //!< タイマー
};  