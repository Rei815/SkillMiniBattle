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
	void    Initialize(const std::string& file_name, const CVector3& position, float scale = 1.0f);
	void    Initialize(const std::string& file_name, const CVector3& position, const CVector3& scale);

	void    Initialize(const std::string& file_name, const CTransform& transform, float scale = 1.0f);
	void    Initialize(const std::string& file_name, const CTransform& transform, const CVector3& scale);

	void	Load(const std::string& file_name);

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

	bool CheckHitLine(const CVector3& startPos, const CVector3& endPos);
	bool CheckHitTriangle(const CVector3& posA, const CVector3& posB, const CVector3& posC);
	CVector3 GetHitLinePosition(const CVector3& startPos, const CVector3& endPos);
	CVector3 GetHitTrianglePosition(const CVector3& posA, const CVector3& posB, const CVector3& posC);

	unsigned int GetMaterialDif(int material_index);

	void	SetMaterialDif(int material_index, unsigned int color);
private:
	int			m_Handle;			//!< �n���h��

	CTransform m_Transform;
};