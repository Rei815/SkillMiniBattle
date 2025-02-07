#pragma once

#include "vivid.h"
#include "..\ui.h"
class CMiniGameTitle : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CMiniGameTitle(UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CMiniGameTitle(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(void);

    /*!
     *  @brief      更新
     */
    void        Update(void);

    /*!
     *  @brief      描画
     */
    void        Draw(void);

    /*!
     *  @brief      解放
     */
    void        Finalize(void);

private:
    static const vivid::Vector2     m_position;     //!< 位置
    static const int                m_height;       //!< 高さ
    static const int                m_width;        //!< 幅

    static const std::string        m_file_name[];   //!< ファイル名
    std::string                     m_File_name;
};
