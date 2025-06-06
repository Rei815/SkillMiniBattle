#pragma once

/*!
 *  @brief  タイマークラス
 */
class CTimer
{
public:

	enum class COUNT_TYPE
	{
		UP,		//!< カウントアップ
		DOWN	//!< カウントダウン
	};

	/*!
	 *  @brief  コンストラクタ
	 */
	CTimer();

	/*!
	 *  @brief  コンストラクタ
	 */
	CTimer(float time);

	/*!
	 *  @brief  デストラクタ
	 */
	~CTimer();

	/*!
	 *  @brief  初期化
	 */
	void Initialize();

	/*!
	 *  @brief  タイマーの設定
	 * 
	 *  @param[in] limit_time	制限時間			
	 *  @param[in] count_type	カウント方法
	 */
	void SetUp(float limit_time, COUNT_TYPE count_type = COUNT_TYPE::UP);

	/*!
	 *  @brief  更新
	 */
	void Update();

	/*!
	 *  @brief  タイマーをリセット
	 */
	void Reset();

	/*!
	 *  @brief  カウントが終了しているか
	 * 
	 *  @return	bool true 終了 false 未終了
	 */
	bool Finished() const;

	/*!
	 *  @brief  現在のタイマーを取得
	 *
	 *  @return	float タイマー
	 */
	float		GetTimer() const;

	/*!
	 *  @brief  制限時間を設定
	 *
	 *  @param[in]	float limit_time　制限時間
	 */
	void		SetLimitTime(float limit_time);

	/*!
	 *  @brief 制限時間を取得
	 *
	 *  @return	float 制限時間
	 */
	float		GetLimitTime() const;

	/*!
	 *  @brief  アクティブ状態を取得
	 *
	 *  @return	bool true アクティブ false 非アクティブ
	 */
	bool		IsActive() const;

	/*!
	 *  @brief  アクティブ状態を設定
	 *
	 *  @param[in]	bool true アクティブ false 非アクティブ
	 */
	void		SetActive(bool active);

private:
	float		m_LimitTime;	//!< 制限時間
	float		m_StartTime;	//!< 開始時の時間(カウントダウン時)
	float		m_Timer;		//!< タイマー
	bool		m_Active;		//!< アクティブ状態
	COUNT_TYPE	m_CountType;	//!< カウント方法
};