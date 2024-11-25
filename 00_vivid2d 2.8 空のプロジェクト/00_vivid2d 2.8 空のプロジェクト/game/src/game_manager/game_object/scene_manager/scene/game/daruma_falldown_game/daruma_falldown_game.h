#pragma once

#include "..\game.h"

class CDaruma_FallDownGame : public CGame
{
public:
	CDaruma_FallDownGame();
	~CDaruma_FallDownGame();

    /*!
     *  @brief      èâä˙âª
     */
    void        Initialize(SCENE_ID scene_id);

    /*!
     *  @brief      çXêV
     */
    void        Update(void);

    /*!
     *  @brief      ï`âÊ
     */
    void        Draw(void);

    /*!
     *  @brief      âï˙
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