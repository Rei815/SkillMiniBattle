#pragma once
#include "../../../engine/core/component/component.h"
#include "../../../engine/utility/timer/timer.h"
// �M�~�b�N�̏�Ԃ��`
enum class GIMMICK_STATE
{
    WAIT,
    PLAY,
    FINISH,
};

class GimmickComponent : public IComponent
{
public:
	/*!
	 *  @brief      �R���X�g���N�^
	 */
    GimmickComponent();

	/*!
	 *       @brief      �f�X�g���N�^
     */
    virtual ~GimmickComponent() = default;

    /*!
	 *  @brief      �R���|�[�l���g�̍X�V
     * 
	 *  @param[in] delta_time �O�t���[������̌o�ߎ���
	 *  @param[in] owner      �R���|�[�l���g���A�^�b�`�����I�[�i�[�I�u�W�F�N�g
     */
    void Update(float delta_time, CGameObject* owner) override;

    /*!
	 *  @brief      �M�~�b�N�̏�Ԃ��擾
     */
    GIMMICK_STATE GetState() const { return m_State; }

    /*!
	 *  @brief      �M�~�b�N�̏�Ԃ�ݒ�
     * 
	 *  @param[in]  state   �M�~�b�N�̏�Ԃ�ݒ肷��l
     */
    void SetState(GIMMICK_STATE state) { m_State = state; }

    /*!
	 *  @brief      �^�C�}�[��ݒ�
     * 
	 *  @param[in]  time    �^�C�}�[�̎��Ԃ�ݒ肷��l
     */
    void SetTimer(float time);


protected:
	GIMMICK_STATE m_State;  //!< �M�~�b�N�̏��
	CTimer        m_Timer;  //!< �^�C�}�[
};  