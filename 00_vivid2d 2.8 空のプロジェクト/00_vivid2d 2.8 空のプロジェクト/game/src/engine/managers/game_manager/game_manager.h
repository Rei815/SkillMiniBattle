
/*!
 *  @file       game_manager.h
 *  @brief      ゲーム管理
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"

 /*!
  *  @class      CGameManager
  *
  *  @brief      ゲーム管理クラス
  *
  *  @author     Kazuya Maruyama
  *
  *  @date       2020/11/13
  *
  *  @since      1.0
  */
class CGameManager
{
public:
    /*!
     *  @brief      インスタンスの取得
     *
     *  @return     インスタンス
     */
    static CGameManager& GetInstance(void);

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
    /*!
     *  @brief      コンストラクタ
     */
    CGameManager(void);

    /*!
     *  @brief      コピーコンストラクタ
     *
     *  @param[in]  rhs     オブジェクト
     */
    CGameManager(const CGameManager& rhs);

    /*!
     *  @brief      デストラクタ
     */
    ~CGameManager(void);

    /*!
     *  @brief      代入演算子
     *
     *  @param[in]  rhs 代入オブジェクト
     *
     *  @return     自身のオブジェクト
     */
    CGameManager& operator=(const CGameManager& rhs);
};
