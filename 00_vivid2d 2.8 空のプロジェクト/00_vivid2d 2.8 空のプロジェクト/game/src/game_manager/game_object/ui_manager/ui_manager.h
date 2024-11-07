
/*!
 *  @file       ui_manager.h
 *  @brief      UI管理
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"
#include "ui/ui.h"
#include <list>
 /*!
  *  @class      CUIManager
  *
  *  @brief      UI管理クラス
  *
  *  @author     Kazuya Maruyama
  *
  *  @date       2020/11/13
  *
  *  @since      1.0
  */
class CUIManager
{
public:
    /*!
     *  @brief      インスタンスの取得
     *
     *  @return     インスタンス
     */
    static CUIManager& GetInstance(void);

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

    /*!
     *  @brief      UI生成
     *
     *  @param[in]  id          UIのID
     */
    void        Create(UI_ID id);

    /*!
     *  @brief      UI生成
     *
     *  @param[in]  id          UIのID
     *  @param[in]  position    UIの位置
     */
    void        Create(UI_ID id, const CVector3& position);

    /*!
     *  @brief      UI生成
     *
     *  @param[in]  id          UIのID
     *  @param[in]  transform    UIのトランスフォーム
     */
    void        Create(UI_ID id, const CTransform& transform);

    /*!
     *  @brief      UI削除
     *
     *  @param[in]  id          UIのID
     */
    void        Delete(UI_ID id);

    /*!
     *  @brief      指定の属性のUIがあるか確認
     *
     *  @return     true:UIがある
     */
    bool        CheckUIAttribute(CUI::UI_ATTRIBUTE ui_attribute);


    /*!
     *  @brief      報酬を受け取ったかを取得
     *
     *  @return     報酬を受け取ったかどうか
     * 
     */
    bool GetReceivedReward(void);

    /*!
     *  @brief      報酬を受け取ったかを設定
     *
     */
    void SetReceivedReward(bool active);

    /*!
     *  @brief      WaveClearUIのアクティブを取得
     *
     *  @return     WaveClearUIのアクティブ
     * 
     */
    bool GetWaveClearUIActive(void);

    /*!
     *  @brief      WaveClearUIのアクティブを設定
     *
     */
    void SetWaveClearUIActive(bool active);

    /*!
     *  @brief      指定のUIのアクティブを取得
     *
     *  @return     1  アクティブ
     *  @return     0 非アクティブ
     *  @return     -1 存在しない
     *
     */
    int GetUIActive(UI_ID ui_id);

private:
    /*!
     *  @brief      コンストラクタ
     */
    CUIManager(void);

    /*!
     *  @brief      コピーコンストラクタ
     *
     *  @param[in]  rhs     オブジェクト
     */
    CUIManager(const CUIManager& rhs);

    /*!
     *  @brief      デストラクタ
     */
    ~CUIManager(void);

    /*!
     *  @brief      代入演算子
     *
     *  @param[in]  rhs 代入オブジェクト
     *
     *  @return     自身のオブジェクト
     */
    CUIManager& operator=(const CUIManager& rhs);

    /*!
     *  @brief      UIリスト型
     */
    using UI_LIST = std::list<CUI*>;

    UI_LIST             m_UIList;             //!< UIリスト


    bool                m_ReceivedReward;
    bool                m_WaveClearUIActiveFlag;
};