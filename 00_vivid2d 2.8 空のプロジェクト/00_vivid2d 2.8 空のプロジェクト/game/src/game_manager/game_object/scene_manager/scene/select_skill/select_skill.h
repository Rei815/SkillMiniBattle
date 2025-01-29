#pragma once

#include <list>
#include "vivid.h"
#include "../scene.h"
#include "../game/game_id.h"
#include "../../../skill_manager/skill/skill_id.h"
#include "../../../unit_manager/unit/unit_id.h"
#include "../../../ui_manager/ui/skill_icon/skill_icon.h"
#include "../../../ui_manager/ui/skill_cursor/skill_cursor.h"
#include "../../../ui_manager/ui/skill_infomation/skill_infomation.h"
#include "../../../ui_manager/ui/skill_video/skill_video.h"

class CSelectSkill
    : public IScene
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    CSelectSkill(void);

    /*!
     *  @brief      デストラクタ
     */
    ~CSelectSkill(void);

    /*!
     *  @brief      初期化
     */
    void Initialize(SCENE_ID scene_id);

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

    void ChooseSkill(void);
    void CreateSkillIcon(void);

    SKILL_ID ConvertGameSkillID(SKILL_ID_DARUMA skill_id);
    SKILL_ID ConvertGameSkillID(SKILL_ID_DODGEBALL skill_id);
    SKILL_ID ConvertGameSkillID(SKILL_ID_FALLOUT skill_id);

private:
    void ResetChooseSkill(void);

    void SetCursorID(void);
    void CreateCursor(void);
    void MoveCursor(void);

    static const float m_cursor_move_time;

    static const vivid::Vector2 m_title_poster_scale;
    static const vivid::Vector2 m_title_poster_position;

    static const float m_icon_scale;
    static const vivid::Vector2 m_icon_positionList[];

    static const vivid::Vector2 m_icon_poster_scale;
    static const vivid::Vector2 m_icon_poster_position;

    static const float m_icon_name_scale;
    static const float m_icon_name_position_up;

    static const float m_info_scale;
    static const vivid::Vector2 m_info_position;

    static const float m_video_scale;
    static const vivid::Vector2 m_video_position;

    static const vivid::Vector2 m_video_poster_scale;

    SKILL_ID            m_ChooseSkillID[(int)UNIT_ID::NONE];
    CSkillIcon*         m_SkillSelectIcon[(int)UNIT_ID::NONE];

    std::list<CSkillCursor*> m_SkillCursorList;

    std::list<int>  m_CursorPosNumList;
    int             m_NowCursorPosNum;

    UNIT_ID         m_CursorID[(int)UNIT_ID::NONE];
    int             m_NowCursorID_Num;

    CSkillCursor*   m_SkillSelectCursor;
    CTimer          m_CursorMoveTimer;

    CSkillInfomation* m_SkillInfomation;

    CSkillVideo* m_SkillVideo;

    GAME_ID         m_GameID;
};
