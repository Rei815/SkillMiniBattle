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
	 *  @brief      ������(�������z�֐��̂��ߔh����Œ�`)
	 *
	*/
	virtual void	Initialize() = 0;

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
	bool            IsActive(void);

	/*!
	 *  @brief      �A�N�e�B�u�t���O�ݒ�
	 *
	 *  @param[in]  active  �A�N�e�B�u�t���O
	 */
	void            SetActive(bool active);

protected:
	
	bool            m_ActiveFlag;   //!< �A�N�e�B�u�t���O
};