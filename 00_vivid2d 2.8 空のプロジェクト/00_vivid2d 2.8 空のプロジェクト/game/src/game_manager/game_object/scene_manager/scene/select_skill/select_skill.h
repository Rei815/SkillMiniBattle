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
    void Initialize(void);

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
