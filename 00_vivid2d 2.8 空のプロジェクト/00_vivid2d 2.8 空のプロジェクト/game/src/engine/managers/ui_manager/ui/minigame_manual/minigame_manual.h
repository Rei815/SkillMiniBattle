#pragma once

#include "vivid.h"
#include "..\ui.h"
class CMiniGameManual : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CMiniGameManual(UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CMiniGameManual(void);

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
    static const vivid::Vector2     m_bg_position;  //!< 背景の位置
    static const vivid::Vector2     m_bg_scale;     //!< 背景の大きさ
    static const vivid::Vector2     m_manual_scale; //!< 操作説明の文字の大きさ

    static const int                m_height;       //!< 高さ
    static const int                m_width;        //!< 幅

    static const std::string        m_file_name[];   //!< ファイル名
    std::string                     m_FileName;
};
