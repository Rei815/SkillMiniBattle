#pragma once

#include "..\player.h"

class CPlayer1 : public CPlayer
{
public:

    CPlayer1();

    ~CPlayer1();

    /*!
     *  @brief      ‰Šú‰»
     *
     *  @param[in]  position    ‰ŠúˆÊ’u
     */
    virtual void        Initialize(const CVector3& position, MOVE_ID moveId, bool aimFlag);

private:
    static const DxLib::COLOR_F        m_color;
};