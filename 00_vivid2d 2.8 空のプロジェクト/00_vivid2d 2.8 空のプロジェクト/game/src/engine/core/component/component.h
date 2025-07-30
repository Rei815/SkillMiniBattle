#pragma once

// �O���錾: CGameObject �N���X
class CGameObject;

// IComponent ���C���^�[�t�F�[�X
// �S�ẴR���|�[�l���g�͂��̃C���^�[�t�F�[�X���p������
class IComponent 
{
public:

	/*!
	 *  @brief      �f�X�g���N�^
	 */
    virtual ~IComponent() = default;

	/*!
	 *	@brief      �R���|�[�l���g�̍X�V
	 * 
	 *	@param[in] delta_time �O�t���[������̌o�ߎ���
	 *	@param[in] owner      �R���|�[�l���g���A�^�b�`�����I�[�i�[�I�u�W�F�N�g
	 */
    virtual void Update(float delta_time, CGameObject* owner) = 0;

    virtual void OnAttach(CGameObject* owner) { /* �f�t�H���g�ł͉������Ȃ� */ }

    virtual void OnDetach(CGameObject* owner) { /* �f�t�H���g�ł͉������Ȃ� */ }
protected:
	CGameObject* m_Owner = nullptr; // ���̃R���|�[�l���g���A�^�b�`����Ă��� GameObject �̃|�C���^
};