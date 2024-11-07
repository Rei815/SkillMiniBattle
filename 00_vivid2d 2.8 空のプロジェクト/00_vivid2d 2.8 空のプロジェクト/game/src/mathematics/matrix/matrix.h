#pragma once
#include "DxLib.h"
class CMatrix : public DxLib::MATRIX
{
public:
	CMatrix();

	/*!
		*  @brief  �R���X�g���N�^
		*
		*  @param[in]  m  �s��
		*/
	CMatrix(const DxLib::MATRIX& m);

	~CMatrix();


	static CMatrix	GetIdentity(CMatrix& m);

	void	SetTranspose();

	void	SetInverse();

	CMatrix	CreateTranspose(const CMatrix& m);

	CMatrix	CreateInverse(const CMatrix& m);

	/*!
		*  @brief      ������Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  m   �}�g���b�N�X�N���X
		*
		*  @return     �}�g���b�N�X�N���X
		*/
	CMatrix& operator=(const CMatrix& m);

	/*!
		*  @brief      ���Z���Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  m   �}�g���b�N�X�N���X
		*
		*  @return     �}�g���b�N�X�N���X
		*/
	CMatrix& operator+=(const CMatrix& m);

	/*!
		*  @brief      ��Z���Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  scale  �X�P�[�����O�l
		*
		*  @return    �}�g���b�N�X�N���X
		*/
	CMatrix     operator*=(float scale);

	/*!
		*  @brief      ��Z���Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  m  �}�g���b�N�X�N���X
		*
		*  @return    �}�g���b�N�X�N���X
		*/
	CMatrix     operator*=(const CMatrix* m);

	/*!
		*  @brief      ���Z���Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  mA  �}�g���b�N�X�N���X
		*  @param[in]  mB  �}�g���b�N�X�N���X
		*
		*  @return     �}�g���b�N�X�N���X
		*/
	friend CMatrix     operator+(const CMatrix& vA, const CMatrix& vB);

	/*!
		*  @brief      ��Z���Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  m  �}�g���b�N�X�N���X
		*  @param[in]  scale  �X�P�[�����O�l
		*
		*  @return    �}�g���b�N�X�N���X
		*/
	friend CMatrix     operator*(const CMatrix& m, float scale);

	/*!
		*  @brief      ��Z���Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  mA  �}�g���b�N�X�N���X
		*  @param[in]  mB  �}�g���b�N�X�N���X
		*
		*  @return    �}�g���b�N�X�N���X
		*/
	friend CMatrix     operator*(const CMatrix& mA, const CMatrix& mB);

private:
};