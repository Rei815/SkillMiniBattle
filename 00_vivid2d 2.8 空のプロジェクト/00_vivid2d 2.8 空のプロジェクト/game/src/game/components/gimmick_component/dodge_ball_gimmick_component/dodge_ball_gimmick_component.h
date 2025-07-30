#pragma once
#include "../../../../engine/core/component/component.h"
#include <memory>
#include "dodge_ball_gimmick/dodge_ball_gimmick.h"

class CDodgeBallGimmick;

class DodgeBallGimmickComponent : public IComponent
{
public:

	/*!
	 *  @brief      �R���X�g���N�^
	 */
    DodgeBallGimmickComponent();

	/*!
	 *  @brief      �f�X�g���N�^
	 */
    ~DodgeBallGimmickComponent();

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

    /*
	 *  @brief      ����t���O��ݒ�
     * 
	 *  @param[in] flag ����t���O
     */
    void SetOperationFlag(bool flag);

	/*!
	 *  @brief      ���݂̏�Ԃ��擾
	 *
	 *  @return     ���݂̏��
	 */
    CANNON_STATE    GetNowState();

	/*
	 *	@brief      �V���b�g�t���O���擾
	 */
    bool            GetShotFlag();

private:
    // ���̃M�~�b�N�̃��W�b�N�����C���X�^���X
    std::unique_ptr<CDodgeBallGimmick> m_GimmickLogic;
};