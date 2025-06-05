#pragma once

#include "vivid.h"

 /*!
  *  @brief      �T�E���hID
  */


enum class BGM_ID
{
    MAIN_BGM,
    RESULT_BGM,
    READY_BGM,

    MAX
};

enum class SE_ID
{
    BARRIER,
    CANCEL_BUTTON,
    CANNON_SHOT,
    DASH,
    DECIDE_BUTTON,
    FALLOUT_DECIDE,
    FALLOUT_RAFFLE,
    FLOATING,
    GAME_DECIDE,
    GAME_FINISH,
    GAME_RAFFLE,
    GAME_START,
    GRAVITYAREA,
    HIDETOPIC,
    INVISIBLE,
    KEYGET,
    MIMICRY,
    RESURECT,
    SCENE_MOVE,
    SELECT,
    SKILL,
    SLOW,
    SPAWN_WALL,
    STOMP,
    STRONG_WIND,
    STUN,
    REFLECTION,
    MAX
};

class CSoundManager
{
public:
    /*!
     *  @brief      �C���X�^���X�̎擾
     *
     *  @return     �C���X�^���X
     */
    static CSoundManager& GetInstance(void);

    /*!
     *  @brief      �T�E���h�̓ǂݍ���
     */
    void        Load_BGM(void);
    void        Load_SE(void);

    /*!
     *  @brief      �Đ�
     *
     *  @param[in]  id      �T�E���hID
     *  @param[in]  loop    ���[�v�t���O
     */

    void        Play_BGM(BGM_ID id, bool loop = false);
    void        Stop_BGM(BGM_ID id);
    void        SetBGMVolume(BGM_ID id, int volume = 1);


    void        Play_SE(SE_ID id, bool loop = false);
    void        Stop_SE(SE_ID id);
    void        SetSEVolume(SE_ID id, int volume = 1);

    /*
    *�@���
    */
    virtual void    Finalize(void);

private:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CSoundManager(void);

    /*!
     *  @brief      �R�s�[�R���X�g���N�^
     *
     *  @param[in]  rhs     �I�u�W�F�N�g
     */
    CSoundManager(const CSoundManager& rhs);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CSoundManager(void);

    /*!
     *  @brief      ������Z�q
     *
     *  @param[in]  rhs ����I�u�W�F�N�g
     *
     *  @return     ���g�̃I�u�W�F�N�g
     */
    CSoundManager& operator=(const CSoundManager& rhs);


    static const char* m_se_file_names[(int)SE_ID::MAX];      //!< SE�̃t�@�C����
    static const char* m_bgm_file_names[(int)BGM_ID::MAX];    //!< BGM�̃t�@�C����
};
