#pragma once

#include "vivid.h"
#include <list>
#include "controller/controller.h"
#include <memory>
class CControllerManager
{
public:
    /*!
     *  @brief      インスタンスの取得
     *
     *  @return     インスタンス
     */
    static CControllerManager& GetInstance(void);


    /*!
     *  @brief      初期化
     */
    void            Initialize(void);

    /*!
     *  @brief      更新
     */
    void            Update(void);

    /*!
     *  @brief      解放
     */
    void            Finalize(void);

    /*!
     *  @brief      コントローラーの数を設定
     * 
     *  @param[in]  num          コントローラーの数
     */
    void            SetControllerNum(int num);

    /*!
     *  @brief      コントローラーの数を取得
     *  @return     コントローラーの数
     */
    int             GetControllerNum();

    /*!
     *  @brief      コントローラー生成
     *
     *  @param[in]  id          コントローラーID
     */
    std::shared_ptr<CController>    Create(CONTROLLER_ID id);

    /*!
     *  @brief      コントローラーを取得
     */
    std::shared_ptr<CController>    GetController(CONTROLLER_ID controller_id);

    /*!
     *  @brief      いずれかのコントローラーのボタンの状態を取得
     *  @return     指定のボタンが押されたか
     */
    bool            GetAnyControllerButtonDown(BUTTON_ID button_id);

    /*!
     *  @brief      コントローラーを振動させる
     *
     *  @param[in]  controller_id          コントローラーのID
     */
    void            Vibration(CONTROLLER_ID controller_id);

    /*!
     *  @brief      指定のボタンを押したコントローラーを取得
     *  @param[in]  button_id    指定のボタン
     *  @return     std::shared_ptr<CController>    コントローラー
     */
    std::shared_ptr<CController>    GetSpecifiedButtonDownController(BUTTON_ID button_id);

    /*!
     *  @brief      指定のボタンを離したコントローラーを取得
     *  @param[in]  button_id    指定のボタン
     *  @return     std::shared_ptr<CController>    コントローラー
     */
    std::shared_ptr<CController>    GetSpecifiedButtonUpController(BUTTON_ID button_id);

    /*!
     *  @brief      指定のボタンを押しているコントローラーを取得
     *  @param[in]  button_id    指定のボタン
     *  @return     std::shared_ptr<CController>    コントローラー
     */
    std::shared_ptr<CController>    GetSpecifiedButtonHoldController(BUTTON_ID button_id);

    using CONTROLLER_LIST = std::list<std::shared_ptr<CController>>;

    /*!
     *  @brief      リストを取得
     *  @return     コントローラーリスト
     */
    CONTROLLER_LIST GetList();

private:

    /*!
     *  @brief      コンストラクタ
     */
    CControllerManager(void);

    /*!
     *  @brief      コピーコンストラクタ
     *
     *  @param[in]  rhs     オブジェクト
     */
    CControllerManager(const CControllerManager& rhs);

    /*!
     *  @brief      デストラクタ
     */
    ~CControllerManager(void);

    /*!
     *  @brief      代入演算子
     *
     *  @param[in]  rhs 代入オブジェクト
     *
     *  @return     自身のオブジェクト
     */
    CControllerManager& operator=(const CControllerManager& rhs);

    CONTROLLER_LIST                                 m_ControllerList;   //!< コントローラーのリスト
    int                                             m_ControllerNum;    //!< コントローラー数

};
