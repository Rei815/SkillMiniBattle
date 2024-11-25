#pragma once

#include <list>
#include "vivid.h"
#include "../scene.h"
#include "../game/game_id.h"
#include "../../../skill_manager/skill/skill_id.h"
#include "../../../unit_manager/unit/unit_id.h"
#include "../../../ui_manager/ui/skill_select_icon/skill_select_icon.h"
#include "../../../ui_manager/ui/skill_select_cursor/skill_select_cursor.h"

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

    void SetNextGameID(GAME_ID game_id);
    void ChooseSkill(void);
    void CreateSkillIcon(void);

private:
    void ResetChooseSkill(void);

    void CreateCursor(void);
    void MoveCursor(void);

    static const float m_cursor_move_time;

    GAME_ID             m_NextGameID;
    int                 m_ChooseSkillNum[(int)UNIT_ID::NONE];
    CSkillSelectIcon*   m_SkillSelectIcon[(int)UNIT_ID::NONE];

    std::list<int> m_CursorPosNumList;
    int m_NowCursorPosNum;

    UNIT_ID m_CursorID;
    CSkillSelectCursor* m_SkillSelectCursor;
    CTimer m_CursorMoveTimer;
};
