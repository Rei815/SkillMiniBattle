#pragma once

#include "..\game.h"
#include "../../../../light/light.h"

class CMazeGame : public CGame
{
public:

    /*!
     *  @brief      �R���X�g���N�^
     */
    CMazeGame(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CMazeGame(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(SCENE_ID scene_id);

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

    static const CVector3           m_camera_position;          //!< �J�����̈ʒu
    static const CVector3           m_camera_direction;         //!< �J�����̕���
    static const CVector3           m_player_default_forward;   //!< �v���C���[�̃X�|�[�����̐��ʕ���
    static const CVector3           m_player_position[];   //!< �v���C���[�̈ʒu
    CLight                          m_Light;

};
