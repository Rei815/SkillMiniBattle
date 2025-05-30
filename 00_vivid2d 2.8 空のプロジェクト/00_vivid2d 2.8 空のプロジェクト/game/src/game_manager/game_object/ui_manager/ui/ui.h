#pragma once

#include "vivid.h"
#include<vector>
#include "ui_id.h"
#include "../../../../utility/utility.h"
#include "../../scene_manager/scene/scene_id.h"
class CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CUI(UI_ID id);
    /*!
     *  @brief      コンストラクタ
     */
    CUI(int width, int height, UI_ID id, int layer = 0);

    /*!
     *  @brief      デストラクタ
     */
    ~CUI(void);

    /*!
     *  @brief      初期化
     */
    virtual void    Initialize(void);

    /*!
     *  @brief      初期化
     * 
     *  @param[in]  position    位置(3D)
     */
    virtual void    Initialize(const CVector3& position);

    /*!
     *  @brief      初期化
     *
     *  @param[in]  position    位置(2D)
     */
    virtual void    Initialize(const vivid::Vector2& position);

    /*!
     *  @brief      初期化
     *
     *  @param[in]  transform   トランスフォーム
     */
    virtual void    Initialize(const CTransform& transform);

    /*!
     *  @brief      更新
     */
    virtual void    Update(void);

    /*!
     *  @brief      描画
     */
    virtual void    Draw(void);

    /*!
     *  @brief      解放
     */
    virtual void    Finalize(void);

    /*!
     *  @brief      アクティブフラグ取得
     *
     *  @return     アクティブフラグ
     */
    bool            IsActive(void);

    /*!
     *  @brief      アクティブフラグ設定
     *
     *  @param[in]  active  アクティブフラグ
     */
    void            SetActive(bool active);

    /*!
     *  @brief      位置取得
     *
     *  @return     位置
     */
    vivid::Vector2  GetPosition(void);
    /*!
     *  @brief      長さ取得
     *
     *  @return     長さ
     */
    int             GetWidth(void);
    /*!
     *  @brief      高さ取得
     *
     *  @return     高さ
     */
    int             GetHeight(void);
    /*!
     *  @brief      ID取得
     *
     *  @return     UIのID
     */
    UI_ID           GetUI_ID(void);

    /*!
     *  @brief      拡大率取得
     *
     *  @return     拡大率
     */
    vivid::Vector2  GetScale(void);

    /*!
     *  @brief      ID設定
     *
     *  @param[in]  id  UIのID
     */
    void            SetUI_ID(UI_ID id);

    /*!
     *  @brief      位置設定
     *
     *  @param[in]  position  位置
     */
    void            SetPosition(const vivid::Vector2& position);

    /*!
     *  @brief      拡大率設定
     *
     *  @param[in]  scale  拡大率
     */
    void            SetScale(float scale);

    /*!
     *  @brief      拡大率設定
     *
     *  @param[in]  scale  拡大率
     */
    void            SetScale(const vivid::Vector2& scale);

    /*!
     *  @brief      トランスフォーム取得
     *
     *  @return     トランスフォーム
     */
    CTransform      GetTransform(void);

    /*!
     *  @brief      トランスフォーム設定
     *
     *  @param[in]  transform  トランスフォーム
     */
    void            SetTransform(const CTransform& transform);

    /*!
     *  @brief      親のオブジェクト取得
     *
     *  @return     親のオブジェクト
     */
    CUI*            GetParent(void);

    /*!
     *  @brief      親のトランスフォーム設定
     *
     *  @param[in]  parent  親のトランスフォーム
     */
    void            SetParent(CUI* parent);

    /*!
     *  @brief      レイヤー内番号取得
     *
     *  @return     レイヤー
     */
    int             GetOrderInLayer(void);

    /*!
     *  @brief      レイヤー内番号設定
     *
     *  @param[in]  num  レイヤー内番号
     */
    void            SetOrderInLayer(int num);

    /*!
     *  @brief      レイヤー内番号の比較
     */
    bool operator<(const CUI& r) const;

    /*!
     *  @brief      設定されているシーンのIDを取得
     *
     *  @return     シーンID
     */
    SCENE_ID        GetSceneID(void);

protected:

    /*!
     *  @brief      移動ベクトルの取得
     * 
     *  @return     Vector3     ベクトル
     */
    CVector3        GetVelocity();

    CTransform                      m_Transform;        //!< トランスフォーム
    vivid::Vector2                  m_Position;         //!< 位置
    int                             m_Height;           //!< 高さ
    int                             m_Width;            //!< 幅
    bool                            m_ActiveFlag;       //!< アクティブフラグ
    UI_ID                           m_UI_ID;            //!< ID
    vivid::Vector2                  m_Scale;            //!< 拡大率
    CUI*                            m_Parent;           //!< 親のポインタ
    int                             m_OrderInLayer;     //!< 描画順
    CVector3                        m_Velocity;         //!< 移動ベクトル
    SCENE_ID                        m_SceneID;          //!< シーンID
};
