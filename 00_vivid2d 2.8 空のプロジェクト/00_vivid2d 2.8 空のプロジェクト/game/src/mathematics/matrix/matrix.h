#pragma once
#include "DxLib.h"
class CMatrix : public DxLib::MATRIX
{
public:
	CMatrix();

	/*!
		*  @brief  コンストラクタ
		*
		*  @param[in]  m  行列
		*/
	CMatrix(const DxLib::MATRIX& m);

	~CMatrix();


	void	GetIdentity();

	void	SetTranspose();

	void	SetInverse();

	CMatrix	CreateTranspose(const CMatrix& m);

	CMatrix	CreateInverse(const CMatrix& m);

	/*!
		*  @brief      代入演算子のオーバーロード
		*
		*  @param[in]  m   マトリックスクラス
		*
		*  @return     マトリックスクラス
		*/
	CMatrix& operator=(const CMatrix& m);

	/*!
		*  @brief      加算演算子のオーバーロード
		*
		*  @param[in]  m   マトリックスクラス
		*
		*  @return     マトリックスクラス
		*/
	CMatrix& operator+=(const CMatrix& m);

	/*!
		*  @brief      乗算演算子のオーバーロード
		*
		*  @param[in]  scale  スケーリング値
		*
		*  @return    マトリックスクラス
		*/
	CMatrix     operator*=(float scale);

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

private:
};