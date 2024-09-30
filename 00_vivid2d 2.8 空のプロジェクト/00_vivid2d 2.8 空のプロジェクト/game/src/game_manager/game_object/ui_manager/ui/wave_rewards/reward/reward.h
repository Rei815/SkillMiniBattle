#pragma once

#include "vivid.h"
#include "..\..\ui.h"
class CReward : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CReward(const std::string text);

    /*!
     *  @brief      デストラクタ
     */
    ~CReward(void);

    /*!
     *  @brief      初期化
     */
    virtual void        Initialize(const vivid::Vector2& position);

    /*!
     *  @brief      更新
     */
    virtual void        Update(const vivid::Vector2& position, float offset);

    /*!
     *  @brief      描画
     */
    virtual void        Draw();

    /*!
     *  @brief      解放
     */
    virtual void        Finalize(void);

protected:
    static const int                m_height;           //!< 高さ
    static const int                m_width;            //!< 幅

    vivid::Vector2                  m_Position;         //!< 位置

    std::string                     m_Text;
    bool                            m_OnClick;          //!< クリックフラグ

};
