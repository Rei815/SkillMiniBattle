#pragma once

#include "vivid.h"
#include <list>
#include "animation/animation_id.h"
#include "animation/animation.h"
#include <memory>
class CAnimationManager
{
public:
    /*!
     *  @brief      �C���X�^���X�̎擾
     *
     *  @return     �C���X�^���X
     */
    static CAnimationManager& GetInstance(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(void);

    /*!
     *  @brief      �X�V
     */
    void        Update(void);

    /*!
     *  @brief      ���
     */
    void        Finalize(void);

    /*!
     *  @brief        �A�j���[�V��������
     *
     *  @param[in]    id                �M�~�b�NID
     *  @param[in]    pointer           �A�j���[�V����������C���X�^���X�̃|�C���^
     *  @return       �A�j���[�V����
     */
    std::shared_ptr<IAnimation>        Create(ANIMATION_ID id, std::shared_ptr<void> pointer);

    /*!
     *  @brief      �M�~�b�N���X�g�^
     */
    using ANIMATION_LIST = std::list<std::shared_ptr<IAnimation>>;

    /*!
     *  @brief      ���X�g�擾
     *
     *  @return     �A�j���[�V�������X�g
     */
    ANIMATION_LIST GetList();

private:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CAnimationManager(void);

    /*!
     *  @brief      �R�s�[�R���X�g���N�^
     *
     *  @param[in]  rhs     �I�u�W�F�N�g
     */
    CAnimationManager(const CAnimationManager& rhs);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CAnimationManager(void);

    /*!
     *  @brief      ������Z�q
     *
     *  @param[in]  rhs ����I�u�W�F�N�g
     *
     *  @return     ���g�̃I�u�W�F�N�g
     */
    CAnimationManager& operator=(const CAnimationManager& rhs);

    ANIMATION_LIST             m_AnimationList;             //!< �A�j���[�V�������X�g
};