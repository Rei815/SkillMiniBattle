#pragma once

#include "vivid.h"
#include "model_id.h"
#include "..\..\..\utility\utility.h"

/*!
 *  @brief      ���f���N���X
 */
class CModel
{
public:

	/*!
	 *  @brief  �R���X�g���N�^
	 */
	CModel();

	/*!
	 *  @brief  �R���X�g���N�^
	 */
	~CModel();

	/*!
	 *  @brief      ������
	 *
	 *  @param[in]  file_name   �t�@�C����
	 *  @param[in]  position    �ʒu
	 *  @param[in]  scale		�傫��
	 */
	void    Initialize(const std::string& file_name, const CVector3& position, float scale = 1.0f);
	void    Initialize(const std::string& file_name, const CVector3& position, const CVector3& scale);

	/*!
	 *  @brief      ������
	 *
	 *  @param[in]  file_name   �t�@�C����
	 *  @param[in]  transform   �g�����X�t�H�[��
	 *  @param[in]  scale		�傫��
	 */
	void    Initialize(const std::string& file_name, const CTransform& transform, float scale = 1.0f);
	void    Initialize(const std::string& file_name, const CTransform& transform, const CVector3& scale);

	/*!
	 *  @brief      ���[�h
	 *
	 *  @param[in]  file_name   �t�@�C����
	 */
	void	Load(const std::string& file_name);

	/*!
	 *  @brief      �A�����[�h
	 */
	void	Unload(void);

	/*!
	 *  @brief      �X�V
	 */
	void    Update(void);

	/*!
	 *  @brief      �X�V
	 */
	void    Update(const CTransform& transform);

	/*!
	 *  @brief      �`��
	 */
	void    Draw(void);

	/*!
	 *  @brief      ���
	 */
	void    Finalize(void);

	/*!
	*  @brief  �n���h���̌Ăяo��
	*/
	int GetModelHandle() const;

	/*!
	*  @brief  �ʒu�ݒ�
	*/
	void SetPosition(const CVector3& position);

	/*!
	*  @brief  ��]�ݒ�
	*/
	void SetRotation(const CVector3& rotation);


	/*!
	 *  @brief      �g��ݒ�
	 * 
	 *  @param[in]  scale   �Z�b�g����g��̔{��
	 */
	void SetScale(float scale);

	/*!
	 *  @brief      �g��ݒ�
	 * 
	 *  @param[in]  scale   �Z�b�g����g��̔{��
	 */
	void SetScale(const CVector3& scale);

	/*!
	 *  @brief      �����Ɠ������Ă��邩���`�F�b�N
	 *
	 *  @param[in]  startPos	�����̊J�n�ʒu
	 *  @param[in]  endPos		�����̍ŏI�ʒu
	 * 
	 *  @return		true �������Ă��� false �������Ă��Ȃ�
	 */
	bool CheckHitLine(const CVector3& startPos, const CVector3& endPos)const;

	/*!
	 *  @brief      �����Ɠ��������ʒu��Ԃ�
	 *
	 *  @param[in]  startPos	�����̊J�n�ʒu
	 *  @param[in]  endPos		�����̍ŏI�ʒu
	 *
	 *  @return		���������ʒu
	 */
	CVector3 GetHitLinePosition(const CVector3& startPos, const CVector3& endPos)const;

	/*!
	 *  @brief      �}�e���A���̃f�B�t���[�Y�J���[���擾
	 *
	 *  @param[in]  material_index  �}�e���A���̔ԍ�
	 * 
	 *  @return		�F(16�i��)
	 */
	unsigned int GetMaterialDif(int material_index);

	/*!
	 *  @brief      �}�e���A���̃f�B�t���[�Y�J���[��ݒ�
	 *
	 *  @param[in]  material_index	�}�e���A���̔ԍ�
	 *  @param[in]  color			�F(16�i��)
	 */
	void	SetMaterialDif(int material_index, unsigned int color);
private:
	int			m_Handle;			//!< �n���h��
	CTransform m_Transform;			//!< �g�����X�t�H�[��
};