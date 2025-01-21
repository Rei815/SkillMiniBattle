
/*!
 *  @file       sound_manager.h
 *  @brief      サウンド管理
 *  @author     Kazuya Maruyama
 *  @date       2020/11/13
 *  @since      1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "vivid.h"

 /*!
  *  @brief      サウンドID
  */
enum class SOUND_ID
{
    BGM,
    SHOT,
    HOMING_SHOT,
    DESTORY,
    BOSS_DESTORY,
    PLAYER_HIT,
    WARNING,
    WARNING_SHORT,
    GAMEOVER,
    GAMECLEAR,//配列9番目
    //↓ここから追加分
    DECIDE_BUTTON,


    MAIN_BGM,
    RESULT_BGM,

    MAX
};

/*!
 *  @class      CSoundManager
 *
 *  @brief      サウンド管理クラス
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
class CSoundManager
{
public:
    /*!
     *  @brief      インスタンスの取得
     *
     *  @return     インスタンス
     */
    static CSoundManager& GetInstance(void);

    /*!
     *  @brief      サウンドの読み込み
     */
    void        Load(void);

    /*!
     *  @brief      再生
     *
     *  @param[in]  id      サウンドID
     *  @param[in]  loop    ループフラグ
     */
    void        Play(SOUND_ID id, bool loop = false);
    void        Stop(SOUND_ID id);

private:
    /*!
     *  @brief      コンストラクタ
     */
    CSoundManager(void);

    /*!
     *  @brief      コピーコンストラクタ
     *
     *  @param[in]  rhs     オブジェクト
     */
    CSoundManager(const CSoundManager& rhs);

    /*!
     *  @brief      デストラクタ
     */
    ~CSoundManager(void);

    /*!
     *  @brief      代入演算子
     *
     *  @param[in]  rhs 代入オブジェクト
     *
     *  @return     自身のオブジェクト
     */
    CSoundManager& operator=(const CSoundManager& rhs);

    static const char* m_sound_file_names[(int)SOUND_ID::MAX];    //!< サウンドのファイル名
};
