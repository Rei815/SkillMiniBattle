#pragma once

#include"..\scene.h"
#include "../../../model_manager/model/model.h"
#include "../../../stage/stage.h"
#include "game_id.h"
#include "../../../object_manager/object/object.h"
#include "../../../unit_manager/unit/unit.h"
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
    virtual void        Initialize(SCENE_ID scene_id);

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

    void AddRanking(UNIT_ID unitID);

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

    /*!
     *  @brief      �I������
     */
    virtual void    CheckFinish(void);

    static const float m_start_count_time;
    static const float m_start_text_time;

    GAME_STATE      m_GameState;    //!< �Q�[���̏��


    CTimer          m_WaitTimer;    //!< �ҋ@���Ԃ̃^�C�}�[
    bool            m_CountFlag;    //!< �J�E���g�_�E���̃t���O
    bool            m_PauseFlag;    //!< �|�[�Y�t���O
    std::string     m_DebugText;    //!< �f�o�b�O�p
    bool            m_SetActionflag;//!< �v���C���[�A�N�V�����t���O�ݒ�p
    bool            m_FinishFlag;
    /*!
     *  @brief      �v���C���[���X�g�^
     */


    using ENTRY_LIST = std::list<IUnit*>;
    using RESULT_LIST = std::list<IUnit*>;

    ENTRY_LIST          m_EntryList;
    RESULT_LIST         m_ResultList;             //!< ���U���g���X�g
};