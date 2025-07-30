#pragma once
#include "../collider_component.h"
class CGameObject;
class MeshColliderComponent : public ColliderComponent
{
public:

	/*!
	 *  @brief      �R���X�g���N�^
	 */
    MeshColliderComponent();

    /*!
	 *  @brief      �f�X�g���N�^
     */
    ~MeshColliderComponent() = default;

    /*!
	 *  @brief      �A�^�b�`���̏�����
     * 
	 *  @param[in]  owner          �R���|�[�l���g���A�^�b�`�����I�[�i�[�I�u�W�F�N�g
     */
    void OnAttach(CGameObject* owner) override;

    /*!
	 *  @brief      �X�V
     * 
	 *  @param[in]  delta_time     �O�t���[������̌o�ߎ���
	 *  @param[in]  owner          �R���|�[�l���g���A�^�b�`�����I�[�i�[�I�u�W�F�N�g
     */
	void Update(float delta_time, CGameObject* owner) override;

    /*!
	 *  @brief      �����Ǝ������������Ă��邩���`�F�b�N
     * 
	 *  @param[in] startPos    �����̎n�_
	 *  @param[in] endPos      �����̏I�_
	 *  @param[out] out_result �����蔻��̌��ʂ��i�[
     */
    bool CheckHitLine(const CVector3& startPos, const CVector3& endPos, CollisionResult& out_result = CollisionResult()) const override;

    /*!
	 *  @brief	  ���Ǝ������������Ă��邩���`�F�b�N
     *  
	 *  @param[in] center        ���̒��S
	 *  @param[in] radius        ���̔��a
	 *  @param[out] out_result �����蔻��̌��ʂ��i�[
     */
    bool CheckHitSphere(const CVector3& center, float radius, CollisionResult& out_result) const override;

	/*!
	 * @brief �w�肳�ꂽ�ʒu�Ɣ��a�̋��Ƃ̓����蔻����`�F�b�N
	 *
	 * @param[in] posA �J�v�Z���̈�[�̈ʒu
	 * @param[in] posB �J�v�Z���̂�����[�̈ʒu
	 * @param[in] radius �J�v�Z���̔��a
	 * @param[out] out_hitPosition �Փ˂����ʒu���i�[
	 *
	 * @return �Փ˂����ꍇ�� true
	 */
    bool CheckHitCapsule(const CVector3& posA, const CVector3& posB, float radius, CVector3& out_hitPosition) const override;

private:

	int m_ModelHandle; //!< ���f���n���h��
};