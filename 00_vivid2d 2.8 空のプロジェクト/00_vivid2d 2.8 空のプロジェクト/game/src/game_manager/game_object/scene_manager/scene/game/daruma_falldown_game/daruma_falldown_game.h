#pragma once

#include "..\game.h"

class CDaruma_FallDownGame : public CGame
{
public:
	CDaruma_FallDownGame();
	~CDaruma_FallDownGame();

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

private:

    static const CVector3           m_camera_position;
    static const CVector3           m_camera_direction;
    static const CVector3           m_ogre_position;
    static const CVector3           m_ogre_rotation;
    CTimer                          m_Timer;
    CVector3                        m_PlayerPosition[4];

    int                             m_RemainCount;

};