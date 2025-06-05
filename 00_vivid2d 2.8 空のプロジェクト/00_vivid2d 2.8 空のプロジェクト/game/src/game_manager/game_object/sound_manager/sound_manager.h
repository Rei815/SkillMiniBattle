#pragma once

#include "vivid.h"

 /*!
  *  @brief      サウンドID
  */


enum class BGM_ID
{
    MAIN_BGM,
    RESULT_BGM,
    READY_BGM,

    MAX
};

enum class SE_ID
{
    BARRIER,
    CANCEL_BUTTON,
    CANNON_SHOT,
    DASH,
    DECIDE_BUTTON,
    FALLOUT_DECIDE,
    FALLOUT_RAFFLE,
    FLOATING,
    GAME_DECIDE,
    GAME_FINISH,
    GAME_RAFFLE,
    GAME_START,
    GRAVITYAREA,
    HIDETOPIC,
    INVISIBLE,
    KEYGET,
    MIMICRY,
    RESURECT,
    SCENE_MOVE,
    SELECT,
    SKILL,
    SLOW,
    SPAWN_WALL,
    STOMP,
    STRONG_WIND,
    STUN,
    REFLECTION,
    MAX
};

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
    void        Load_BGM(void);
    void        Load_SE(void);

    /*!
     *  @brief      再生
     *
     *  @param[in]  id      サウンドID
     *  @param[in]  loop    ループフラグ
     */

    void        Play_BGM(BGM_ID id, bool loop = false);
    void        Stop_BGM(BGM_ID id);
    void        SetBGMVolume(BGM_ID id, int volume = 1);


    void        Play_SE(SE_ID id, bool loop = false);
    void        Stop_SE(SE_ID id);
    void        SetSEVolume(SE_ID id, int volume = 1);

    /*
    *　解放
    */
    virtual void    Finalize(void);

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


    static const char* m_se_file_names[(int)SE_ID::MAX];      //!< SEのファイル名
    static const char* m_bgm_file_names[(int)BGM_ID::MAX];    //!< BGMのファイル名
};
