#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "..\..\..\scene_manager\scene\game\game_id.h"
#include "..\..\..\..\..\primitive\primitive.h"

class CPlaneGameImage : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CPlaneGameImage(UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CPlaneGameImage(void);

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

    /*!
     *  @brief      設定されているゲームのIDを取得
     * 
     *  @return     ゲームのID
     */
    GAME_ID     GetGameID(void);

    /*!
     *  @brief      設定されているゲームのIDを設定
     * 
     *  @param[in]  game_id     ゲームのID
     */
    void        SetGameID(GAME_ID game_id);

    /*!
     *  @brief      トランスフォーム設定
     *
     *  @param[in]  transform  トランスフォーム
     */
    void            SetTransform(const CTransform& transform);

    /*!
     *  @brief      中心位置からの角度設定
     *
     *  @param[in]  angle  中心位置からの角度
     */
    void            SetPosAngle(float angle);

    /*!
     *  @brief      移動速度設定
     *
     *  @param[in]  speed  移動速度
     */
    void            SetSpeed(float speed);
private:


    static const std::string        m_file_names[];
    static const int                m_height;           //!< 高さ
    static const int                m_width;            //!< 幅
    static const vivid::Rect        m_rect;             //!< 読み込み範囲
    static const vivid::Vector2     m_anchor;           //!< 基準点
    static const vivid::Vector2     m_scale;            //!< 拡縮
    static const float              m_rotation_speed;
    static const float              m_speed;

    float                           m_Speed;
    std::string                     m_FileName;
    int                             m_Width;
    int                             m_Height;
    int                             m_Handle;
    float                           m_Angle;
    float                           m_PosAngle;
    CPlane                          m_Plane;
    CVector3                        m_InitialPosition;  //!< 初期位置
    GAME_ID                         m_GameID;
    CMatrix                         m_Matrix;
};
