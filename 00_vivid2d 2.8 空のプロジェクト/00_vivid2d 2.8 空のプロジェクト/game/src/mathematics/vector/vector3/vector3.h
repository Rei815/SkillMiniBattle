#pragma once

#include <DxLib.h>

enum COORDINATES_AXIS
{
	X,
	Y,
	Z,
};

/*!
	*  @brief      三次元ベクトルクラス
	*/
class CVector3 : public DxLib::VECTOR
{
public:

	/*!
		*  @brief  コンストラクタ
		*/
	CVector3(void);

	/*!
		*  @brief		コンストラクタ
		*
		*  @param[in]	xVal   X成分
		*  @param[in]	yVal   Y成分
		*  @param[in]	zVal   Z成分
		*/
	CVector3(float xVal, float yVal, float zVal);

	/*!
		*  @brief		コンストラクタ
		*
		*  @param[in]	v  ベクトル
		*/
	CVector3(const DxLib::VECTOR& v);

	/*!
		*  @brief  デストラクタ
		*/
	~CVector3(void);

	/*!
		*  @brief		ベクトルの正規化<br>
		*				自身のベクトルも正規化される
		*
		*  @return		正規化されたベクトル
		*/
	CVector3			Normalize(void);

	/*!
		*  @brief		ベクトルの正規化
		*
		*  @param[in]	v   ベクトルクラス
		*
		*  @return		正規化されたベクトル
		*/
	static CVector3     Normalize(const CVector3& v);

	/*!
		*  @brief		ベクトルの大きさ取得
		*
		*  @return		ベクトルの大きさ
		*/
	float               Length(void);

	/*!
		*  @brief		ベクトルの大きさ取得
		*
		*  @param[in]	v   ベクトルクラス
		*
		*  @return		ベクトルの大きさ
		*/
	static float        Length(const CVector3& v);

	/*!
		*  @brief		2つのベクトルの内積<br>
		*				dot = vA・vB
		*
		*  @param[in]	vA  ベクトルクラス
		*  @param[in]	vB  ベクトルクラス
		*
		*  @return		内積
		*/
	static float        Dot(const CVector3& vA, const CVector3& vB);

	/*!
		*  @brief		2つのベクトルの外積<br>
		*				cross = vA×vB
		*
		*  @param[in]	vA  ベクトルクラス
		*  @param[in]	vB  ベクトルクラス
		*
		*  @return		外積
		*/
	static CVector3     Cross(const CVector3& vA, const CVector3& vB);

	/*!
	*  @brief			線形補間
	*					lerp(a,b,t) = (1 - t) * a + t * b
	*
	*  @param[in]		start  開始点
	*  @param[in]		end  終了点
	*  @param[in]		t  0から１までの範囲の補間パラメータ
	*
	*  @return			位置
	*/
	static CVector3     Lerp(const CVector3& start, const CVector3& end, float t);

	/*!
		*  @brief		代入演算子のオーバーロード
		*
		*  @param[in]	v   ベクトルクラス
		*
		*  @return		ベクトルクラス
		*/
	CVector3&			operator=(const CVector3& v);

	/*!
		*  @brief		代入演算子のオーバーロード
		*
		*  @param[in]	f   フロート値
		*
		*  @return		ベクトルクラス
		*/
	CVector3&			operator=(float f);

	/*!
		*  @brief		加算演算子のオーバーロード
		*
		*  @param[in]	v   ベクトルクラス
		*
		*  @return		ベクトルクラス
		*/
	CVector3&			operator+=(const CVector3& v);

	/*!
		*  @brief		減算演算子のオーバーロード
		*
		*  @param[in]	v   ベクトルクラス
		*
		*  @return		ベクトルクラス
		*/
	CVector3&			operator-=(const CVector3& v);

	/*!
		*  @brief		乗算演算子のオーバーロード
		*
		*  @param[in]	scalar  スカラー値
		*
		*  @return		ベクトルクラス
		*/
	CVector3&			operator*=(float scalar);

	/*!
		*  @brief		乗算演算子のオーバーロード
		*
		*  @param[in]	v  ベクトルクラス
		*
		*  @return		ベクトルクラス
		*/
	CVector3&			operator*=(const CVector3& v);

	/*!
		*  @brief		除算演算子のオーバーロード
		*
		*  @param[in]	scalar  スカラー値
		*
		*  @return		ベクトルクラス
		*/
	CVector3&			operator/=(float scalar);

	/*!
		*  @brief		等価演算子のオーバーロード
		*
		*  @param[in]	v   ベクトルクラス
		*
		*  @return		二つのベクトルが等しい
		*  @retval		true    等しい
		*  @retval		false   等しくない
		*/
	bool                operator==(const CVector3& v) const;

	/*!
		*  @brief		不等演算子のオーバーロード
		*
		*  @param[in]	v   ベクトルクラス
		*
		*  @return		二つのベクトルが等しくない
		*  @retval		true    等しくない
		*  @retval		false   等しい
		*/
	bool				operator!=(const CVector3& v) const;

	/*!
		*  @brief      正符号演算子のオーバーロード
		*
		*  @param[in]  v   ベクトルクラス
		*
		*  @return     ベクトルクラス
		*/
	friend CVector3     operator+(const CVector3& v);

	/*!
		*  @brief		負符号演算子のオーバーロード
		*
		*  @param[in]	v   ベクトルクラス
		*
		*  @return		ベクトルクラス
		*/
	friend CVector3     operator-(const CVector3& v);

	/*!
		*  @brief		加算演算子のオーバーロード
		*
		*  @param[in]	vA  ベクトルクラス
		*  @param[in]	vB  ベクトルクラス
		*
		*  @return		ベクトルクラス
		*/
	friend CVector3     operator+(const CVector3& vA, const CVector3& vB);

	/*!
		*  @brief		加算演算子のオーバーロード
		*
		*  @param[in]	v  ベクトルクラス
		*  @param[in]	f  float型
		*
		*  @return		ベクトルクラス
		*/
	friend CVector3		operator+(const CVector3& vA, float f);

	/*!
		*  @brief		減算演算子のオーバーロード
		*
		*  @param[in]	vA  ベクトルクラス
		*  @param[in]	vB  ベクトルクラス
		*
		*  @return		ベクトルクラス
		*/
	friend CVector3		operator-(const CVector3& vA, const CVector3& vB);

	/*!
		*  @brief		乗算演算子のオーバーロード
		*
		*  @param[in]	vA  ベクトルクラス
		*  @param[in]	vB  ベクトルクラス
		*
		*  @return		ベクトルクラス
		*/
	friend CVector3		operator*(const CVector3& vA, const CVector3& vB);

	/*!
		*  @brief		乗算演算子のオーバーロード
		*
		*  @param[in]	v       ベクトルクラス
		*  @param[in]	scalar  スカラー値
		*
		*  @return		ベクトルクラス
		*/
	friend CVector3		operator*(const CVector3& v, float scalar);

	/*!
		*  @brief		乗算演算子のオーバーロード
		*
		*  @param[in]	scalar  スカラー値
		*  @param[in]	v       ベクトルクラス
		*
		*  @return		ベクトルクラス
		*/
	friend CVector3     operator*(float scalar, const CVector3& v);


	/*!
		*  @brief		ベクトルの方向を回転値（XYZオイラー角）に変換して返す
		*
		*  @param[in]	vector	回転値に変換するベクトル
		*
		*  @return		回転値（XYZオイラー角）
		*/
	CVector3			GetVectorRotateXYZ(void);


	CVector3			GetVectorRotateXYZ(const CVector3& vector);

	/*!
		*  @brief		ベクトルを座標軸周りで回転させる
		*
		*  @param[in]	axis          回転軸になる座標軸の種類
		*  @param[in]	degree_angle  回転させる角度（度数法）
		*
		*  @return		回転後のベクトル
		*/
	CVector3			RotateAroundCoordinatesAxis(COORDINATES_AXIS axis, float degree_angle);

	/*!
		*  @brief		方向にブレを持たせる
		*
		*  @param[in]	direction    方向
		*
		*  @param[in]	deviation    偏差の大きさ
		*
		*  @return		ブレを持った向き
		 */
	static CVector3     DeviationToDirection(const CVector3& direction, float deviationAmount);

	/*!
	 *  @brief			ランダムな偏差を生成
	 *
	 *  @param[in]		deviation    偏差の大きさ
	 *
	 *  @return			ブレの値
	 */
	static CVector3     GetRandomDeviation(float deviationAmount);

	static const CVector3   ZERO;   //!< 成分がすべて0のベクトル
	static const CVector3   ONE;    //!< 成分がすべて1のベクトル
	static const CVector3   UP;		//!< 成分が0,1,0のベクトル
	static const CVector3   DOWN;	//!< 成分が0,-1,0のベクトル
	static const CVector3   FORWARD;//!< 成分が0,0,1のベクトル
	static const CVector3   BACK;   //!< 成分が0,0,-1のベクトル
	static const CVector3   RIGHT;	//!< 成分が1,0,0のベクトル
	static const CVector3   LEFT;   //!< 成分が-1,0,0のベクトル
};

/*!
	*  @brief			正符号演算子のオーバーロード
	*
	*  @param[in]		v   ベクトルクラス
	*
	*  @return			ベクトルクラス
	*/
CVector3				operator+(const CVector3& v);

/*!
	*  @brief			負符号演算子のオーバーロード
	*
	*  @param[in]		v   ベクトルクラス
	*
	*  @return			ベクトルクラス
	*/
CVector3				operator-(const CVector3& v);

/*!
	*  @brief			加算演算子のオーバーロード
	*
	*  @param[in]		vA  ベクトルクラス
	*  @param[in]		vB  ベクトルクラス
	*
	*  @return			ベクトルクラス
	*/
CVector3				operator+(const CVector3& vA, const CVector3& vB);

/*!
	*  @brief			減算演算子のオーバーロード
	*
	*  @param[in]		vA  ベクトルクラス
	*  @param[in]		vB  ベクトルクラス
	*
	*  @return			ベクトルクラス
	*/
CVector3				operator-(const CVector3& vA, const CVector3& vB);

/*!
	*  @brief			乗算演算子のオーバーロード
	*
	*  @param[in]		vA  ベクトルクラス
	*  @param[in]		vB  ベクトルクラス
	*
	*  @return			ベクトルクラス
	*/
CVector3				operator*(const CVector3& vA, const CVector3& vB);

/*!
	*  @brief			乗算演算子のオーバーロード
	*
	*  @param[in]		v       ベクトルクラス
	*  @param[in]		scalar  スカラー値
	*
	*  @return			ベクトルクラス
	*/
CVector3				operator*(const CVector3& v, float scalar);

/*!
	*  @brief			乗算演算子のオーバーロード
	*
	*  @param[in]		scalar  スカラー値
	*  @param[in]		v       ベクトルクラス
	*
	*  @return			ベクトルクラス
	*/
CVector3				operator*(float scalar, const CVector3& v);

