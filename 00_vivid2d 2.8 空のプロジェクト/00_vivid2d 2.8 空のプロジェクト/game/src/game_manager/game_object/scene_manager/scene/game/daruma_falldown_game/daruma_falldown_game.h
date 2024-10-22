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

    CTimer                          m_Timer;
};