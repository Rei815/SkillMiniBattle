#pragma once

#include "..\player.h"

class CPlayer2 : public CPlayer
{
public:

    CPlayer2();

    ~CPlayer2();

    /*!
     *  @brief      ‰Šú‰»
     *
     *  @param[in]  position    ‰ŠúˆÊ’u
     */
    virtual void        Initialize(const CVector3& position, MOVE_ID moveId, bool aimFlag);

private:
    static const DxLib::COLOR_F        m_color;
};