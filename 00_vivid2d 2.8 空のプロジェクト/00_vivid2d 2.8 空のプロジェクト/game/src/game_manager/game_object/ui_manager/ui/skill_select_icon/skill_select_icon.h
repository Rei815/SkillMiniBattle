#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../skill_manager/skill/skill_id.h"

class CSkillSelectIcon : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CSkillSelectIcon(UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CSkillSelectIcon(void);

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

    void        SetIcon(SKILL_ID_FALLGAME skill_id, int PosNum);
    void        SetIcon(SKILL_ID_DARUMA skill_id, int PosNum);
    void        SetIcon(SKILL_ID_DODGEBALL skill_id, int PosNum);

private:
    static const vivid::Vector2     m_positionList[];   //!< 位置
    static const int                m_height;           //!< 高さ
    static const int                m_width;            //!< 幅
    static const vivid::Rect        m_rect;             //!< 読み込み範囲
    static const vivid::Vector2     m_anchor;           //!< 基準点
    static const vivid::Vector2     m_scale;            //!< 拡縮

    static const std::string        m_fallgameFileName[];
    static const std::string        m_darumaFileName[];
    static const std::string        m_dodgeballFileName[];

    bool                            m_Selected;

    std::string                     m_FileName;
};
