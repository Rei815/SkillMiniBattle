#pragma once

#include "..\game.h"

class CFallGame : public CGame
{
public:

    /*!
     *  @brief      �R���X�g���N�^
     */
    CFallGame(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CFallGame(void);

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

};
