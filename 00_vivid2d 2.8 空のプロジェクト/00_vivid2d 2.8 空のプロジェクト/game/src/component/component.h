#pragma once

// �O���錾: CGameObject �N���X
// Component �� CGameObject �̃��\�b�h���Ăяo���K�v������ꍇ�����邽��
class CGameObject;

// IComponent ���C���^�[�t�F�[�X
// �S�ẴR���|�[�l���g�͂��̃C���^�[�t�F�[�X���p������
class IComponent {
public:
    virtual ~IComponent() = default;

    // �X�V����
    // delta_time: �O�̃t���[������̌o�ߎ��ԁi�b�P�ʂȂǁj
    // owner: ���̃R���|�[�l���g���A�^�b�`����Ă��� GameObject �̃|�C���^
    // �R���|�[�l���g�� owner �̏�Ԃ��X�V���邽�߂Ɏg�p
    virtual void Update(float delta_time, CGameObject* owner) = 0;

    // �R���|�[�l���g���G���e�B�e�B�ɃA�^�b�`���ꂽ�Ƃ��ɌĂ΂�鏉��������
    // �����ŁA���̃R���|�[�l���g�ւ̎Q�Ƃ��擾������A�����ݒ���s������ł���
    virtual void OnAttach(CGameObject* owner) { /* �f�t�H���g�ł͉������Ȃ� */ }

    // �R���|�[�l���g���G���e�B�e�B����f�^�b�`�����Ƃ��ɌĂ΂��I������
    // ���\�[�X�̉���Ȃǂ��s��
    virtual void OnDetach(CGameObject* owner) { /* �f�t�H���g�ł͉������Ȃ� */ }
};