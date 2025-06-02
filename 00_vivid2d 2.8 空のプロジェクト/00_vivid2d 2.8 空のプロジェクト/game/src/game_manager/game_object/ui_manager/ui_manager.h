#pragma once

#include "vivid.h"
#include "ui/ui.h"
#include <list>
#include <memory>
 /*!
  *  @brief      UIマネージャークラス
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
     *  @param[in]  layerNum    UIの描画順
     */
    CUI*        Create(UI_ID id);

    /*!
     *  @brief      UI生成
     *
     *  @param[in]  id          UIのID
     *  @param[in]  position    UIの位置
     */
    CUI*        Create(UI_ID id, const vivid::Vector2& position);

    /*!
     *  @brief      UI生成
     *
     *  @param[in]  id          UIのID
     *  @param[in]  position    UIの位置
     */
    CUI*        Create(UI_ID id, const CVector3& position);

    /*!
     *  @brief      UI生成
     *
     *  @param[in]  id          UIのID
     *  @param[in]  transform    UIのトランスフォーム
     */
    CUI*        Create(UI_ID id, const CTransform& transform);

    /*!
     *  @brief      UI削除
     *
     *  @param[in]  id          UIのID
     */
    void        Delete(UI_ID id);

    /*!
     *  @brief      UIリスト型
     */
    using UI_LIST = std::list<std::shared_ptr<CUI>>;

    /*!
     *  @brief      リスト取得
     *
     *  @return     オブジェクトリスト
     */
    UI_LIST         GetList();

    /*!
     *  @brief      レイヤー内の番号をもとに並び替え
     */
    void            SortList(void);

    /*
    *  @brief       UI取得
    *               複数ある場合最初に作られたものが返ってくる
     * @param[in]   ui_id          UIのID
    *  @return      オブジェクトリスト
    */
    CUI*            GetUI(UI_ID ui_id);

private:
    UI_LIST             m_UIList;             //!< UIリスト

    /*!
     *  @brief              UIのクラスを作成
     *
     *  @param[in]  id      UIのID
     */
    std::shared_ptr<CUI>    CreateClass(UI_ID id);


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

};