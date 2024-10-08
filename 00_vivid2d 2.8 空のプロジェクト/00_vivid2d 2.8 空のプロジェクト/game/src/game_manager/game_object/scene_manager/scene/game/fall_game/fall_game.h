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

    int     m_FallTime;
    int     m_FallTimer;

    static const CVector3 m_object_position_list[];
};
