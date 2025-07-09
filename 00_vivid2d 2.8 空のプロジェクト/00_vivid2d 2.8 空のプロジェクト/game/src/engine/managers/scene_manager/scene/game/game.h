#pragma once

#include"..\scene.h"
#include "game_id.h"
#include "../../../ui_manager/ui/game_bg/game_bg.h"
#include "../../../../../game/components/player_component/player_id.h"
#include <list>
#include "../../../../core/game_object/game_object.h"
/*!
*  @brief  �Q�[���̏��
*/
enum class GAME_STATE
{
    START,
    PLAY,
    FINISH,
};

class CGame : public IScene
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
    virtual void    Initialize(SCENE_ID scene_id);

    /*!
     *  @brief      �X�V
     */
    virtual void    Update(void);

    /*!
     *  @brief      �`��
     */
    virtual void    Draw(void);

    /*!
     *  @brief      ���
     */
    virtual void    Finalize(void);

    /*!
     *  @brief      �Q�[���̏�Ԏ擾
     *
     *  @return     �Q�[���̏��ID
     */
    GAME_STATE      GetGameState(void);

    /*!
     *  @brief      �Q�[���̏�Ԑݒ�
     *
     *  @param[in]  state   �Q�[�����ID
     */
    void            SetGameState(GAME_STATE state);

protected:

    /*!
     *  @brief      �����L���O�ɒǉ�
     *
     *  @param[in]  unit   �ǉ�����v���C���[��ID
     */
    void            AddRanking(PLAYER_ID playerID);

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
    static const float m_finish_text_time;

    GAME_STATE      m_GameState;    //!< �Q�[���̏��
    CTimer          m_WaitTimer;    //!< �ҋ@���Ԃ̃^�C�}�[
    bool            m_CountFlag;    //!< �J�E���g�_�E���̃t���O
    bool            m_SetActionflag;//!< �v���C���[�A�N�V�����t���O�ݒ�p
    bool            m_FinishFlag;   //!< �~�j�Q�[�����I��������
    bool            m_ResultFlag;   //!< ���U���g���o�Ă��邩

    using ENTRY_LIST = std::list<std::shared_ptr<CGameObject>>;   //!< �Q���������͐������̃v���C���[�̃��X�g
    using RESULT_LIST = std::list<std::shared_ptr<CGameObject>>;  //!< �s�k���ă��U���g�Ɉڂ����v���C���[�̃��X�g

    ENTRY_LIST          m_EntryList;    //!< �G���g���[���X�g
    RESULT_LIST         m_ResultList;   //!< ���U���g���X�g

    CTimer              m_PlayTimer;    //!< �v���C���̃^�C�}�[
    CGameBG             m_BackGround;   //!< �Q�[���w�i(UI���X�g�Ƃ͕ʂœ�����)

};