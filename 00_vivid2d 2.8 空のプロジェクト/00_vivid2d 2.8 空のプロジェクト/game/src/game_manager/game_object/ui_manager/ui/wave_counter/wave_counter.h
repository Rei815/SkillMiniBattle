#pragma once

#include "vivid.h"
#include <string>
#include "..\ui.h"

class CWaveCounter : public CUI
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CWaveCounter(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CWaveCounter(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(void);

    /*!
     *  @brief      �X�V
     */
    void        Update(vivid::Vector2 position);

    /*!
     *  @brief      �`��
     */
    void        Draw(void);

    /*!
     *  @brief      ���
     */
    void        Finalize(void);

    /*!
     *  @brief      �ʒu�ݒ�
     */
    void        SetPosition(vivid::Vector2 position);

private:
    static const vivid::Vector2     m_position;     //!< �ʒu
    static const int                m_font_size;    //!< �����̑傫��

    int                             m_MaxWave;      //!< Wave�ő吔
    int                             m_CurrentWave;  //!< ���݂�Wave
    std::string                     m_Text;         //!< �e�L�X�g
};
