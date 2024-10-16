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
* �R���X�g���N�^
*/
CVector3::CVector3(void)
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

/*
* �R���X�g���N�^
*/
CVector3::CVector3(float xVal, float yVal, float zVal)
{
	x = xVal;
	y = yVal;
	z = zVal;
}

/*
* �R���X�g���N�^
*/
CVector3::CVector3(const DxLib::VECTOR& v)
	: CVector3(v.x, v.y, v.z)
{
}

/*
* �f�X�g���N�^
*/
CVector3::~CVector3()
{
}

/*
 *  ���K��
 */
CVector3 CVector3::Normalize(void)
{
	return Normalize(*this);
}

/*
 *  ���K��
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
 *  �x�N�g���̑傫���擾
 */
float CVector3::Length(void)
{
	return Length(*this);
}

/*
 *  �x�N�g���̑傫���擾
 */
float CVector3::Length(const CVector3& v)
{
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

/*
 *  ����
 */
float CVector3::Dot(const CVector3& vA, const CVector3& vB)
{
	return (vA.x * vB.x + vA.y * vB.y + vA.z * vB.z);
}

/*
 *  �O��
 */
CVector3 CVector3::Cross(const CVector3& vA, const CVector3& vB)
{
	return CVector3(vA.y * vB.z - vA.z * vB.y,vA.z * vB.x - vA.x * vB.z,vA.x * vB.y - vA.y * vB.x);
}

/*
 *  ���`���
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
 *  ���Z���Z�q�̃I�[�o�[���[�h
 */
CVector3& CVector3::operator+=(const CVector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}

/*
 *  ���Z���Z�q�̃I�[�o�[���[�h
 */
CVector3& CVector3::operator-=(const CVector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}

/*
 *  ��Z���Z�q�̃I�[�o�[���[�h
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
 *  �������Z�q�̃I�[�o�[���[�h
 */
bool CVector3::operator==(const CVector3& v) const
{
	return (x == v.x && y == v.y && z == v.z);
}

/*
 *  �s�����Z�q�̃I�[�o�[���[�h
 */
bool CVector3::operator!=(const CVector3& v) const
{
	return (x != v.x || y != v.y || z != v.z);
}

/*
 *  ���������Z�q�̃I�[�o�[���[�h
 */
CVector3 operator+(const CVector3& v)
{
	return v;
}

/*
 *  ���������Z�q�̃I�[�o�[���[�h
 */
CVector3 operator-(const CVector3& v)
{
	return CVector3(-v.x, -v.y, -v.z);
}

/*
 *  ���Z���Z�q�̃I�[�o�[���[�h
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
 *  ���Z���Z�q�̃I�[�o�[���[�h
 */
CVector3 operator-(const CVector3& vA, const CVector3& vB)
{
	return CVector3(vA.x - vB.x, vA.y - vB.y, vA.z - vB.z);
}

/*
 *  ��Z���Z�q�̃I�[�o�[���[�h
 */
CVector3 operator*(const CVector3& vA, const CVector3& vB)
{
	return CVector3(vA.x * vB.x, vA.y * vB.y, vA.z * vB.z);
}

/*
 *  ��Z���Z�q�̃I�[�o�[���[�h
 */
CVector3 operator*(const CVector3& v, float scalar)
{
	return CVector3(v.x * scalar, v.y * scalar, v.z * scalar);
}

/*
 *  ��Z���Z�q�̃I�[�o�[���[�h
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

