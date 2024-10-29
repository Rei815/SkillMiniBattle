#pragma once

#include"..\scene.h"
#include "../../../model_manager/model/model.h"
#include "../../../stage/stage.h"
#include "game_id.h"
#include "../../../object_manager/object/object.h"
/*!
*  @brief  �Q�[���̏��
*/
enum class GAME_STATE
{
    START,
    PLAY,
    FINISH,
};

class CGame
    : public IScene
{
public:

    /*!
     *  @brief      �R���X�g���N�^
     */
    CGame(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    virtual ~CGame(void);

    /*!
     *  @brief      ������
     */
    virtual void        Initialize(void);

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
     *  @brief      �Q�[���̏�Ԏ擾
     *
     *  @return     �Q�[���̏��ID
     */
    GAME_STATE  GetGameState(void);

    /*!
     *  @brief      �Q�[���̏�Ԑݒ�
     *
     *  @param[in]  state   �Q�[�����ID
     */
    void        SetGameState(GAME_STATE state);


protected:


    /*!
     *  @brief      �X�^�[�g
     */
    virtual void    Start(void);

    /*!
     *  @brief      �v���C
     */
    virtual void    Play(void);

    /*!
     *  @brief      �I��
     */
    virtual void    Finish(void);

    GAME_STATE      m_GameState;    //!< �Q�[���̏��


    int             m_WaitTime;     //!< �ҋ@����
    bool            m_PauseFlag;    //!< �|�[�Y�t���O
    std::string     m_DebugText;    //!< �f�o�b�O�p
    bool            m_SetActionflag;//!< �v���C���[�A�N�V�����t���O�ݒ�p
    bool            m_FinishUIFlag;
};
