#pragma once
#include "../../core/component/component.h"
#include "../../mathematics/mathematics.h"
#include "collision_result.h"
class ColliderComponent : public IComponent
{
public:
    ColliderComponent();
    virtual ~ColliderComponent() = default;

    /*!
     * @brief �w�肳�ꂽ���C���Ƃ̓����蔻����`�F�b�N
     * 
     * @param[in] startPos ���C���̊J�n���W
     * @param[in] endPos ���C���̏I�����W
     * @param[out] out_hitPosition �Փ˂����ʒu���i�[
     * 
     * @return �Փ˂����ꍇ�� true
     */
    virtual bool CheckHitLine( const CVector3& startPos, const CVector3& endPos, CollisionResult& out_result = CollisionResult()) const = 0;

    /*!
	 *  @brief �w�肳�ꂽ�ʒu�Ɣ��a�̋��Ƃ̓����蔻����`�F�b�N
     * 
	 *  @param[in] center ���̒��S���W
	 *  @param[in] radius ���̔��a
	 *  @param[out] out_result �Փˌ��ʂ��i�[
     */
    virtual bool CheckHitSphere(const CVector3& center, float radius, CollisionResult& out_result) const = 0;

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
    virtual bool CheckHitCapsule(const CVector3& posA, const CVector3& posB, float radius, CVector3& out_hitPosition) const = 0;

    /*!
     * @brief �����蔻�肪�L�����ǂ�����ݒ�
     * 
	 * @param[in] isEnabled �L�����ǂ����̃t���O
     */
    void SetEnabled(bool isEnabled);

    /*!
     * @brief �����蔻�肪���ݗL�����ǂ������擾
     * 
	 * @return true : �L��, false : ����
     */
    bool IsEnabled() const;
protected:
	bool m_IsEnabled;   //!< �����蔻�肪�L�����ǂ���
};