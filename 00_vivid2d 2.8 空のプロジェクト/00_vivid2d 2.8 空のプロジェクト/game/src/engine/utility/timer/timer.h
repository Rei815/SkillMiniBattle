#pragma once

/*!
 *  @brief  �^�C�}�[�N���X
 */
class CTimer
{
public:

	enum class COUNT_TYPE
	{
		UP,		//!< �J�E���g�A�b�v
		DOWN	//!< �J�E���g�_�E��
	};

	/*!
	 *  @brief  �R���X�g���N�^
	 */
	CTimer();

	/*!
	 *  @brief  �R���X�g���N�^
	 */
	CTimer(float time);

	/*!
	 *  @brief  �f�X�g���N�^
	 */
	~CTimer();

	/*!
	 *  @brief  ������
	 */
	void Initialize();

	/*!
	 *  @brief  �^�C�}�[�̐ݒ�
	 * 
	 *  @param[in] limit_time	��������			
	 *  @param[in] count_type	�J�E���g���@
	 */
	void SetUp(float limit_time, COUNT_TYPE count_type = COUNT_TYPE::UP);

	/*!
	 *  @brief  �X�V
	 */
	void Update();

	/*!
	 *  @brief  �^�C�}�[�����Z�b�g
	 */
	void Reset();

	/*!
	 *  @brief  �J�E���g���I�����Ă��邩
	 * 
	 *  @return	bool true �I�� false ���I��
	 */
	bool Finished() const;

	/*!
	 *  @brief  ���݂̃^�C�}�[���擾
	 *
	 *  @return	float �^�C�}�[
	 */
	float		GetTimer() const;

	/*!
	 *  @brief  �������Ԃ�ݒ�
	 *
	 *  @param[in]	float limit_time�@��������
	 */
	void		SetLimitTime(float limit_time);

	/*!
	 *  @brief �������Ԃ��擾
	 *
	 *  @return	float ��������
	 */
	float		GetLimitTime() const;

	/*!
	 *  @brief  �A�N�e�B�u��Ԃ��擾
	 *
	 *  @return	bool true �A�N�e�B�u false ��A�N�e�B�u
	 */
	bool		IsActive() const;

	/*!
	 *  @brief  �A�N�e�B�u��Ԃ�ݒ�
	 *
	 *  @param[in]	bool true �A�N�e�B�u false ��A�N�e�B�u
	 */
	void		SetActive(bool active);

private:
	float		m_LimitTime;	//!< ��������
	float		m_StartTime;	//!< �J�n���̎���(�J�E���g�_�E����)
	float		m_Timer;		//!< �^�C�}�[
	bool		m_Active;		//!< �A�N�e�B�u���
	COUNT_TYPE	m_CountType;	//!< �J�E���g���@
};