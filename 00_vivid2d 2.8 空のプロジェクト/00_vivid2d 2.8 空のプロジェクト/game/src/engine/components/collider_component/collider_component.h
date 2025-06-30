#pragma once
#include "../../core/component/component.h"
#include "../../mathematics/mathematics.h"

// �S�Ă̓����蔻��R���|�[�l���g�̐e�N���X
class ColliderComponent : public IComponent
{
public:
    ColliderComponent() = default;
    virtual ~ColliderComponent() = default;

    /**
     * @brief �w�肳�ꂽ���C���Ƃ̓����蔻����`�F�b�N���܂��B
     * @param startPos ���C���̊J�n���W
     * @param endPos ���C���̏I�����W
     * @param out_hitPosition [out] �Փ˂����ʒu���i�[����ϐ�
     * @return �Փ˂����ꍇ�� true
     */
    virtual bool CheckHitLine(
        const CVector3& startPos,
        const CVector3& endPos,
        CVector3& out_hitPosition) const = 0; // = 0 �ŏ������z�֐�

    /*
     * @brief �����蔻�肪�L�����ǂ�����ݒ肵�܂��B
     * @param isEnabled �L���ɂ���ꍇ��true
     */
    void SetEnabled(bool isEnabled);

    /*
     * @brief �����蔻�肪���ݗL�����ǂ������擾���܂��B
     * @return �L���ȏꍇ��true
     */
    bool IsEnabled() const;
protected:
    // �����蔻��̗L��/�����t���O
    bool m_IsEnabled;
};