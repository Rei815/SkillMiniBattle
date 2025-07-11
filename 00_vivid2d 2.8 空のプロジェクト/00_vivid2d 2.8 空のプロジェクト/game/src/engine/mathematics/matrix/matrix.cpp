#include "matrix.h"
#include "..\mathematics.h"
CMatrix::CMatrix()
{
    for (int i = 0; i < 4; ++i)
        for (int k = 0; k < 4; ++k)
            m[i][k] = 0.0f;
}

CMatrix::CMatrix(const DxLib::MATRIX& mat)
{
    for (int i = 0; i < 4; ++i)
        for (int k = 0; k < 4; ++k)
            m[i][k] = mat.m[i][k];
}

CMatrix::~CMatrix()
{
}

CMatrix CMatrix::GetIdentity(CMatrix& mat)
{
    CreateIdentityMatrix(&mat);
    return mat;
}

CMatrix CMatrix::CreateTranspose(const CMatrix& mat)
{
    CreateTransposeMatrix(this, &mat);
    return *this;
}


CMatrix CMatrix::CreateInverse(const CMatrix& mat)
{
    CreateInverseMatrix(this, &mat);
    return *this;
}

CMatrix& CMatrix::operator=(const CMatrix& mat)
{
    for (int i = 0; i < 4; ++i)
        for (int k = 0; k < 4; ++k)
            m[i][k] = mat.m[i][k];
    return *this;
}

CMatrix& CMatrix::operator+=(const CMatrix& mat)
{
    return *this = MAdd(*this, mat);
}

CMatrix& CMatrix::operator*=(float scale)
{
    return *this = MScale(*this, scale);
}

CMatrix& CMatrix::operator*=(const CMatrix& m)
{
    CreateMultiplyMatrix(this, this, &m);
    return *this;
}

CMatrix CMatrix::Translate(const CVector3& translate)
{
    return DxLib::MGetTranslate(translate);
}

CMatrix CMatrix::Rotate(const CVector3& rotate)
{
    // 度数法で受け取った角度をラジアンに変換します
    float radX = rotate.x * DX_PI_F / 180.0f;
    float radY = rotate.y * DX_PI_F / 180.0f;
    float radZ = rotate.z * DX_PI_F / 180.0f;

    // ラジアンに変換した値をDXライブラリの関数に渡します
    return DxLib::MMult(DxLib::MMult(DxLib::MGetRotZ(radZ), DxLib::MGetRotX(radX)), DxLib::MGetRotY(radY));
}

CMatrix CMatrix::Scale(const CVector3& scale)
{
    return DxLib::MGetScale(scale);
}

CMatrix operator+(const CMatrix& mA, const CMatrix& mB)
{
    return MAdd(mA, mB);
}

CMatrix operator*(const CMatrix& m, float scale)
{
    return MScale(m, scale);
}

CMatrix operator*(const CMatrix& mA, const CMatrix& mB)
{
    return MMult(mA, mB);
}

CVector3 operator*(const CMatrix& mat, const CVector3& v)
{
    return DxLib::VTransform(v, mat);
}

CVector3 operator*(const CVector3& v, const CMatrix& mat)
{
    return mat * v;
}
