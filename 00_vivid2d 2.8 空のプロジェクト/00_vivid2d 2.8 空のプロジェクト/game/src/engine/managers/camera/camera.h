#pragma once

#include "vivid.h"
#include "../../utility/timer/timer.h"
/*!
*  @brief      カメラクラス
*/
class CCamera
{
public:

	/*!
	 *  @brief      インスタンスの取得
	 *
	 *  @return     インスタンス
	 */
	static CCamera& GetInstance(void);


	/*!
	 *  @brief      カメラの初期化
	 */
	void Initialize();

	/*!
	 *  @brief      カメラの更新
	 */
	void Update();


	/*!
	 *  @brief      カメラの解放
	 */
	void Finalize();

	/*!
	 *  @brief      追従する動き
	 */
	void Follow(const CVector3& position,const CVector3& offset);

	/*!
	 *  @brief      位置設定
	 */
	void			SetPosition(const CVector3& position);

	/*!
	 *  @brief      向き設定
	 */
	void			SetDirection(const CVector3& direction);

	/*!
	 *  @brief      位置取得
	 */
	CVector3 GetPosition();

	/*!
	 *  @brief      Nearの値を取得
	 */
	float GetNear();

	/*!
	 *  @brief      Farの値を取得
	 */
	float GetFar();

	/*!
	*  @brief      カメラを揺らす
	*/
	void Shake();
private:

	/*!
	*  @brief      カメラの揺れ
	*/
	void _Shake();


	/*!
	 *  @brief      コンストラクタ
	 */
	CCamera(void);

	/*!
	 *  @brief      コピーコンストラクタ
	 *
	 *  @param[in]  rhs     オブジェクト
	 */
	CCamera(const CCamera& rhs);

	/*!
	 *  @brief      デストラクタ
	 */
	~CCamera(void);

	/*!
	 *  @brief      代入演算子
	 *
	 *  @param[in]  rhs 代入オブジェクト
	 *
	 *  @return     自身のオブジェクト
	 */
	CCamera& operator=(const CCamera& rhs);

	static const float		m_lerp_speed;			//!< カメラの動きの速さ
	static const float		m_near;					//!< Nearクリップ
	static const float		m_far;					//!< Farクリップ
	static const float		m_fov;					//!< Fovクリップ
	static const int		m_shake_max_num;		//!< 揺れる回数
	static const float		m_shake_interval;		//!< 揺れの間隔
	static const float		m_shake_value;			//!< 揺れの大きさ
	static const CVector3	m_position;				//!< 初期位置
	static const CVector3	m_direction;			//!< 初期角度

	CVector3				m_Position;				//!< 位置(視点)
	CVector3				m_Direction;			//!< 向き
	float					m_Fov;					//!< 視野角
	CVector3				m_Offset;				//!< オブジェクトとの距離
	CVector3				m_ShakeVector;			//!< 揺れのベクトル
	bool					m_ShakeFlag;			//!< 揺れフラグ
	int						m_ShakeCount;			//!< 揺れた回数
	CVector3				m_PreviousPosition;		//!< 揺れ前の位置
	CTimer					m_ShakeTimer;			//!< 揺れタイマー
};