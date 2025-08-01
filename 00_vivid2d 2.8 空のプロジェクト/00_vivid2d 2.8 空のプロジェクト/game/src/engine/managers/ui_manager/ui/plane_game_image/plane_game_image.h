#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "..\..\..\scene_manager\scene\game\game_id.h"
#include "../../../animation_manager/animation/animation.h"
#include "../../../../primitive/plane/plane.h"

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
    GAME_ID         GetGameID(void);

    /*!
     *  @brief      ゲームのIDを設定
     * 
     *  @param[in]  game_id     ゲームのID
     */
    void            SetGameID(GAME_ID game_id);

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

    /*!
     *  @brief      アニメーション取得
     *
     *  @return     アニメーション
     */
    std::shared_ptr<IAnimation>     GetAnimation(void);

    /*!
     *  @brief      アニメーション設定
     *
     *  @param[in]  animation  アニメーション
     */
    void            SetAnimation(std::shared_ptr<IAnimation> animation);

private:


    static const std::string        m_file_names[];
    static const int                m_height;           //!< 高さ
    static const int                m_width;            //!< 幅
    static const vivid::Rect        m_rect;             //!< 読み込み範囲
    static const vivid::Vector2     m_anchor;           //!< 基準点
    static const CVector3           m_scale;            //!< 拡縮
    static const float              m_rotation_speed;
    static const float              m_speed;            //!< 位置を軸に回転する速さ

    float                           m_Speed;
    std::string                     m_FileName;
    int                             m_Width;
    int                             m_Height;
    int                             m_Handle;
    float                           m_Angle;            //!< 自身の回転
    float                           m_PosAngle;         //!< 位置を軸に回転
    CPlane                          m_Plane;            //!< 平面
    CVector3                        m_InitialPosition;  //!< 初期位置
    GAME_ID                         m_GameID;           //!< 画像のゲームID
    CMatrix                         m_Matrix;
    std::shared_ptr<IAnimation>     m_Animation;
};
