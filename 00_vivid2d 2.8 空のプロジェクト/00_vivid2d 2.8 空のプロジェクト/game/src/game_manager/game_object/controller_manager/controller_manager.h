#pragma once

#include "vivid.h"
#include "..\..\..\utility\utility.h"
#include <list>
#include "controller/controller.h"

class CControllerManager
{
public:
    /*!
     *  @brief      �C���X�^���X�̎擾
     *
     *  @return     �C���X�^���X
     */
    static CControllerManager& GetInstance(void);


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
     *  @brief      �R���g���[���[�̐���ݒ�
     * 
     *  @param[in]  num          �R���g���[���[�̐�
     */
    void        SetControllerNum(int num);

    /*!
     *  @brief      �R���g���[���[�̐����擾
     *  @return     �R���g���[���[�̐�
     */
    int         GetControllerNum();

    /*!
     *  @brief      �R���g���[���[����
     *
     *  @param[in]  id          �R���g���[���[ID
     */
    CController* Create(CONTROLLER_ID id);

    /*!
     *  @brief      �R���g���[���[���擾
     */
    CController* GetController(CONTROLLER_ID controller_id);

    /*!
     *  @brief      �����ꂩ�̃R���g���[���[�̃{�^���̏�Ԃ��擾
     *  @return     �w��̃{�^���������ꂽ��
     */
    bool         GetAnyControllerButtonDown(BUTTON_ID button_id);

    /*!
     *  @brief      �R���g���[���[��U��������
     *
     *  @param[in]  controller_id          �R���g���[���[��ID
     */
    void Vibration(CONTROLLER_ID controller_id);

    /*!
     *  @brief      �w��̃{�^�����������R���g���[���[���擾
     *  @param[in]  player    �v���C���[�̃|�C���^�[
     *  @return     CPlayer*    �v���C���[�̃|�C���^�[
     */
    CController* GetSpecifiedButtonDownController(BUTTON_ID button_id);

private:

    /*!
     *  @brief      �R���X�g���N�^
     */
    CControllerManager(void);

    /*!
     *  @brief      �R�s�[�R���X�g���N�^
     *
     *  @param[in]  rhs     �I�u�W�F�N�g
     */
    CControllerManager(const CControllerManager& rhs);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CControllerManager(void);

    /*!
     *  @brief      ������Z�q
     *
     *  @param[in]  rhs ����I�u�W�F�N�g
     *
     *  @return     ���g�̃I�u�W�F�N�g
     */
    CControllerManager& operator=(const CControllerManager& rhs);

    int             m_ControllerNum;

    std::list<vivid::controller::DEVICE_ID>         m_ControllerIDList;
    using CONTROLLER_LIST = std::list<CController*>;

    CONTROLLER_LIST                                 m_ControllerList;
};
