#pragma once

#include "..\player.h"

class CPlayer2 : public CPlayer
{
public:

    CPlayer2();

    ~CPlayer2();

    /*!
     *  @brief      初期化
     *
     *  @param[in]  position    初期位置
     */
    virtual void        Initialize(const CVector3& position, MOVE_ID moveId);

private:
    static const DxLib::COLOR_F     m_color;
    static const std::string        m_file_name;        //!< 読み込むファイル名

};