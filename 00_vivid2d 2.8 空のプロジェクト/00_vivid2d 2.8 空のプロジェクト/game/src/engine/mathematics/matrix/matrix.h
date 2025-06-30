#pragma once
#include "DxLib.h"

class CVector3;

class CMatrix : public DxLib::MATRIX
{
public:

	CMatrix();

	/*!
		*  @brief  コンストラクタ
		*
		*  @param[in]  m  行列
		*/
	CMatrix(const DxLib::MATRIX& mat);

	~CMatrix();


	static CMatrix	GetIdentity(CMatrix& mat);

	CMatrix	CreateTranspose(const CMatrix& mat);

	CMatrix	CreateInverse(const CMatrix& mat);

	/*!
		*  @brief      代入演算子のオーバーロード
		*
		*  @param[in]  m   マトリックスクラス
		*
		*  @return     マトリックスクラス
		*/
	CMatrix& operator=(const CMatrix& mat);

	/*!
		*  @brief      加算演算子のオーバーロード
		*
		*  @param[in]  m   マトリックスクラス
		*
		*  @return     マトリックスクラス
		*/
	CMatrix& operator+=(const CMatrix& mat);

	/*!
		*  @brief      乗算演算子のオーバーロード
		*
		*  @param[in]  scale  スケーリング値
		*
		*  @return    マトリックスクラス
		*/
	CMatrix&     operator*=(float scale);

	/*!
		*  @brief      乗算演算子のオーバーロード
		*
		*  @param[in]  m  マトリックスクラス
		*
		*  @return    マトリックスクラス
		*/
	CMatrix&     operator*=(const CMatrix& mat);

	/*!
		*  @brief      加算演算子のオーバーロード
		*
		*  @param[in]  mA  マトリックスクラス
		*  @param[in]  mB  マトリックスクラス
		*
		*  @return     マトリックスクラス
		*/
	friend CMatrix     operator+(const CMatrix& vA, const CMatrix& vB);

	/*!
		*  @brief      乗算演算子のオーバーロード
		*
		*  @param[in]  m  マトリックスクラス
		*  @param[in]  scale  スケーリング値
		*
		*  @return    マトリックスクラス
		*/
	friend CMatrix     operator*(const CMatrix& m, float scale);

	/*!
		*  @brief      乗算演算子のオーバーロード
		*
		*  @param[in]  mA  マトリックスクラス
		*  @param[in]  mB  マトリックスクラス
		*
		*  @return    マトリックスクラス
		*/
	friend CMatrix     operator*(const CMatrix& mA, const CMatrix& mB);

	friend CVector3		operator*(const CMatrix& mat, const CVector3& v);
	friend CVector3		operator*(const CVector3& v, const CMatrix& mat);

	static CMatrix Translate(const CVector3& translate);
	static CMatrix Rotate(const CVector3& rotate);
	static CMatrix Scale(const CVector3& scale);
private:
};