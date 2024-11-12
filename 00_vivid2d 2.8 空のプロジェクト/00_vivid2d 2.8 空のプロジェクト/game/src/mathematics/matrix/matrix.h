#pragma once
#include "DxLib.h"

class CVector3;

class CMatrix : public DxLib::MATRIX
{
public:

	CMatrix();

	/*!
		*  @brief  �R���X�g���N�^
		*
		*  @param[in]  m  �s��
		*/
	CMatrix(const DxLib::MATRIX& mat);

	~CMatrix();


	static CMatrix	GetIdentity(CMatrix& mat);

	CMatrix	CreateTranspose(const CMatrix& mat);

	CMatrix	CreateInverse(const CMatrix& mat);

	/*!
		*  @brief      ������Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  m   �}�g���b�N�X�N���X
		*
		*  @return     �}�g���b�N�X�N���X
		*/
	CMatrix& operator=(const CMatrix& mat);

	/*!
		*  @brief      ���Z���Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  m   �}�g���b�N�X�N���X
		*
		*  @return     �}�g���b�N�X�N���X
		*/
	CMatrix& operator+=(const CMatrix& mat);

	/*!
		*  @brief      ��Z���Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  scale  �X�P�[�����O�l
		*
		*  @return    �}�g���b�N�X�N���X
		*/
	CMatrix&     operator*=(float scale);

	/*!
		*  @brief      ��Z���Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  m  �}�g���b�N�X�N���X
		*
		*  @return    �}�g���b�N�X�N���X
		*/
	CMatrix&     operator*=(const CMatrix& mat);

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

	friend CVector3		operator*(const CMatrix& mat, const CVector3& v);
	friend CVector3		operator*(const CVector3& v, const CMatrix& mat);

	static CMatrix Translate(const CVector3& translate);
	static CMatrix Rotate(const CVector3& rotate);
	static CMatrix Scale(const CVector3& scale);
private:
};