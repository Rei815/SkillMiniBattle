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
	 *  @brief      初期化(純粋仮想関数のため派生先で定義)
	 *
	*/
	virtual void	Initialize(void* pointer) = 0;

	/*!
	 *  @brief      更新
	 */
	virtual void	Update(void);

	/*!
	 *  @brief      解放
	 */
	virtual void	Finalize(void);

	/*!
	 *  @brief      アクティブフラグ取得
	 *
	 *  @return     アクティブフラグ
	 */
	bool            IsActive(void);

	/*!
	 *  @brief      アクティブフラグ設定
	 */
	void            Delete();

protected:
	
	bool            m_ActiveFlag;   //!< アクティブフラグ
};