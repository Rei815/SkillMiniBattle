#pragma once
class IAnimation
{
public:
	/*!
	 *  @brief      コンストラクタ
	 */
	IAnimation();

	/*!
	 *  @brief      コンストラクタ
	 */
	virtual ~IAnimation();

	/*!
	 *  @brief      初期化
	 *
	 *  @param[in]  object_pointer    アニメーションさせるオブジェクトのポインタ
	*/
	virtual void Initialize(void* object_pointer) = 0;

	/*!
	 *  @brief      更新
	 */
	virtual void Update(void);

	/*!
	 *  @brief      解放
	 */
	virtual void Finalize(void);

	/*!
	 *  @brief      アクティブフラグ取得
	 *
	 *  @return     アクティブフラグ
	 */
	bool            GetActive(void);

	/*!
	 *  @brief      アクティブフラグ設定
	 *
	 *  @param[in]  active  アクティブフラグ
	 */
	void            SetActive(bool active);

	/*!
	 *  @brief      終了フラグ取得
	 *
	 *  @return     終了フラグ
	 */
	bool            GetFinishFlag(void);

	/*!
	 *  @brief      終了フラグ設定
	 *
	 *  @param[in]  finish  終了フラグ
	 */
	void            SetFinishFlag(bool finish);

	/*!
	 *  @brief      アクティブフラグ設定
	 *
	 *  @param[in]  active  アクティブフラグ
	 */
	void            SetEndPosition(bool active);

protected:
	
	bool            m_ActiveFlag;   //!< アクティブフラグ
	bool			m_FinishFlag;
};