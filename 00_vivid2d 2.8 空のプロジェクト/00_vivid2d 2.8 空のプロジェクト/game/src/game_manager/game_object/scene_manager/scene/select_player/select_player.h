
/*!
 *  @file       title.h
 *  @brief      タイトルシーン
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"
#include "..\scene.h"
#include "..\..\..\camera\camera.h"
#include "../../../stage/stage.h"

 /*!
  *  @class      CTitle
  *
  *  @brief      タイトルシーンクラス
  *
  *  @author     Kazuya Maruyama
  *
  *  @date       2020/11/13
  *
  *  @since      1.0
  */
class CSelect_Player
    : public IScene
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CSelect_Player(void);

    /*!
     *  @brief      デストラクタ
     */
    ~CSelect_Player(void);

    /*!
     *  @brief      初期化
     */
    void Initialize(void);

    /*!
     *  @brief      更新
     */
    void Update(void);

    /*!
     *  @brief      描画
     */
    void Draw(void);

    /*!
     *  @brief      解放
     */
    void Finalize(void);

private:
    /*!
     *  @brief  状態ID
     */
    enum class STATE
    {
        WAIT,
    };

    STATE           m_State;                //!< 状態ID
};
