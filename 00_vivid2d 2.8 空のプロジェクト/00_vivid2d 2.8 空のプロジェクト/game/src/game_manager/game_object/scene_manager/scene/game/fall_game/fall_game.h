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

private:

    /*!
     *  @brief      �X�^�[�g
     */
    void    Start(void);

    /*!
     *  @brief      �v���C
     */
    void    Play(void);

    /*!
     *  @brief      �I��
     */
    void    Finish(void);

    /*!
     *  @brief      ������I�u�W�F�N�g�̑I��
     * 
     *  @return     �I�u�W�F�N�gID
     */
    OBJECT_ID    ChooseObject(void);

    float           m_FallTime;

    CTimer          m_Timer;
};
