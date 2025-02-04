#pragma once

#include "vivid.h"
#include "..\..\..\utility\utility.h"
/*!
*  @brief      �J�����N���X
*/
class CCamera
{
public:

	/*!
	 *  @brief      �C���X�^���X�̎擾
	 *
	 *  @return     �C���X�^���X
	 */
	static CCamera& GetInstance(void);


	/*!
	*  @brief      �J�����̏�����
	*/
	void Initialize();

	/*!
	*  @brief      �J�����̍X�V
	*/
	void Update();


	/*!
	*  @brief      �J�����̉��
	*/
	void Finalize();

	/*!
	*  @brief      �Ǐ]���铮��
	*/
	void Follow(const CVector3& position,const CVector3& offset);

	/*!
	*  @brief      �ʒu�ݒ�
	*/
	void SetPosition(const CVector3& position);

	/*!
	*  @brief      �����ݒ�
	*/
	void SetDirection(const CVector3& direction);

	/*!
	*  @brief      �ʒu�擾
	*/
	CVector3 GetPosition();

	float GetNear();

	float GetFar();

	/*!
	*  @brief      �J������h�炷
	*/
	void Shake();
private:

	/*!
	*  @brief      �J�����̗h��
	*/
	void _Shake();


	/*!
	 *  @brief      �R���X�g���N�^
	 */
	CCamera(void);

	/*!
	 *  @brief      �R�s�[�R���X�g���N�^
	 *
	 *  @param[in]  rhs     �I�u�W�F�N�g
	 */
	CCamera(const CCamera& rhs);

	/*!
	 *  @brief      �f�X�g���N�^
	 */
	~CCamera(void);

	/*!
	 *  @brief      ������Z�q
	 *
	 *  @param[in]  rhs ����I�u�W�F�N�g
	 *
	 *  @return     ���g�̃I�u�W�F�N�g
	 */
	CCamera& operator=(const CCamera& rhs);

	static const float	m_lerp_speed;						//!< �J�����̓����̑���
	static const float	m_near;									//!< Near�N���b�v
	static const float	m_far;										//!< Far�N���b�v
	static const int	m_shake_max_num;				//!< �h����
	static const int	m_shake_interval;					//!< �h��̊Ԋu
	static const float	m_shake_value;						//!< �h��̑傫��
	static const CVector3 m_initial_position;		//!< �����ʒu
	static const CVector3 m_initial_direction;		//!< �����p�x

	CVector3			m_Position;			//!< �ʒu(���_)
	CVector3			m_Direction;		//!< ����
	float				m_Fov;				//!< ����p
	CVector3			m_Offset;			//!< �I�u�W�F�N�g�Ƃ̋���
	CVector3			m_ShakeVector;		//!< �h��̃x�N�g��
	bool				m_ShakeFlag;		//!< �h��t���O
	int					m_ShakeCount;		//!< �h�ꂽ��
	float				m_ShakeTimer;		//!< �h��^�C�}�[
	CVector3			m_PreviousPosition;	//!< �h��O�̈ʒu

};