#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "..\..\..\controller_manager\controller\controller.h"
class CPause : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CPause(UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CPause(void);

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

    void        SetPauseController(std::shared_ptr<CController> controller);
private:
    static const vivid::Vector2     m_position;     //!< 位置
    static const int                m_height;       //!< 高さ
    static const int                m_width;        //!< 幅
    static const vivid::Rect        m_rect;         //!< 読み込み範囲
    static const vivid::Vector2     m_anchor;       //!< 基準点
    static const vivid::Vector2     m_scale;        //!< 拡縮
    static const vivid::Vector2     m_offset;       //!< 拡縮
    unsigned int                    m_Color[2];
    std::shared_ptr<CController>                    m_PauseController;
    int                             m_UINum;
    vivid::Vector2                  m_Anchor[2];
    vivid::Vector2                  m_Scale[2];
};
