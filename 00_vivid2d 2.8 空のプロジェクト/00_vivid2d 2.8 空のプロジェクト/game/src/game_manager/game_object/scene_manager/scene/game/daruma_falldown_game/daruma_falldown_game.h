#pragma once

#include "..\game.h"

class CDaruma_FallDownGame : public CGame
{
public:

    /*!
     *  @brief      �R���X�g���N�^
     */
    CDaruma_FallDownGame(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CDaruma_FallDownGame(void);

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
