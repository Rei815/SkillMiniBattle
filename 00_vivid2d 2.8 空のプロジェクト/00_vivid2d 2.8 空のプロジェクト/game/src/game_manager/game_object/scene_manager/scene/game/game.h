
/*!
 *  @file       game_main.h
 *  @brief      �Q�[�����C���V�[��
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"
#include"..\scene.h"
#include "../../../model_manager/model/model.h"
#include "../../../stage/stage.h"
 
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
    ~CGame(void);

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

    GAME_STATE          m_GameState;            //!< �Q�[���̏��

    static const int                m_fight_width;          //!< FIGHT�̕�
    static const int                m_fight_height;         //!< FIGHT�̍���
    static const int                m_gameclear_width;      //!< �Q�[���N���A�̕�
    static const int                m_gameclear_height;     //!< �Q�[���N���A�̍���
    static const int                m_gameover_width;       //!< �Q�[���I�[�o�[�̕�
    static const int                m_gameover_height;      //!< �Q�[���I�[�o�[�̍���
    static const vivid::Vector2     m_fight_position;       //!< �Q�[���J�n�ʒu
    static const vivid::Vector2     m_gameclear_position;   //!< �Q�[���N���A�J�n�ʒu
    static const vivid::Vector2     m_gameover_position;    //!< �Q�[���I�[�o�[�J�n�ʒu
    static const int                m_wave_interval;        //!< Wave�Ԃ̑ҋ@����
    static const int                m_start_wave_interval;  //!< Wave�J�n����̑ҋ@����


    int                             m_WaitTime;             //!< �ҋ@����
    int                             m_FightAlpha;           //!< FIGHT�A���t�@�l
    int                             m_GameOverAlpha;        //!< �Q�[���I�[�o�[�A���t�@�l
    int                             m_GameClearAlpha;       //!< �Q�[���N���A�A���t�@�l
    vivid::Vector2                  m_FightScale;           //!< FIGHT�g�嗦
    vivid::Vector2                  m_GameClearScale;       //!< �Q�[���N���A�g�嗦
    float                           m_GameClearRotation;    //!< �Q�[���N���A��]�l
    bool                            m_PauseFlag;            //!< �|�[�Y�t���O
    bool                            m_ActiveWave;           //!< Wave�����ǂ���
    bool                            m_StartWave;            //!< Wave�J�n�������ǂ���
    bool                            m_WaveClear;            //!< Wave�N���A�������ǂ���
    int                             m_WaveTimer;            //!< Wave�Ԃ̃^�C�}�[
    int                             m_StartWaveTimer;       //!< Wave�J�n����̂̃^�C�}�[
    bool                            m_ReceiveReward;        //!< ��V���󂯎��邩�ǂ���

};
