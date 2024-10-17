#pragma once

#include <DxLib.h>
/*!
	*  @brief      �O�����x�N�g���N���X
	*/
class CVector3 : public DxLib::VECTOR
{
public:

	/*!
		*  @brief  �R���X�g���N�^
		*/
	CVector3(void);

	/*!
		*  @brief  �R���X�g���N�^
		*
		*  @param[in]  xVal   X����
		*  @param[in]  yVal   Y����
		*  @param[in]  zVal   Z����
		*/
	CVector3(float xVal, float yVal, float zVal);

	/*!
		*  @brief  �R���X�g���N�^
		*
		*  @param[in]  v  �x�N�g��
		*/
	CVector3(const DxLib::VECTOR& v);
	/*!
		*  @brief  �f�X�g���N�^
		*/
	~CVector3(void);

	/*!
		*  @brief      �x�N�g���̐��K��<br>
		*              ���g�̃x�N�g�������K�������
		*
		*  @return     ���K�����ꂽ�x�N�g��
		*/
	CVector3            Normalize(void);

	/*!
		*  @brief      �x�N�g���̐��K��
		*
		*  @param[in]  v   �x�N�g���N���X
		*
		*  @return     ���K�����ꂽ�x�N�g��
		*/
	static CVector3     Normalize(const CVector3& v);

	/*!
		*  @brief      �x�N�g���̑傫���擾
		*
		*  @return     �x�N�g���̑傫��
		*/
	float               Length(void);

	/*!
		*  @brief      �x�N�g���̑傫���擾
		*
		*  @param[in]  v   �x�N�g���N���X
		*
		*  @return     �x�N�g���̑傫��
		*/
	static float        Length(const CVector3& v);

	/*!
		*  @brief      2�̃x�N�g���̓���<br>
		*              dot = vA�EvB
		*
		*  @param[in]  vA  �x�N�g���N���X
		*  @param[in]  vB  �x�N�g���N���X
		*
		*  @return     ����
		*/
	static float        Dot(const CVector3& vA, const CVector3& vB);

	/*!
		*  @brief      2�̃x�N�g���̊O��<br>
		*              cross = vA�~vB
		*
		*  @param[in]  vA  �x�N�g���N���X
		*  @param[in]  vB  �x�N�g���N���X
		*
		*  @return     �O��
		*/
	static CVector3        Cross(const CVector3& vA, const CVector3& vB);

	/*!
	*  @brief      ���`���
	*              lerp(a,b,t) = (1 - t) * a + t * b
	*
	*  @param[in]  start  �J�n�_
	*  @param[in]  end  �I���_
	*  @param[in]  t  0����P�܂ł͈̔͂̕�ԃp�����[�^
	*
	*  @return     �ʒu
	*/
	static CVector3        Lerp(const CVector3& start, const CVector3& end, float t);

	/*!
		*  @brief      ������Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  v   �x�N�g���N���X
		*
		*  @return     �x�N�g���N���X
		*/
	CVector3& operator=(const CVector3& v);

	/*!
		*  @brief      ���Z���Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  v   �x�N�g���N���X
		*
		*  @return     �x�N�g���N���X
		*/
	CVector3& operator+=(const CVector3& v);

	/*!
		*  @brief      ���Z���Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  v   �x�N�g���N���X
		*
		*  @return     �x�N�g���N���X
		*/
	CVector3& operator-=(const CVector3& v);

	/*!
		*  @brief      ��Z���Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  scalar  �X�J���[�l
		*
		*  @return     �x�N�g���N���X
		*/
	CVector3& operator*=(float scalar);

	/*!
		*  @brief      ���Z���Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  scalar  �X�J���[�l
		*
		*  @return     �x�N�g���N���X
		*/
	CVector3& operator/=(float scalar);

	/*!
		*  @brief      �������Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  v   �x�N�g���N���X
		*
		*  @return     ��̃x�N�g����������
		*  @retval     true    ������
		*  @retval     false   �������Ȃ�
		*/
	bool                operator==(const CVector3& v) const;

	/*!
		*  @brief      �s�����Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  v   �x�N�g���N���X
		*
		*  @return     ��̃x�N�g�����������Ȃ�
		*  @retval     true    �������Ȃ�
		*  @retval     false   ������
		*/
	bool                operator!=(const CVector3& v) const;

	/*!
		*  @brief      ���������Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  v   �x�N�g���N���X
		*
		*  @return     �x�N�g���N���X
		*/
	friend CVector3     operator+(const CVector3& v);

	/*!
		*  @brief      ���������Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  v   �x�N�g���N���X
		*
		*  @return     �x�N�g���N���X
		*/
	friend CVector3     operator-(const CVector3& v);

	/*!
		*  @brief      ���Z���Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  vA  �x�N�g���N���X
		*  @param[in]  vB  �x�N�g���N���X
		*
		*  @return     �x�N�g���N���X
		*/
	friend CVector3     operator+(const CVector3& vA, const CVector3& vB);

	/*!
		*  @brief      ���Z���Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  v  �x�N�g���N���X
		*  @param[in]  f  float�^
		*
		*  @return     �x�N�g���N���X
		*/
	friend CVector3     operator+(const CVector3& vA, float f);

	/*!
		*  @brief      ���Z���Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  vA  �x�N�g���N���X
		*  @param[in]  vB  �x�N�g���N���X
		*
		*  @return     �x�N�g���N���X
		*/
	friend CVector3     operator-(const CVector3& vA, const CVector3& vB);

	/*!
		*  @brief      ��Z���Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  vA  �x�N�g���N���X
		*  @param[in]  vB  �x�N�g���N���X
		*
		*  @return     �x�N�g���N���X
		*/
	friend CVector3     operator*(const CVector3& vA, const CVector3& vB);

	/*!
		*  @brief      ��Z���Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  v       �x�N�g���N���X
		*  @param[in]  scalar  �X�J���[�l
		*
		*  @return     �x�N�g���N���X
		*/
	friend CVector3     operator*(const CVector3& v, float scalar);

	/*!
		*  @brief      ��Z���Z�q�̃I�[�o�[���[�h
		*
		*  @param[in]  scalar  �X�J���[�l
		*  @param[in]  v       �x�N�g���N���X
		*
		*  @return     �x�N�g���N���X
		*/
	friend CVector3     operator*(float scalar, const CVector3& v);


	/*!
	 *  @brief      ���˕����Ƀu������������
	 *
	 *  @param[in]  direction    ���˕���
	 *
	 *  @param[in]  deviation    �΍��̑傫��
	 *
	 *  @return     �u��������������
	 */
	static CVector3        DeviationToDirection(const CVector3& direction, float deviationAmount);

	/*!
	 *  @brief      �����_���ȕ΍��𐶐�
	 *
	 *  @param[in]  deviation    �΍��̑傫��
	 *
	 *  @return     �u���̒l
	 */
	static CVector3        GetRandomDeviation(float deviationAmount);

	static const CVector3   ZERO;   //!< ���������ׂ�0�̃x�N�g��
	static const CVector3   ONE;    //!< ���������ׂ�1�̃x�N�g��
	static const CVector3   UP;		//!< ������0,1,0�̃x�N�g��
	static const CVector3   DOWN;	//!< ������0,-1,0�̃x�N�g��
	static const CVector3   FORWARD;//!< ������0,0,1�̃x�N�g��
	static const CVector3   BACK;   //!< ������0,0,-1�̃x�N�g��
	static const CVector3   RIGHT;	//!< ������1,0,0�̃x�N�g��
	static const CVector3   LEFT;   //!< ������-1,0,0�̃x�N�g��
};

/*!
	*  @brief      ���������Z�q�̃I�[�o�[���[�h
	*
	*  @param[in]  v   �x�N�g���N���X
	*
	*  @return     �x�N�g���N���X
	*/
CVector3     operator+(const CVector3& v);

/*!
	*  @brief      ���������Z�q�̃I�[�o�[���[�h
	*
	*  @param[in]  v   �x�N�g���N���X
	*
	*  @return     �x�N�g���N���X
	*/
CVector3     operator-(const CVector3& v);

/*!
	*  @brief      ���Z���Z�q�̃I�[�o�[���[�h
	*
	*  @param[in]  vA  �x�N�g���N���X
	*  @param[in]  vB  �x�N�g���N���X
	*
	*  @return     �x�N�g���N���X
	*/
CVector3     operator+(const CVector3& vA, const CVector3& vB);

/*!
	*  @brief      ���Z���Z�q�̃I�[�o�[���[�h
	*
	*  @param[in]  vA  �x�N�g���N���X
	*  @param[in]  vB  �x�N�g���N���X
	*
	*  @return     �x�N�g���N���X
	*/
CVector3     operator-(const CVector3& vA, const CVector3& vB);

/*!
	*  @brief      ��Z���Z�q�̃I�[�o�[���[�h
	*
	*  @param[in]  vA  �x�N�g���N���X
	*  @param[in]  vB  �x�N�g���N���X
	*
	*  @return     �x�N�g���N���X
	*/
CVector3     operator*(const CVector3& vA, const CVector3& vB);

/*!
	*  @brief      ��Z���Z�q�̃I�[�o�[���[�h
	*
	*  @param[in]  v       �x�N�g���N���X
	*  @param[in]  scalar  �X�J���[�l
	*
	*  @return     �x�N�g���N���X
	*/
CVector3     operator*(const CVector3& v, float scalar);

/*!
	*  @brief      ��Z���Z�q�̃I�[�o�[���[�h
	*
	*  @param[in]  scalar  �X�J���[�l
	*  @param[in]  v       �x�N�g���N���X
	*
	*  @return     �x�N�g���N���X
	*/
CVector3     operator*(float scalar, const CVector3& v);

