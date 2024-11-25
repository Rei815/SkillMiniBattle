
#pragma once
#include "..\gimmick.h"

enum class OGRE_STATE
{
    READY,
    PLAY,
    WAIT,
    FINISH,
};

enum class TURN_TYPE
{
    FEINT,
    SLOW,
    FAST,

    TYPE_NUM,
};

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
    void    Initialize(IObject* object);

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

    /*!
    *  @brief      ����
    */
    virtual void    Ready(void);

    /*!
    *  @brief      �v���C
    */
    virtual void    Play(void);

    /*!
    *  @brief      �ҋ@
    */
    virtual void    Wait(void);

    /*!
    *  @brief      �I��
    */
    virtual void    Finish(void);

    /*!
    *  @brief      �U������t�F�C���g
    */
    virtual void    Feint(void);

    /*!
    *  @brief      �U���������
    */
    virtual void    Fast(void);

    /*!
    *  @brief      �U������x��
    */
    virtual void    Slow(void);

private:

    OGRE_STATE m_OgreState;
    TURN_TYPE  m_TurnType;

    bool m_SeenMove;             //�S�Ɍ����Ă鎞�ɓ�������
    bool m_Touch;                //�S�ɐG�������ǂ���
    bool m_GameEnd;              //�Q�[���I�������𖞂�������

    float m_ReadyTime;      //�S���U������܂ł̎���
    float m_WaitTime;            //�S�̑ҋ@����
    float m_TurnSpeed;           //�S�̐U��������x
    float m_TurnAngle;           //�U������p�x
    int   m_RestPlayer;          //�c��̃v���C���[��

    CTransform m_Transform;      //�S�̃g�����X�t�H�[��
    CTimer  m_Timer;
};
