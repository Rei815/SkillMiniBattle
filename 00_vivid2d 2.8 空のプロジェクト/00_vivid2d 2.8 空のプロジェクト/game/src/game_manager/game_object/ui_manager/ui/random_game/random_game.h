#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "..\..\..\scene_manager\scene\game\game_id.h"
#include "..\..\..\..\..\primitive\primitive.h"

class CRandomGame : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CRandomGame(UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CRandomGame(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(const CTransform& transform);

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


    void        SetGameID(GAME_ID game_id);
private:


    static const std::string        m_file_names[];
    static const int                m_height;       //!< 高さ
    static const int                m_width;        //!< 幅
    static const vivid::Rect        m_rect;         //!< 読み込み範囲
    static const vivid::Vector2     m_anchor;       //!< 基準点
    static const vivid::Vector2     m_scale;        //!< 拡縮
    static const float              m_rotation_speed;
    static const float              m_speed;

    std::string                     m_FileName;
    int                             m_Width;
    int                             m_Height;
    int                             m_Handle;
    float                           m_Angle;
    float                           m_PosAngle;
    CPlane                          m_Plane;
    CVector3                        m_InitialPosition;     //!< 初期位置
};
