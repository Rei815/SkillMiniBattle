#pragma once
#include "../../../../engine/core/component/component.h"
#include "../gimmick_component.h"
#include <memory>

class CDarumaFallDownGimmick;

class DarumaFallDownGimmickComponent : public GimmickComponent
{
public:

    /*!
     *  @brief      �R���X�g���N�^
     */
    DarumaFallDownGimmickComponent();

	/*!
	 *  @brief      �f�X�g���N�^
	 */
    ~DarumaFallDownGimmickComponent();
    
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
	 *  @brief      �S�̐U�����
	 */
    void OgreControlTurn();
private:
    // ���̃M�~�b�N�̃��W�b�N�����C���X�^���X
    std::unique_ptr<CDarumaFallDownGimmick> m_GimmickLogic;
};