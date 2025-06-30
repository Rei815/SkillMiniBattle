#pragma once
#include "..\controller.h"
class CKeyboard : public CController
{
public:
	CKeyboard();
	~CKeyboard();

    /*!
     *  @brief  �{�^���ɑΉ�����L�[�������ꂽ���ǂ���
     */
    bool        GetButtonDown(BUTTON_ID button_id) override;

    /*!
     *  @brief  �{�^���ɑΉ�����L�[�������ꂽ���ǂ���
     */
    bool        GetButtonUp(BUTTON_ID button_id) override;

    /*!
     *  @brief  �{�^���ɑΉ�����L�[��������Ă��邩�ǂ���
     */
    bool        GetButtonHold(BUTTON_ID button_id) override;

    /*!
     *  @brief  ���X�e�B�b�N�ɑΉ�����L�[�̏�Ԃ��擾
     *
     *  @return vivid::Vector2          -1.0f�`1.0f
     */
    vivid::Vector2        GetLeftStick() override;
};