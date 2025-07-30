#pragma once
#include "../../core/component/component.h"
#include "../../managers/model_manager/model_id.h" // MODEL_ID ���g������
#include "DxLib.h"

class TransformComponent;

class ModelComponent : public IComponent
{

public:

	/*!
	 *  @brief      �R���X�g���N�^
	 *  @param[in]  id             ���f��ID
	 *  @param[in]  IsDuplicate    �����t���O
	 */
    ModelComponent(MODEL_ID id = MODEL_ID::MAX, bool IsDuplicate = false);

	/*!
	 *  @brief      �f�X�g���N�^
	 */
    ~ModelComponent() override = default;

	/*!
	 *  @brief      �A�^�b�`���̏�����
	 *  @param[in]  owner          �R���|�[�l���g���A�^�b�`�����I�[�i�[�I�u�W�F�N�g
	 */
    void OnDetach(CGameObject* owner) override;

    /*!
	 *  @brief      �X�V
     * 
	 *  @param[in]  delta_time     �O�t���[������̌o�ߎ���
	 *  @param[in]  owner          �R���|�[�l���g���A�^�b�`�����I�[�i�[�I�u�W�F�N�g
     */
    void Update(float delta_time, CGameObject* owner) override {};

    /*!
	 *  @brief      �`��
     *  
	 *  @param[in]  owner          �R���|�[�l���g���A�^�b�`�����I�[�i�[�I�u�W�F�N�g
     */
    void Draw(const CGameObject* owner) const;

    /*!
	 *  @brief      ���f���n���h����ݒ�
     *  
	 *  @param[in]  handle ���f���n���h��
     */
    void SetModelHandle(int handle);

	/*!
	 *  @brief      ���f���n���h�����擾
     * 
	 *  @return     ���f���n���h��
     */ 
    int GetHandle() const;

    /*!
	 *  @brief      �}�e���A���̐F��ݒ�
     *  
	 *  @param[in]  material_index �}�e���A���̃C���f�b�N�X
	 *  @param[in]  color          �ݒ肷��F
     */
    void SetMaterialColor(int material_index, const DxLib::COLOR_F& color);

    /*!
	 *  @brief	  �}�e���A���̐F���擾
     *  
	 *  @param[in]  material_index �}�e���A���̃C���f�b�N�X
     * 
	 *  @return     �}�e���A���̐F
     */
    DxLib::COLOR_F GetMaterialColor(int material_index);

	/*!
	 *  @brief      �A���t�@�l��ݒ�
     * 
	 *  @param[in]  alpha �����x�̒l
     */
    void SetAlpha(float alpha);
private:
	int m_ModelHandle;		//!< ���f���̃n���h��
    float m_Alpha;			//!< �����x
	bool m_IsDuplicated;	//!< �����t���O
};