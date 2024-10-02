#pragma once

#include "..\player.h"

class CPlayer1 : public CPlayer
{
public:

    CPlayer1();

    ~CPlayer1();

    /*!
     *  @brief      ������
     *
     *  @param[in]  position    �����ʒu
     */
    virtual void        Initialize(const CVector3& position, MOVE_ID moveId);

private:
    static const DxLib::COLOR_F        m_color;
};