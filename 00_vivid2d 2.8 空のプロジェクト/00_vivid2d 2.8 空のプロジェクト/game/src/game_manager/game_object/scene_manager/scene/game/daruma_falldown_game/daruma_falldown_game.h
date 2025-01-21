#pragma once

#include "..\game.h"
#include "../../../../sound_manager/sound_manager.h"

class CDaruma_FallDownGame : public CGame
{
public:
	CDaruma_FallDownGame();
	~CDaruma_FallDownGame();

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

    /*!
 *  @brief      ���
 */
    void        Ranking(void);

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

    static const CVector3           m_camera_position;          //�J�����̃|�W�V����
    static const CVector3           m_camera_direction;         //�J�����̊p�x
    static const CVector3           m_ogre_position;            //�S�̃|�W�V����
    static const CVector3           m_ogre_rotation;
    static const float              m_move_speed;

    IObject* m_OgreObject;
    CTimer                          m_Timer;
    CVector3                        m_PlayerPosition[4];
    int                             m_RemainCount;
    int                             m_TempFirstNum;
    int                             m_CountTime;
    float                           m_TempFirstDis;
    bool                            m_GimmickOn;
    SOUND_ID                        m_Sound;
};