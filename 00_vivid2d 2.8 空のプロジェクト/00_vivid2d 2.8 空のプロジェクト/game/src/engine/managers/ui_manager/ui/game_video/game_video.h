#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../scene_manager/scene/game/game_id.h"

class CGameVideo : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CGameVideo(UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CGameVideo(void);

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

    void        SetGameVideo(GAME_ID game_id);

private:
    static const int                m_height;                   //!< 高さ
    static const int                m_width;                    //!< 幅
    static const float              m_scale;                    //!< 拡大率
    static const vivid::Vector2     m_position;                 //!< 位置
    static const std::string        m_file_name[];   //!< ファイル名

    int                             m_Handle;                   //!< ハンドル
};
