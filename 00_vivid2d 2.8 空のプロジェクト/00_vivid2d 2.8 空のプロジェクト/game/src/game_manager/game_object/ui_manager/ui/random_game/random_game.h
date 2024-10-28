#pragma once

#include "vivid.h"
#include "..\ui.h"
class CRandomGame : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CRandomGame(void);

    /*!
     *  @brief      デストラクタ
     */
    ~CRandomGame(void);

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

    void Draw3DRot(const CVector3& position, float _x_rot, float _y_rot, float _z_rot);

    static const TCHAR*             m_file_name;
    CVector3     m_Position;     //!< 位置
    static const int                m_height;       //!< 高さ
    static const int                m_width;        //!< 幅
    static const vivid::Rect        m_rect;         //!< 読み込み範囲
    static const vivid::Vector2     m_anchor;       //!< 基準点
    static const vivid::Vector2     m_scale;        //!< 拡縮

    int                             m_Width;
    int                             m_Height;
    int                             m_Handle;
    float                           m_Angle;
};
