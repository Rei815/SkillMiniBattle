#pragma once

#include "..\game.h"
#include "..\..\..\..\light\light.h"

class CBeltConveyorGame : public CGame
{
public:

    /*!
     *  @brief      �R���X�g���N�^
     */
    CBeltConveyorGame(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CBeltConveyorGame(void);

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

    static const float m_defeat_height;

    static const CVector3   m_player_spawnpos_list[(int)UNIT_ID::NONE];
    static const CVector3   m_player_default_forward;

    static const CVector3   m_camera_position;
    static const CVector3   m_camera_direction;

    static const CVector3   m_belt_conveyor_position;
    static const float      m_belt_conveyor_rotate_y;
    static const float      m_belt_conveyor_scale;

    CLight                  m_StageLight;
    IObject*                m_StageObject;
};