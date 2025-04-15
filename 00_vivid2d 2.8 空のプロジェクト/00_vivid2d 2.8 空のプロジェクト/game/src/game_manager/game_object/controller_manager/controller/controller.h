#pragma once
#include "controller_id.h"
#include <vivid.h>
#include "button_id.h"
#include "../../unit_manager/unit/player/player.h"

class CPlayer;
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
    virtual bool        GetButtonDown(BUTTON_ID button_id);

    /*!
     *  @brief  �{�^���������ꂽ���ǂ���
     */
    virtual bool        GetButtonUp(BUTTON_ID button_id);

    /*!
     *  @brief  �{�^����������Ă��邩�ǂ���
     */
    virtual bool        GetButtonHold(BUTTON_ID button_id);

    /*!
     *  @brief  ���X�e�B�b�N�̏�Ԃ��擾
     * 
     *  @return vivid::Vector2          -1.0f�`1.0f
     */
    virtual vivid::Vector2        GetLeftStick();

    /*!
     *  @brief  ���X�e�B�b�N�����E�ɌX�������̃t���O���擾
     *          ������true�ɂȂ�Ȃ�
     *  @return bool          ���E�ɌX������
     */
    bool        GetLeftHorizontal();

    /*!
     *  @brief  ���X�e�B�b�N�����E�ɌX�������̃t���O��ݒ�
     * 
     *  @param[in]      flag    ���E�ɌX������
     */
    void        SetLeftHorizontal(bool flag);

    /*!
     *  @brief  ���X�e�B�b�N���㉺�ɌX�������̃t���O���擾
     *          ������true�ɂȂ�Ȃ�
     *  @return bool          �㉺�ɌX������
     */
    bool        GetLeftVertical();

    /*!
     *  @brief  ���X�e�B�b�N���㉺�ɌX�������̃t���O��ݒ�
     * 
     *  @param[in]      flag    �㉺�ɌX������
     */
    void        SetLeftVertical(bool flag);


    /*!
     *  @brief      �R���g���[���[��ID���擾
     */
    CONTROLLER_ID       GetID();

    void                Vibration();

    void                SetControllerID(CONTROLLER_ID controller_id);

    /*!
     *  @brief      ���j�b�gID���擾
     *
     *  @return     ���j�b�gID
     */
    UNIT_ID         GetUnitID();

    /*!
     *  @brief      ���j�b�gID��ݒ�
     *
     *  @param[in]  unit_id    ���j�b�gID
     */
    void            SetUnitID(UNIT_ID unit_id);


private:

    static const float              m_vibration_power;
    static const float              m_vibration_time;

    bool                            m_Active;
    vivid::controller::DEVICE_ID    m_Device;
    int                             m_JoyPad;
    CONTROLLER_ID                   m_ControllerID;
    bool                            m_LeftHorizontal;
    bool                            m_LeftVertical;
    vivid::Vector2                  m_Stick;
    UNIT_ID                         m_UnitID;
};