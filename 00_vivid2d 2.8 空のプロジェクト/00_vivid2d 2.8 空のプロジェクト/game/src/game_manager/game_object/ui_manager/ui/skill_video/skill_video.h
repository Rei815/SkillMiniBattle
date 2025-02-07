#pragma once

#include "vivid.h"
#include "..\ui.h"
#include "../../../skill_manager/skill/skill_id.h"
#include "../../../unit_manager/unit/unit_id.h"

class CSkillVideo : public CUI
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CSkillVideo(UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CSkillVideo(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(const vivid::Vector2& position);

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

    void        SetPosition(const vivid::Vector2& position);

    void        SetScale(float scale);
    void        SetScale(const vivid::Vector2& scale);

    void        SetSkillVideo(int skill_num, SKILL_ID skill_id);
    void        ResetSkillVideo();

    void        SetSkillNum(int skill_num);

private:
    static const int                m_height;           //!< 高さ
    static const int                m_width;            //!< 幅
    static const vivid::Vector2     m_default_scale;    //!< 拡縮
    static const vivid::Vector2     m_default_position; //!< 座標

    static const std::string        m_skill_video_file_name[];
    int                             m_Handle[(int)UNIT_ID::NONE];
    SKILL_ID                        m_HandleSkillID[(int)UNIT_ID::NONE];

    vivid::Vector2  m_CenterPos;
    int             m_NowSkillNum;
};