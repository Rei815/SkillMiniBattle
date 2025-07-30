#pragma once
#include "../../core/component/component.h"
#include "../../mathematics/mathematics.h"
#include "../../utility/transform/transform.h"

class TransformComponent : public IComponent
{
public:

    /*!
	 *  @brief      �R���X�g���N�^
     */
    TransformComponent();

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~TransformComponent() override = default;

    /*!
	 *  @brief      �X�V
     * 
	 *  @param[in] delta_time �O�t���[������̌o�ߎ���
	 *  @param[in] owner      �R���|�[�l���g���A�^�b�`�����I�[�i�[�I�u�W�F�N�g
     */
    void Update(float delta_time, CGameObject* owner) override {}

    // --- �Q�b�^�[ / �Z�b�^�[ ---
    const CTransform& GetTransform() const { return m_Transform; }
    void SetTransform(const CTransform& transform);

    const CVector3& GetPosition() const { return m_Transform.position; }
    const CVector3& GetRotation() const { return m_Transform.rotation; }
    const CVector3& GetScale() const { return m_Transform.scale; }
    void SetPosition(const CVector3& position);
    void SetRotation(const CVector3& euler_angles);
    void SetScale(const CVector3& scale);
    void SetScale(float scale);

    /*!
	 *  @brief      �I�t�Z�b�g�������Ĉʒu��ύX
     *  
	 *  @param[in] offset �ʒu��ύX���邽�߂̃I�t�Z�b�g
     */
    void Translate(const CVector3& offset);

	/*!
	 *  @brief      ���[���h�s����擾
	 *
	 *  @return     ���[���h�s��
	 */
    const CMatrix&  GetWorldMatrix() const;

    /*!
	 *  @brief      ���[���h���W�n�ł̒������擾
     */
    float GetLength() const;
private:
    // --- �������� ---
    void RecalculateWorldMatrix() const;

private:
	CTransform m_Transform;         //!< �g�����X�t�H�[��

	mutable CMatrix m_WorldMatrix;  //!< ���[���h�s��
	mutable bool    m_IsDirty;      //!< ���[���h�s�񂪍Čv�Z���K�v���ǂ����̃t���O
};