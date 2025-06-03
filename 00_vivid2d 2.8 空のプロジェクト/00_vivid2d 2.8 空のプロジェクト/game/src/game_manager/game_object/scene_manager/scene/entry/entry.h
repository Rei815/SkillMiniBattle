#pragma once

#include "vivid.h"
#include "..\scene.h"
#include "..\..\..\camera\camera.h"
#include <list>
#include "..\..\..\controller_manager\controller\controller.h"
#include "..\..\..\unit_manager\unit\unit_id.h"
#include "..\..\..\ui_manager\ui\skill_gauge\skill_gauge.h"
#include "..\..\..\ui_manager\ui\game_bg\game_bg.h"
#include "..\..\..\ui_manager\ui\player_join\player_join.h"
class CEntry : public IScene
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CEntry(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CEntry(void);

    /*!
     *  @brief      ������
     */
    void Initialize(SCENE_ID scene_id);

    /*!
     *  @brief      �X�V
     */
    void Update(void);

    /*!
     *  @brief      �`��
     */
    void Draw(void);

    /*!
     *  @brief      ���
     */
    void Finalize(void);

private:
    /*!
     *  @brief      �{�^���̒��������`�F�b�N
     */
    void CheckButtonHold(void);
    /*!
     *  @brief      �{�^���̉������`�F�b�N
     */
    void CheckButtonDown(void);
    /*!
     *  @brief      �{�^���𗣂������`�F�b�N
     */
    void CheckButtonUp(void);

    static const CVector3           m_spawn_position;       //!< �����ʒu
    static const float              m_respawn_height;       //!< ���X�|�[�������鍂��
    static const float              m_start_time;           //!< �J�n�܂ł̎���
    static const float              m_hold_start_time;      //!< �������ŊJ�n����b��
    static const float              m_exit_time;            //!< �ގ��܂łɕK�v�ȕb��
    static const CVector3           m_camera_position;      //!< �J�����̈ʒu
    static const CVector3           m_camera_direction;     //!< �J�����̌���
    static const int                m_min_player;           //!< �J�n�\�ȍŏ��l��

    UNIT_ID                         m_NextUnitID;           //!< ���ɐ�������v���C���[��ID
    UNIT_ID                         m_PlayerArray[4];       //!< ���݂��Ă���v���C���[��ID
    CTimer                          m_GameStartTimer;       //!< �Q�[���J�n�܂ł̃^�C�}�[
    CTimer                          m_HoldStartTimer;       //!< �������ŊJ�n����^�C�}�[
    CTimer                          m_HoldTimer[5];         //!< ���������Ă��鎞��
    bool                            m_WasPressd;            //!< �����t���O
    int                             m_PlayerNum;            //!< �v���C���[�̐l��
    CGameBG                         m_BackGround;           //!< �w�i
    CSkillGauge*                    m_GameStartGauge;       //!< �Q�[���J�n�܂ł̃Q�[�W
    CPlayerJoin*                    m_PlayerJoinUI;         //!< �v���C���[�Q����UI
    bool                            m_CanStartFlag;         //!< �X�^�[�g�\���ǂ���
};
