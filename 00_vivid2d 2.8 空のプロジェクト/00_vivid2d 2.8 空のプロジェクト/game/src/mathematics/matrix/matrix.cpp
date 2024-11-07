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

CMatrix CMatrix::GetIdentity(CMatrix& m)
{
    CreateIdentityMatrix(&m);
    return m;
}

void CMatrix::SetTranspose()
{
    CreateTransposeMatrix(this, this);
}

void CMatrix::SetInverse()
{
    CreateInverseMatrix(this, this);
}
CMatrix CMatrix::CreateTranspose(const CMatrix& m)
{
    CreateTransposeMatrix(this, &m);
    return *this;
}


CMatrix CMatrix::CreateInverse(const CMatrix& m)
{
    CreateInverseMatrix(this, &m);
    return *this;
}

CMatrix& CMatrix::operator=(const CMatrix& mat)
{
    for (int i = 0; i < 4; ++i)
        for (int k = 0; k < 4; ++k)
            m[i][k] = mat.m[i][k];
    return *this;
}

CMatrix& CMatrix::operator+=(const CMatrix& m)
{
    return *this = MAdd(*this, m);
}

CMatrix CMatrix::operator*=(float scale)
{
    return *this = MScale(*this, scale);
}

CMatrix CMatrix::operator*=(const CMatrix* m)
{
    CreateMultiplyMatrix(this, this, m);
    return *this;
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
