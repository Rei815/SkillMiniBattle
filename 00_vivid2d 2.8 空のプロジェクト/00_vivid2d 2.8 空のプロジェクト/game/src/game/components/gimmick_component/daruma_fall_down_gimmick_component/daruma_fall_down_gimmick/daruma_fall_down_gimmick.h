#pragma once
#include "../../../../../engine/core/game_object/game_object.h"
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

class CDarumaFallDownGimmick
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     *
     */
    CDarumaFallDownGimmick();

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CDarumaFallDownGimmick(void);

    /*!
     *  @brief      ������
     *
     */
    void    Initialize(CGameObject* object);

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
    void    Ready(void);

    /*!
    *  @brief      �v���C
    */
    void    Play(void);

    /*!
    *  @brief      �ҋ@
    */
    void    Wait(void);

    /*!
    *  @brief      �I��
    */
    void    Finish(void);

    /*!
    *  @brief      �U������t�F�C���g
    */
    void    Feint(void);

    void    OgreControlTurn(void);

    /*!
     *  @brief      ��Ԃ��擾
     *
     *  @return     ���
     */
    OGRE_STATE      GetState();

private:

    static const float      m_default_ready_time;   //�f�t�H���g�̋S�̏�������
    static const float      m_default_wait_time;    //                �ҋ@����
    static const float      m_default_turn_angle;   //                �U������p�x

    static const float      m_feint_ready_time;     //�t�F�C���g�̋S�̏�������
    static const float      m_feint_wait_time;      //                �ҋ@����
    static const float      m_feint_turn_angle;     //                �U������p�x

    static const float      m_turn_speed;            //�S�̐U��������x

    float                   m_ReadyTime;                          //�S���U������܂ł̎���
    float                   m_WaitTime;                           //�S�̑ҋ@����
    float                   m_TurnAngle;                          //�U������p�x
    int                     m_RestPlayer;                         //�c��̃v���C���[��

    OGRE_STATE              m_OgreState;                     //�S�̏��
    TURN_TYPE               m_TurnType;                      //�U������̎��
    CTransform              m_Transform;                     //�S�̃g�����X�t�H�[��
    CTimer                  m_Timer;                         //�^�C�}�[
    CGameObject* m_Object;

};
