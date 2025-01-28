#pragma once

#include "vivid.h"
#include "..\ui.h"

class  CSceneUIParent : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CSceneUIParent(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CSceneUIParent(void);

    /*!
     *  @brief      ������
     */
    void        Initialize();

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

private:

    static const vivid::Vector2             m_position;             //!< �ʒu
    static const int            m_speed;                //!< �ړ����x
    static const float			m_down_final_height;	//!< �~���Ƃ��̍ŏI���x

    static const float          m_end_time;             //!< �I������
    float                       m_EaseTimer;            //!< �o�ߎ���
    float                       m_StartValue;           //!< �J�n�l
    float                       m_FinishValue;          //!< �I���l

};