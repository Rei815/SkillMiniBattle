#pragma once
#include "../../../../engine/core/component/component.h"
#include <memory>

class CBeltConveyorGimmick;

class BeltConveyorGimmickComponent : public IComponent
{
public:

	/*!
	 *  @brief      �R���X�g���N�^
	 */
    BeltConveyorGimmickComponent();

	/*!
	 *  @brief      �f�X�g���N�^
	 */
    ~BeltConveyorGimmickComponent();

	/*!
	 *  @brief      �A�^�b�`���̏�����
	 *
	 *  @param[in]  owner          �R���|�[�l���g���A�^�b�`�����I�[�i�[�I�u�W�F�N�g
	 */
    void OnAttach(CGameObject* owner) override;

	/*�I
	 *	@brief      �X�V
	 *	
	 *	@param[in] delta_time �O�t���[������̌o�ߎ���
	 *	@param[in] owner      �R���|�[�l���g���A�^�b�`�����I�[�i�[�I�u�W�F�N�g
	 */
    void Update(float delta_time, CGameObject* owner) override;

private:
    std::unique_ptr<CBeltConveyorGimmick> m_GimmickLogic;
};