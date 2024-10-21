#pragma once

#include "vivid.h"
#include "model_id.h"
#include "..\..\..\..\utility\utility.h"

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
	 *  @param[in]  position    �ʒu
	 */
	void    Initialize(const std::string& file_name, const CVector3& position);

	void    Initialize(const std::string& file_name, const CTransform& transform);

	void	Load(const std::string& file_name);

	void	Unload(void);

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

	bool CheckHitLine(const CVector3& startPos, const CVector3& endPos);
	CVector3 GetHitLinePosition(const CVector3& startPos, const CVector3& endPos);
private:
	int			m_Handle;			//!< �n���h��

	CTransform m_Transform;
};