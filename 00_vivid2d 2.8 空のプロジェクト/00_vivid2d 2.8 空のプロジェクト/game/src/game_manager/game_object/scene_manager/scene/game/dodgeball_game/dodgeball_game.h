#pragma once

#include "..\game.h"
#include "..\..\..\..\ui_manager\ui\ui_id.h"
#include "../../../../sound_manager/sound_manager.h"


enum class CANNON_DIRECTION
{
    UP,
    DOWN,
    RIGHT,
    LEFT,

    MAX,
};

class CDodgeBallGame : public CGame
{
public:

    /*!
     *  @brief      �R���X�g���N�^
     */
    CDodgeBallGame(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CDodgeBallGame(void);

    /*!
     *  @brief      ������
     */
    void Initialize(SCENE_ID scene_id);
    
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

    /*!
     *  @brief      �I������
     */
    void    CheckFinish(void) override;

    void SpawnCannnon(void);

    IObject* ChooseCannon(void);


    static const CVector3 m_cannon_pos_list[];
    static const CVector3 m_cannon_rot_list[];
    static const CVector3 m_player_spawnpos_list[];
    static const CVector3 m_player_default_forward; //!< �v���C���[�̃X�|�[�����̐��ʕ���

    static const int        m_max_cannnon_count;
    static const float      m_cannnon_spawn_time;
    static const float      m_initial_shot_time;
    static const float      m_min_shot_time;
    static const float      m_shot_time_acceleration;

    static const float      m_defeat_distance;

    static const float      m_stage_shrink_time;

    static const CVector3   m_camera_position;
    static const CVector3   m_camera_direction;

    int                 m_CannonCount;
    CTimer              m_SpawnTimer;
    CTimer              m_ShotTimer;
    float               m_NowShotTime;
    CTimer              m_StageShrinkTimer;
    bool                m_StageShrinkFlg;
    IObject*            m_StageObject;
    CANNON_DIRECTION    m_NextCannnonDir;
    CSoundManager*      m_bgm;
};
