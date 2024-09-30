#pragma once

#include "vivid.h"
#include <string>
#include "..\ui.h"

class CWaveCounter : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CWaveCounter(void);

    /*!
     *  @brief      デストラクタ
     */
    ~CWaveCounter(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(void);

    /*!
     *  @brief      更新
     */
    void        Update(vivid::Vector2 position);

    /*!
     *  @brief      描画
     */
    void        Draw(void);

    /*!
     *  @brief      解放
     */
    void        Finalize(void);

    /*!
     *  @brief      位置設定
     */
    void        SetPosition(vivid::Vector2 position);

private:
    static const vivid::Vector2     m_position;     //!< 位置
    static const int                m_font_size;    //!< 文字の大きさ

    int                             m_MaxWave;      //!< Wave最大数
    int                             m_CurrentWave;  //!< 現在のWave
    std::string                     m_Text;         //!< テキスト
};
