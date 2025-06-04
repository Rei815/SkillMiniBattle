#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "..\..\..\controller_manager\controller\controller.h"
class CPause : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CPause(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CPause(void);

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

    void        SetPauseController(std::shared_ptr<CController> controller);
private:
    static const vivid::Vector2     m_position;     //!< �ʒu
    static const int                m_height;       //!< ����
    static const int                m_width;        //!< ��
    static const vivid::Rect        m_rect;         //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;       //!< ��_
    static const vivid::Vector2     m_scale;        //!< �g�k
    static const vivid::Vector2     m_offset;       //!< �g�k
    unsigned int                    m_Color[2];
    std::shared_ptr<CController>                    m_PauseController;
    int                             m_UINum;
    vivid::Vector2                  m_Anchor[2];
    vivid::Vector2                  m_Scale[2];
};
