#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../scene_manager/scene/scene_id.h"

class CSceneTitle : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CSceneTitle(UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CSceneTitle(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(vivid::Vector2 position);

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

    void        SetData(SCENE_ID scene_id, vivid::Vector2 position, float scale);
    void        SetData(SCENE_ID scene_id, vivid::Vector2 position, vivid::Vector2 scale);

    void        SetSceneInfo(SCENE_ID scene_id);

    void        SetPosition(const vivid::Vector2& position);

private:
    static const int                m_height;           //!< 高さ
    static const int                m_width;            //!< 幅
    static const vivid::Rect        m_rect;             //!< 読み込み範囲
    static const vivid::Vector2     m_anchor;           //!< 基準点
    static const vivid::Vector2     m_default_scale;    //!< 拡縮
    static const vivid::Vector2     m_default_position;


    static const std::string        m_scene_title_file_name[(int)SCENE_ID::MAX];
    std::string                     m_FileName;
};
