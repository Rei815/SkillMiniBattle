#pragma once
#include "button_id.h"
#include "controller_id.h"
#include <vivid.h>

class CController
{
public:
	CController();
	~CController();

    /*!
      *  @brief      ������
      */
    void    Initialize(CONTROLLER_ID controller_id);

    /*!
     *  @brief      �X�V
     */
    void    Update(void);

    /*!
     *  @brief      ���
     */
    void    Finalize(void);

    /*!
     *  @brief      �A�N�e�B�u�t���O�̎擾
     */
    bool    GetActive(void);

    /*!
     *  @brief      �{�^���������ꂽ���ǂ���
     */
    bool    GetButtonDown(BUTTON_ID button_id);

    /*!
     *  @brief      �R���g���[���[��ID���擾
     */
    CONTROLLER_ID    GetID();


private:
    /*!
     *  @brief      ���͂̃��Z�b�g
     */
    void    Reset(void);

    bool                            m_Active;
    vivid::controller::DEVICE_ID    m_Device;
    int                             m_JoyPad;
    bool                            m_BButton;
    bool                            m_AnyButton;
    CONTROLLER_ID                   m_ControllerID;
};