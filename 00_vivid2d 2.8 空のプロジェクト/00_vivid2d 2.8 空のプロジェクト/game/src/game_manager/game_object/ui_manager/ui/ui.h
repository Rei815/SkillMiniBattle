#pragma once

#include "vivid.h"
#include<vector>
#include "ui_id.h"
#include "../../../../utility/utility.h"
class CUI
{
public:
    //UI�̑���
    enum class UI_ATTRIBUTE
    {
        NONE,               //!< �����Ȃ�
        STOP_GENERATION,    //!< �G�̐������~
        BUTTON,             //!< ������
        WAVE_REWARD,        //!< ��V���󂯎���
        MOVE,               //!< ����
        MAX,
    };

    /*!
     *  @brief      �R���X�g���N�^
     */
    CUI(int width, int height, UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CUI(void);

    /*!
     *  @brief      ������
     */
    virtual void        Initialize(void);

    /*!
     *  @brief      ������
     */
    virtual void        Initialize(const CVector3& position);

    /*!
     *  @brief      ������
     */
    virtual void        Initialize(const vivid::Vector2& position);

    /*!
     *  @brief      ������
     */
    virtual void        Initialize(const CTransform& transform);

    /*!
     *  @brief      �X�V
     */
    virtual void        Update(void);

    /*!
     *  @brief      �`��
     */
    virtual void        Draw(void);

    /*!
     *  @brief      ���
     */
    virtual void        Finalize(void);

    /*!
     *  @brief      �A�N�e�B�u�t���O�擾
     *
     *  @return     �A�N�e�B�u�t���O
     */
    bool            GetActive(void);

    /*!
     *  @brief      �A�N�e�B�u�t���O�ݒ�
     *
     *  @param[in]  active  �A�N�e�B�u�t���O
     */
    void            SetActive(bool active);

    /*!
     *  @brief      UI�̑��������邩
     * 
     *  @param[in]  attribute  ����
     * 
     *  @return     true ����������
     */
    bool            CheckAttribute(UI_ATTRIBUTE attribute);

    bool            OnMouseClick(const vivid::Vector2& position, int width, int height);

    /*!
     *  @brief      �ʒu�擾
     *
     *  @return     �ʒu
     */
    vivid::Vector2            GetPosition(void);
    /*!
     *  @brief      �����擾
     *
     *  @return     ����
     */
    int            GetWidth(void);
    /*!
     *  @brief      �����擾
     *
     *  @return     ����
     */
    int            GetHeight(void);
    /*!
     *  @brief      ID�擾
     *
     *  @return     UI��ID
     */
    UI_ID            GetUI_ID(void);

protected:

    CTransform                      m_Transform;
    vivid::Vector2                  m_Position;         //!< �ʒu
    int                             m_Height;       //!< ����
    int                             m_Width;        //!< ��
    bool                            m_ActiveFlag;   //!< �A�N�e�B�u�t���O
    std::vector<UI_ATTRIBUTE>       m_Attributes;    //!< ����
    UI_ID                           m_UI_ID;
};
