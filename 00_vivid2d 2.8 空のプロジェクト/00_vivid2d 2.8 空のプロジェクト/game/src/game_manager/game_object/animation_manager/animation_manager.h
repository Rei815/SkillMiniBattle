#pragma once

#include "vivid.h"
#include <list>
#include "animation/animation_id.h"
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
     *  @brief      �`��
     */
    void        Draw(void);

    /*!
     *  @brief      ���
     */
    void        Finalize(void);

    ///*!
    // *  @brief        �A�j���[�V��������
    // *
    // *  @param[in]  id                  �M�~�b�NID
    // */
    void        Create(ANIMATION_ID id);

    ///*!
    // *  @brief      �M�~�b�N����
    // *
    // *  @param[in]  id                  �M�~�b�NID
    // *  @param[in]  object              �I�u�W�F�N�g�̃|�C���^
    // *  @param[in]  time                �x������
    // */
    //void        Create(GIMMICK_ID id, IObject* object, float time);

    /*!
     *  @brief      �M�~�b�N���X�g�^
     */
    //using ANIMATION_LIST = std::list<IAnim*>;

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

    //ANIMATION_LIST             m_AnimationList;             //!< �A�j���[�V�������X�g
};