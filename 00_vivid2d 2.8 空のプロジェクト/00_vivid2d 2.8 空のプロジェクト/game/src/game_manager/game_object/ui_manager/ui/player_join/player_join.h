#include "..\ui.h"
#include "..\..\..\unit_manager\unit\unit_id.h"

class CPlayerJoin : public CUI
{
public:
    CPlayerJoin(UI_ID id);
    ~CPlayerJoin();

    /*!
     *  @brief      初期化
     */
    void        Initialize();

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
     *  @brief      プレイヤー参加状況のセット
     */
    void        SetPlayer(UNIT_ID id, bool join);

private:
    static const std::string        m_file_names[];
    static const int                m_height;           //!< 高さ
    static const int                m_width;            //!< 幅
    static const vivid::Vector2     m_offset;           //!< 画像同士の幅
    static const vivid::Vector2     m_position;         //!< 位置
    static const unsigned int       m_color_dark;       //!< 色
    static const unsigned int       m_color_light;      //!< 色

    static const vivid::Rect        m_rect;             //!< 読み込み範囲
    static const vivid::Vector2     m_anchor;           //!< 基準点
    static const vivid::Vector2     m_scale;            //!< 拡縮
    unsigned int                    m_Color[4];          //!< 色
    bool                            m_ReadyFlag;        //!< 準備完了のフラグ
};