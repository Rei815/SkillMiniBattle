#pragma once

#include "vivid.h"
#include "..\..\ui.h"
class CReward : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CReward(const std::string text);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CReward(void);

    /*!
     *  @brief      ������
     */
    virtual void        Initialize(const vivid::Vector2& position);

    /*!
     *  @brief      �X�V
     */
    virtual void        Update(const vivid::Vector2& position, float offset);

    /*!
     *  @brief      �`��
     */
    virtual void        Draw();

    /*!
     *  @brief      ���
     */
    virtual void        Finalize(void);

protected:
    static const int                m_height;           //!< ����
    static const int                m_width;            //!< ��

    vivid::Vector2                  m_Position;         //!< �ʒu

    std::string                     m_Text;
    bool                            m_OnClick;          //!< �N���b�N�t���O

};
