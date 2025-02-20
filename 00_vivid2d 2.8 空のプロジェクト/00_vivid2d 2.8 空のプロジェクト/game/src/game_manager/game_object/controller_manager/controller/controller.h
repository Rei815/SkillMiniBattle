#pragma once
#include "input_id.h"
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
     *  @brief  �A�N�e�B�u�t���O�̎擾
     */
    bool        GetActive(void);

    /*!
     *  @brief  �{�^���������ꂽ���ǂ���
     */
    bool        GetButtonDown(INPUT_ID button_id);

    /*!
     *  @brief      �R���g���[���[��ID���擾
     */
    CONTROLLER_ID       GetID();

    void                Vibration();

    void                SetControllerID(CONTROLLER_ID controller_id);
private:
    /*!
     *  @brief      ���͂̃��Z�b�g
     */
    void    Reset(void);

    static const float              m_vibration_power;
    static const float              m_vibration_time;

    bool                            m_Active;
    vivid::controller::DEVICE_ID    m_Device;
    int                             m_JoyPad;
    bool                            m_BButton;
    bool                            m_AButton;
    bool                            m_AllButton;
    bool                            m_StickLeftButton;
    bool                            m_StickRightButton;
    CONTROLLER_ID                   m_ControllerID;
    int                             m_AllButtonDown;
    int                             m_BButtonDown;
    int                             m_AButtonDown;
    int                             m_StickLeftDown;
    int                             m_StickRightDown;
};

class CButton
{
public:


};