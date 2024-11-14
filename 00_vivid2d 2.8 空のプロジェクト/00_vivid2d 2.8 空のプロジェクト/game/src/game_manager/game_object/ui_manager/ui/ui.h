#pragma once

#include "vivid.h"
#include<vector>
#include "ui_id.h"
#include "../../../../utility/utility.h"
class CUI
{
public:
    //UIの属性
    enum class UI_ATTRIBUTE
    {
        NONE,               //!< 属性なし
        STOP_GENERATION,    //!< 敵の生成を停止
        BUTTON,             //!< 押せる
        WAVE_REWARD,        //!< 報酬を受け取れる
        MOVE,               //!< 動く
        MAX,
    };

    /*!
     *  @brief      コンストラクタ
     */
    CUI(int width, int height, UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CUI(void);

    /*!
     *  @brief      初期化
     */
    virtual void        Initialize(void);

    /*!
     *  @brief      初期化
     */
    virtual void        Initialize(const CVector3& position);

    /*!
     *  @brief      初期化
     */
    virtual void        Initialize(const CTransform& transform);

    /*!
     *  @brief      更新
     */
    virtual void        Update(void);

    /*!
     *  @brief      描画
     */
    virtual void        Draw(void);

    /*!
     *  @brief      解放
     */
    virtual void        Finalize(void);

    /*!
     *  @brief      アクティブフラグ取得
     *
     *  @return     アクティブフラグ
     */
    bool            GetActive(void);

    /*!
     *  @brief      アクティブフラグ設定
     *
     *  @param[in]  active  アクティブフラグ
     */
    void            SetActive(bool active);

    /*!
     *  @brief      UIの属性があるか
     * 
     *  @param[in]  attribute  属性
     * 
     *  @return     true 属性がある
     */
    bool            CheckAttribute(UI_ATTRIBUTE attribute);

    bool            OnMouseClick(const vivid::Vector2& position, int width, int height);

    /*!
     *  @brief      位置取得
     *
     *  @return     位置
     */
    vivid::Vector2            GetPosition(void);
    /*!
     *  @brief      長さ取得
     *
     *  @return     長さ
     */
    int            GetWidth(void);
    /*!
     *  @brief      高さ取得
     *
     *  @return     高さ
     */
    int            GetHeight(void);
    /*!
     *  @brief      ID取得
     *
     *  @return     UIのID
     */
    UI_ID            GetUI_ID(void);

protected:

    CTransform                      m_Transform;
    vivid::Vector2                  m_Position;         //!< 位置
    int                             m_Height;       //!< 高さ
    int                             m_Width;        //!< 幅
    bool                            m_ActiveFlag;   //!< アクティブフラグ
    std::vector<UI_ATTRIBUTE>       m_Attributes;    //!< 属性
    UI_ID                           m_UI_ID;
};
