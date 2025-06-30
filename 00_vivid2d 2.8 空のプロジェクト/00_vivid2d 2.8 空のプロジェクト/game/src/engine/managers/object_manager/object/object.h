#pragma once
#include <memory>
#include "object_id.h"

// �O���錾
class CGameObject;
class CGimmick;
class CTransform;

// ���ׂẮu�ÓI�I�u�W�F�N�g�v�̐e�ƂȂ�N���X
// ���͂�A�����ł͕`������W�Ǘ������Ȃ��A�u�]�v�����̑���
class IObject
{
protected:
    // ������ ���ׂẴI�u�W�F�N�g�����u�́v ������
    std::shared_ptr<CGameObject> m_gameObject;

    // --- �u�]�v�����ׂ��A�I�u�W�F�N�g�ŗL�̃f�[�^ ---
    OBJECT_ID m_ObjectID;
    std::shared_ptr<CGimmick> m_Gimmick;
    std::string m_Tag;
    bool m_ColliderActiveFlag;

public:
    IObject();
    virtual ~IObject() = default;

    // �����������́A�����́u�́v�𐶐����A�ݒ肷������ɂȂ�
    virtual void Initialize(OBJECT_ID id, const CTransform& transform);

    // �X�V�����́A�M�~�b�N�̍X�V��A����ȃ��W�b�N�����s����
    virtual void Update();

    // �`�揈���́A�u�́v�Ɋۓ������邾��
    virtual void Draw();

    // --- �O���Ƃ̃C���^�[�t�F�[�X ---
    // ���W�Ȃǂ�m�肽���ꍇ�́A�u�́v�ɖ₢���킹��
    CVector3 GetPosition();
    bool IsActive();
    void Delete(); // ������m_gameObject->Delete()���Ă�

    // �M�~�b�N�̑���́A���̂܂܎c��
    void SetGimmick(std::shared_ptr<CGimmick> gimmick);
    std::shared_ptr<CGimmick> GetGimmick();
};