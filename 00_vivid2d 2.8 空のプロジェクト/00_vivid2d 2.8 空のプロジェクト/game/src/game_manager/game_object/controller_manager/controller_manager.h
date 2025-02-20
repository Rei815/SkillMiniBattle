#pragma once

#include "vivid.h"
#include "..\..\..\utility\utility.h"
#include <list>
#include "controller/controller.h"

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
    void        Initialize(void);

    /*!
     *  @brief      更新
     */
    void        Update(void);

    /*!
     *  @brief      解放
     */
    void        Finalize(void);

    /*!
     *  @brief      コントローラーの数を設定
     * 
     *  @param[in]  num          コントローラーの数
     */
    void SetControllerNum(int num);

    /*!
     *  @brief      コントローラーの数を取得
     *  @return     コントローラーの数
     */
    int GetControllerNum();

    /*!
     *  @brief      コントローラー生成
     *
     *  @param[in]  id          コントローラーID
     */
    CController* Create(CONTROLLER_ID id);

    /*!
     *  @brief      コントローラーを取得
     */
    CController* GetController(CONTROLLER_ID controller_id);

    /*!
     *  @brief      コントローラーを振動させる
     *
     *  @param[in]  controller_id          コントローラーのID
     */
    void Vibration(CONTROLLER_ID controller_id);

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

    int             m_ControllerNum;

    std::list<vivid::controller::DEVICE_ID>         m_ControllerIDList;
    using CONTROLLER_LIST = std::list<CController*>;

    CONTROLLER_LIST                                 m_ControllerList;
};
