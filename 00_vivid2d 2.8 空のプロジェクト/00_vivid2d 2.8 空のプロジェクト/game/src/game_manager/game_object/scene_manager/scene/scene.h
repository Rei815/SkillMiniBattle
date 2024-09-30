
/*!
 *  @file       scene.h
 *  @brief      シーンベース
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

 /*!
  *  @class      IScene
  *
  *  @brief      シーンベースクラス
  *
  *  @author     Kazuya Maruyama
  *
  *  @date       2020/11/13
  *
  *  @since      1.0
  */
class IScene
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    IScene(void);

    /*!
     *  @brief      デストラクタ
     */
    virtual ~IScene(void);

    /*!
     *  @brief      初期化
     */
    virtual void        Initialize(void);

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
};
