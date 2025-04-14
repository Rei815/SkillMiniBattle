#pragma once
class IAnimation
{
public:
	/*!
	 *  @brief      �R���X�g���N�^
	 */
	IAnimation();

	/*!
	 *  @brief      �R���X�g���N�^
	 */
	virtual ~IAnimation();

	/*!
	 *  @brief      ������
	 *
	 *  @param[in]  object_pointer    �A�j���[�V����������I�u�W�F�N�g�̃|�C���^
	*/
	virtual void	Initialize(void* object_pointer) = 0;

	/*!
	 *  @brief      �X�V
	 */
	virtual void	Update(void);

	/*!
	 *  @brief      ���
	 */
	virtual void	Finalize(void);

	/*!
	 *  @brief      �A�N�e�B�u�t���O�擾
	 *
	 *  @return     �A�N�e�B�u�t���O
	 */
	bool            GetActive(void);

	/*!
	 *  @brief      �A�N�e�B�u�t���O�ݒ�
	 *
	 *  @param[in]  active  �A�N�e�B�u�t���O
	 */
	void            SetActive(bool active);

	/*!
	 *  @brief      �I���t���O�擾
	 *
	 *  @return     �I���t���O
	 */
	bool            GetFinishFlag(void);

	/*!
	 *  @brief      �I���t���O�ݒ�
	 *
	 *  @param[in]  finish  �I���t���O
	 */
	void            SetFinishFlag(bool finish);

	/*!
	 *  @brief      �A�N�e�B�u�t���O�ݒ�
	 *
	 *  @param[in]  active  �A�N�e�B�u�t���O
	 */
	void            SetEndPosition(bool active);

protected:
	
	bool            m_ActiveFlag;   //!< �A�N�e�B�u�t���O
	bool			m_FinishFlag;
};