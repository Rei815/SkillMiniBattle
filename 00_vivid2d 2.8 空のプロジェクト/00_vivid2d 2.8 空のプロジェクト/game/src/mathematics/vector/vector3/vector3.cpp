#include "Vector3.h"
#include <corecrt_math.h>
#include <random>

const CVector3 CVector3::ZERO = CVector3(0.0f, 0.0f, 0.0f);
const CVector3 CVector3::ONE = CVector3(1.0f, 1.0f, 1.0f);
const CVector3 CVector3::UP = CVector3(0.0f, 1.0f, 0.0f);
const CVector3 CVector3::FORWARD = CVector3(0.0f, 0.0f, 1.0f);
const CVector3 CVector3::BACK = CVector3(0.0f, 0.0f, -1.0f);
const CVector3 CVector3::RIGHT = CVector3(1.0f, 0.0f, 0.0f);
const CVector3 CVector3::LEFT = CVector3(-1.0f, 0.0f, 0.0f);

/*
* コンストラクタ
*/
CVector3::CVector3(void)
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

/*
* コンストラクタ
*/
CVector3::CVector3(float xVal, float yVal, float zVal)
{
	x = xVal;
	y = yVal;
	z = zVal;
}

/*
* コンストラクタ
*/
CVector3::CVector3(const DxLib::VECTOR& v)
	: CVector3(v.x, v.y, v.z)
{
}

/*
* デストラクタ
*/
CVector3::~CVector3()
{
}

/*
 *  正規化
 */
CVector3 CVector3::Normalize(void)
{
	return Normalize(*this);
}

/*
 *  正規化
 */
CVector3 CVector3::Normalize(const CVector3& v)
{
#if 0
	CVector3 t = v;

	float inv = 1.0f / t.Length();

	t.x *= inv;
	t.y *= inv;
	t.z *= inv;

	return t;
#else
	return VNorm(v);
#endif
}

/*
 *  ベクトルの大きさ取得
 */
float CVector3::Length(void)
{
	return Length(*this);
}

/*
 *  ベクトルの大きさ取得
 */
float CVector3::Length(const CVector3& v)
{
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

/*
 *  内積
 */
float CVector3::Dot(const CVector3& vA, const CVector3& vB)
{
	return (vA.x * vB.x + vA.y * vB.y + vA.z * vB.z);
}

/*
 *  外積
 */
CVector3 CVector3::Cross(const CVector3& vA, const CVector3& vB)
{
	return CVector3(vA.y * vB.z - vA.z * vB.y,vA.z * vB.x - vA.x * vB.z,vA.x * vB.y - vA.y * vB.x);
}

/*
 *  線形補間
 */
CVector3 CVector3::Lerp(const CVector3& start, const CVector3& end, float t)
{
	return (1 - t) * start + t * end;
}
CVector3& CVector3::operator=(const CVector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

/*
 *  加算演算子のオーバーロード
 */
CVector3& CVector3::operator+=(const CVector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}

/*
 *  減算演算子のオーバーロード
 */
CVector3& CVector3::operator-=(const CVector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}

/*
 *  乗算演算子のオーバーロード
 */
CVector3& CVector3::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

CVector3& CVector3::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}

/*
 *  等価演算子のオーバーロード
 */
bool CVector3::operator==(const CVector3& v) const
{
	return (x == v.x && y == v.y && z == v.z);
}

/*
 *  不等演算子のオーバーロード
 */
bool CVector3::operator!=(const CVector3& v) const
{
	return (x != v.x || y != v.y || z != v.z);
}

/*
 *  正符号演算子のオーバーロード
 */
CVector3 operator+(const CVector3& v)
{
	return v;
}

/*
 *  負符号演算子のオーバーロード
 */
CVector3 operator-(const CVector3& v)
{
	return CVector3(-v.x, -v.y, -v.z);
}

/*
 *  加算演算子のオーバーロード
 */
CVector3 operator+(const CVector3& vA, const CVector3& vB)
{
	return CVector3(vA.x + vB.x, vA.y + vB.y, vA.z + vB.z);
}

/*
 *  減算演算子のオーバーロード
 */
CVector3 operator-(const CVector3& vA, const CVector3& vB)
{
	return CVector3(vA.x - vB.x, vA.y - vB.y, vA.z - vB.z);
}

/*
 *  乗算演算子のオーバーロード
 */
CVector3 operator*(const CVector3& vA, const CVector3& vB)
{
	return CVector3(vA.x * vB.x, vA.y * vB.y, vA.z * vB.z);
}

/*
 *  乗算演算子のオーバーロード
 */
CVector3 operator*(const CVector3& v, float scalar)
{
	return CVector3(v.x * scalar, v.y * scalar, v.z * scalar);
}

/*
 *  乗算演算子のオーバーロード
 */
CVector3 operator*(float scalar, const CVector3& v)
{
	return CVector3(v.x * scalar, v.y * scalar, v.z * scalar);
}


CVector3 CVector3::DeviationToDirection(const CVector3& direction, float deviationAmount)
{
	CVector3 deviation = GetRandomDeviation(deviationAmount);

	return direction + deviation;
}
CVector3 CVector3::GetRandomDeviation(float deviationAmount)
{
	static std::random_device rd;

	static std::mt19937 gen(rd());

	std::uniform_real_distribution<float> dis(-deviationAmount, deviationAmount);

	return CVector3(dis(gen), dis(gen), dis(gen));
}

