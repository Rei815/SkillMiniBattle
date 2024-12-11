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
     *  @brief      �R���X�g���N�^
     */
    CSelectSkill(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CSelectSkill(void);

    /*!
     *  @brief      ������
     */
    void Initialize(SCENE_ID scene_id);

    /*!
     *  @brief      �X�V
     */
    void Update(void);

    /*!
     *  @brief      �`��
     */
    void Draw(void);

    /*!
     *  @brief      ���
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

    SKILL_ID            m_ChooseSkillID[(int)UNIT_ID::NONE];
    CSkillSelectIcon*   m_SkillSelectIcon[(int)UNIT_ID::NONE];

    std::list<int> m_CursorPosNumList;
    int m_NowCursorPosNum;

    UNIT_ID m_CursorID[(int)UNIT_ID::NONE];
    int m_NowCursorID_Num;

    CSkillSelectCursor* m_SkillSelectCursor;
    CTimer m_CursorMoveTimer;

    GAME_ID m_GameID;
};
