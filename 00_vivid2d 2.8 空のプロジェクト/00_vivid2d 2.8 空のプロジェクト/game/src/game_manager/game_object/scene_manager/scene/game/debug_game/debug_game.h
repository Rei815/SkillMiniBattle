#pragma once

#include "..\game.h"

class CDebugGame : public CGame
{
public:

    /*!
     *  @brief      �R���X�g���N�^
     */
    CDebugGame(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CDebugGame(void);

    /*!
     *  @brief      ������
     */
    void Initialize(SCENE_ID scene_id);

    /*!
     *  @brief      �X�V
     */
    void        Update(void);

    /*!
     *  @brief      �`��
     */
    void        Draw(void);

};
