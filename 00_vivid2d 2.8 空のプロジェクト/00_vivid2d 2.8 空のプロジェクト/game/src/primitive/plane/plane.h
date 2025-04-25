#pragma once
#include "vivid.h"
#include "..\..\mathematics\mathematics.h"
#include "..\..\utility\utility.h"


class CPlane
{
public:

	CPlane();

	~CPlane();

	/*!
	 *  @brief      �����ݒ�
	 *  @param[in]	fileName	�摜�̃t�@�C����
	 */
	void SetUp(const std::string fileName);

	void _Draw();

	/*!
	 *  @brief      �s���n���ĕ`�悷��
	 *  @param[in]	mat	�s��
	 */
	void Draw(const CMatrix& mat);

	/*!
	 *  @brief      ���
	 */
	void Finalize();

	/*!
	 *  @brief      �g�����X�t�H�[���̐ݒ�
	 *  @param[in]	transform	�g�����X�t�H�[��
	 */
	void	SetTransform(const CTransform& transform);

private:

	static const unsigned short m_index[];
	CTransform					m_Transform;
	int							m_Handle;
	DxLib::COLOR_U8				m_Color;
	int							m_Width;
	int							m_Height;
	CVector3					m_Normal;

};