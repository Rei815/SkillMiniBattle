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
const CVector3 CVector3::DOWN = CVector3(0.0f, -1.0f, 0.0f);

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
	CVector3 t = v;

	float inv = 1.0f / t.Length();

	t.x *= inv;
	t.y *= inv;
	t.z *= inv;

	return t;
	//return VNorm(v);
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

CVector3& CVector3::operator=(const float f)
{
	x = f;
	y = f;
	z = f;
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

CVector3& CVector3::operator*=(const CVector3& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;

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

CVector3 operator+(const CVector3& vA, float f)
{
	return CVector3(vA.x + f, vA.y + f, vA.z + f);
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

CVector3 CVector3::GetVectorRotateXYZ(void)
{
	return GetVectorRotateXYZ(*this);
}

CVector3 CVector3::GetVectorRotateXYZ(const CVector3& vector)
{
	const float math_pi = 3.1415926535897931;

	CVector3 Rotate;

	float cos;
	float rot;
	CVector3 TempVector;

	//Y軸回転
	TempVector = CVector3(vector.x, 0, vector.z).Normalize();
	cos = Dot(CVector3().FORWARD, TempVector);
	rot = acos(cos) * 180.0f / math_pi;
	if (Cross(CVector3().FORWARD, TempVector).y > 0)
	{
		rot = abs(rot);
	}
	else
	{
		rot = -(abs(rot));
	}
	Rotate.y = rot;

	//X軸回転
	TempVector = CVector3(0, vector.y, vector.z).Normalize();
	cos = Dot(CVector3().FORWARD, TempVector);
	rot = acos(cos) * 180.0f / math_pi;
	if (Cross(CVector3().FORWARD, TempVector).x < 0)
	{
		rot = abs(rot);
	}
	else
	{
		rot = -(abs(rot));
	}
	Rotate.x = rot;

	return Rotate;
}

CVector3 CVector3::RotateAroundCoordinatesAxis(COORDINATES_AXIS axis, float degree_angle)
{
	const float math_pi = 3.1415926535897931;

	//degree_angle（度数法の角度）が『-180度 <= degree_angle <= 180度』になるように修正する
	while (degree_angle > 180.0f)
		degree_angle -= 360.0f;
	while (degree_angle < -180.0f)
		degree_angle += 360.0f;

	//degree_angle（度数法の角度）から、弧度法の角度を求めてradianにセットする
	float radian = -degree_angle / 180.0f * math_pi;

	//回転させるために、各要素のベクトルに分解する
	CVector3 TempVectorX = CVector3(x,0,0);
	CVector3 TempVectorY = CVector3(0,y,0);
	CVector3 TempVectorZ = CVector3(0,0,z);

	switch (axis)
	{
	case X:		//X軸回転なので、YベクトルとZベクトルを回転させる
		TempVectorY = CVector3(0.0f, y * cos(radian), -y * sin(radian));
		TempVectorZ = CVector3(0.0f, z * sin(radian), z * cos(radian));
		break;
	case Y:		//Y軸回転なので、ZベクトルとXベクトルを回転させる
		TempVectorZ = CVector3(-z * sin(radian), 0.0f, z * cos(radian));
		TempVectorX = CVector3(x * cos(radian), 0.0f, x * sin(radian));
		break;
	case Z:		//Z軸回転なので、XベクトルとYベクトルを回転させる
		TempVectorX = CVector3(x * cos(radian), -x * sin(radian), 0.0f);
		TempVectorY = CVector3(y * sin(radian), y * cos(radian), 0.0f);
		break;
	default:
		break;
	}

	//回転させた各要素のベクトルを合成する
	return (TempVectorX + TempVectorY + TempVectorZ);
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

