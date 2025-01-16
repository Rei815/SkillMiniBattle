
/*!
 *  @file       sound_manager.h
 *  @brief      �T�E���h�Ǘ�
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"

 /*!
  *  @brief      �T�E���hID
  */
enum class SOUND_ID
{
    BGM,
    SHOT,
    HOMING_SHOT,
    DESTORY,
    BOSS_DESTORY,
    PLAYER_HIT,
    WARNING,
    WARNING_SHORT,
    GAMEOVER,
    GAMECLEAR,//�z��9�Ԗ�
    //����������ǉ���
    DECIDE_BUTTON,
    MAIN_BGM,

    MAX
};

/*!
 *  @class      CSoundManager
 *
 *  @brief      �T�E���h�Ǘ��N���X
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
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
    void        Load(void);

    /*!
     *  @brief      �Đ�
     *
     *  @param[in]  id      �T�E���hID
     *  @param[in]  loop    ���[�v�t���O
     */
    void        Play(SOUND_ID id, bool loop = false);

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

    static const char* m_sound_file_names[(int)SOUND_ID::MAX];    //!< �T�E���h�̃t�@�C����
};
