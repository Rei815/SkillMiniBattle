
#pragma once
#include "..\gimmick.h"

class CDaruma_FallDownGimmick : public CGimmick
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     *
     */
    CDaruma_FallDownGimmick();

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CDaruma_FallDownGimmick(void);

    /*!
     *  @brief      ������
     *
     */
    void    Initialize();

    /*!
     *  @brief      �X�V
     */
    void    Update(void);

    /*!
     *  @brief      �`��
     */
    void    Draw(void);

    /*!
     *  @brief      ���
     */
    void    Finalize(void);

private:

    bool m_TurnAround;           //�S���U����������ǂ���
    bool m_SeenMove;             //�S�Ɍ����Ă鎞�ɓ�������
    bool m_Touch;                //�S�ɐG�������ǂ���
    bool m_GameEnd;              //�Q�[���I�������𖞂�������

    float m_TurnAroundTime;      //�S���U������܂ł̎���
    int   m_RestPlayer;          //�c��̃v���C���[��

    CTimer  m_Timer;
};
