#pragma once
#include "../../unit_manager/unit/player/player.h"

class CPlayer;

class CSkill
{
public:
    CSkill(void);
    ~CSkill(void);

    /*!
     *  @brief      ������
     */
    virtual void    Initialize(CPlayer* player);

    /*!
     *  @brief      �X�V
     */
    virtual void    Update(void);

    /*!
     *  @brief      �`��
     */
    virtual void    Draw(void);

    /*!
     *  @brief      ���
     */
    virtual void    Finalize(void);

    /*!
     *  @brief      �A�N�V�����Ăяo��
     */
    virtual void    Action(void);

protected:
    CPlayer* m_Player;
};