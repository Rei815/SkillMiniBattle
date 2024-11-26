#include "select_skill.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "..\..\..\camera\camera.h"
#include "..\..\..\skill_manager\skill_manager.h"
#include "..\..\..\data_manager\data_manager.h"
#include "..\..\..\ui_manager\ui\ui.h"
#include "..\..\..\ui_manager\ui\skill_select_icon\skill_select_icon.h"

const float CSelectSkill::m_cursor_move_time = 0.2f;

CSelectSkill::CSelectSkill(void)
    :m_CursorMoveTimer()
    ,m_NowCursorID_Num(0)
    ,m_GameID(GAME_ID::MAX)
{

}

CSelectSkill::~CSelectSkill(void)
{
}

void CSelectSkill::Initialize(SCENE_ID scene_id)
{
    IScene::Initialize(scene_id);
    CCamera::GetInstance().Initialize();
    CCamera::GetInstance().SetPosition(CVector3(0.0f, 600.0f, -5000.0f));
    CCamera::GetInstance().SetDirection(CVector3(0.0f, 0.0f, 1.0f));
    CUIManager::GetInstance().Initialize();
    CSkillManager::GetInstance().Initialize();

    m_GameID = CDataManager::GetInstance().GetGameID();

    //スキル抽選
    ChooseSkill();
    //スキルアイコンの表示
    CreateSkillIcon();

    //アイコンの配列を初期化
    for (int i = 0; i < (int)UNIT_ID::NONE; i++)
    {
        m_SkillSelectIcon[i] = nullptr;
    }
    
    //カーソル座標のリストの初期化
    m_CursorPosNumList.clear();
    for (int i = 0; i < (int)UNIT_ID::NONE; i++)
    {
        m_CursorPosNumList.push_back(i);
    }
    m_NowCursorPosNum = 0;

    //カーソルの初期化
    SetCursorID();
    m_SkillSelectCursor = nullptr;
    CreateCursor();

    //カーソル移動タイマーのリセット
    m_CursorMoveTimer.SetUp(m_cursor_move_time);
}

void CSelectSkill::Update(void)
{
    CCamera::GetInstance().Update();
    CUIManager::GetInstance().Update();

    MoveCursor();
}

void CSelectSkill::Draw(void)
{
    CUIManager::GetInstance().Draw();


    vivid::DrawText(20, "スキル選択中", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));
}

void CSelectSkill::Finalize(void)
{
    CCamera::GetInstance().Finalize();

    CUIManager::GetInstance().Finalize();

    for (int i = 0; i < (int)UNIT_ID::NONE; i++)
    {
        m_SkillSelectIcon[i] = nullptr;
    }

    m_SkillSelectCursor = nullptr;
}

void CSelectSkill::ChooseSkill(void)
{
    ResetChooseSkill();

    std::list<int> TempSkillNumList;

    switch (m_GameID)
    {
    case GAME_ID::FALL_GAME:
        for (int i = 0; i < (int)SKILL_ID_FALLGAME::MAX; i++)
            TempSkillNumList.push_back(i);
        break;
    case GAME_ID::DODGE_BALL_GAME:
        for (int i = 0; i < (int)SKILL_ID_DODGEBALL::MAX; i++)
            TempSkillNumList.push_back(i);
        break;
    case GAME_ID::DARUMA_FALL_DOWN_GAME:
        for (int i = 0; i < (int)SKILL_ID_DARUMA::MAX; i++)
            TempSkillNumList.push_back(i);
        break;
    case GAME_ID::DEBUG_GAME:
        for (int i = 0; i < (int)SKILL_ID_DODGEBALL::MAX; i++)
            TempSkillNumList.push_back(i);
        break;
    }

    for (int i = 0; i < (int)UNIT_ID::NONE; i++)
    {
        if (!TempSkillNumList.empty())
        {
            if (TempSkillNumList.size() == 1)
            {
                m_ChooseSkillNum[i] = *(TempSkillNumList.begin());
                TempSkillNumList.clear();
            }
            else
            {
                int TempNum = rand() % (TempSkillNumList.size() - 1);
                
                m_ChooseSkillNum[i] = *(std::next(TempSkillNumList.begin(), TempNum));
                TempSkillNumList.erase(std::next(TempSkillNumList.begin(), TempNum));
            }
        }
        else
        {
            switch (m_GameID)
            {
            case GAME_ID::FALL_GAME:
                m_ChooseSkillNum[i] = (int)(SKILL_ID_FALLGAME::MAX);
                break;
            case GAME_ID::DODGE_BALL_GAME:
                m_ChooseSkillNum[i] = (int)(SKILL_ID_DODGEBALL::MAX);
                break;
            case GAME_ID::DARUMA_FALL_DOWN_GAME:
                m_ChooseSkillNum[i] = (int)(SKILL_ID_DARUMA::MAX);
                break;
            case GAME_ID::DEBUG_GAME:
                m_ChooseSkillNum[i] = (int)(SKILL_ID_DODGEBALL::MAX);
                break;
            }
        }
    }
}

void CSelectSkill::CreateSkillIcon(void)
{
    CUIManager& uim = CUIManager::GetInstance();

    CSkillSelectIcon* SkillIconUI = nullptr;

    for (int i = 0; i < (int)UNIT_ID::NONE; i++)
    {
        CUI* ui = uim.Create(UI_ID::SKILL_SELECT_ICON);
        SkillIconUI = dynamic_cast<CSkillSelectIcon*>(ui);
        
        if (SkillIconUI == nullptr) //ダウンキャストのチェック（念のため）
        {
            ui->SetActive(false);
            continue;
        }

        if (m_ChooseSkillNum[i] == -1)
        {
            switch (m_GameID)
            {
            case GAME_ID::FALL_GAME:
                SkillIconUI->SetIcon(SKILL_ID_FALLGAME::MAX, i);
                break;
            case GAME_ID::DODGE_BALL_GAME:
                SkillIconUI->SetIcon(SKILL_ID_DODGEBALL::MAX, i);
                break;
            case GAME_ID::DARUMA_FALL_DOWN_GAME:
                SkillIconUI->SetIcon(SKILL_ID_DARUMA::MAX, i);
                break;
            case GAME_ID::DEBUG_GAME:
                SkillIconUI->SetIcon(SKILL_ID_DODGEBALL::MAX, i);
                break;
            }
        }
        else
        {
            switch (m_GameID)
            {
            case GAME_ID::FALL_GAME:
                SkillIconUI->SetIcon((SKILL_ID_FALLGAME)m_ChooseSkillNum[i], i);
                break;
            case GAME_ID::DODGE_BALL_GAME:
                SkillIconUI->SetIcon((SKILL_ID_DODGEBALL)m_ChooseSkillNum[i], i);
                break;
            case GAME_ID::DARUMA_FALL_DOWN_GAME:
                SkillIconUI->SetIcon((SKILL_ID_DARUMA)m_ChooseSkillNum[i], i);
                break;
            case GAME_ID::DEBUG_GAME:
                SkillIconUI->SetIcon(SKILL_ID_DODGEBALL::MAX, i);
                break;
            }
        }

        m_SkillSelectIcon[i] = SkillIconUI;
    }
}

void CSelectSkill::ResetChooseSkill(void)
{
    for (int i = 0; i < (int)UNIT_ID::NONE; i++)
    {
        m_ChooseSkillNum[i] = 0;
    }
}

void CSelectSkill::SetCursorID(void)
{
    for (int i = 0; i < (int)UNIT_ID::NONE; i++)
    {
        if (i < CDataManager::GetInstance().GetCurrentPlayer())
        {
            //テスト用に、1Pから順番に選択
            // (実際には、順位が低い順に格納するようにする)
            m_CursorID[i] = (UNIT_ID)i;
        }
        else
        {
            m_CursorID[i] = UNIT_ID::NONE;
        }
    }

    m_NowCursorID_Num = 0;
}

void CSelectSkill::CreateCursor(void)
{
    CUI* ui = CUIManager::GetInstance().Create(UI_ID::SKILL_SELECT_CURSOR);
    m_SkillSelectCursor = nullptr;
    m_SkillSelectCursor = dynamic_cast<CSkillSelectCursor*>(ui);

    if (m_SkillSelectCursor == nullptr) //ダウンキャストのチェック（念のため）
    {
        ui->SetActive(false);
        return;
    }

    m_NowCursorPosNum = 0;

    
    m_SkillSelectCursor->SetCursor(m_CursorID[m_NowCursorID_Num], *(std::next(m_CursorPosNumList.begin(), m_NowCursorPosNum)));
}

void CSelectSkill::MoveCursor(void)
{
    m_CursorMoveTimer.Update();

    int     joyPad = 0;
    switch (m_CursorID[m_NowCursorID_Num])
    {
    case UNIT_ID::PLAYER1:
        joyPad = DX_INPUT_PAD1;
        break;
    case UNIT_ID::PLAYER2:
        joyPad = DX_INPUT_PAD2;
        break;
    case UNIT_ID::PLAYER3:
        joyPad = DX_INPUT_PAD3;
        break;
    case UNIT_ID::PLAYER4:
        joyPad = DX_INPUT_PAD4;
        break;
    }

    if (m_CursorMoveTimer.Finished())
    {
        int TempPosNum = m_NowCursorPosNum;

        if ((GetJoypadInputState(joyPad) & PAD_INPUT_RIGHT) || vivid::keyboard::Button(vivid::keyboard::KEY_ID::D))
        {
            m_NowCursorPosNum++;
            if (m_NowCursorPosNum >= m_CursorPosNumList.size())
            {
                m_NowCursorPosNum = 0;
            }
        }
        if ((GetJoypadInputState(joyPad) & PAD_INPUT_LEFT) || vivid::keyboard::Button(vivid::keyboard::KEY_ID::A))
        {
            m_NowCursorPosNum--;
            if (m_NowCursorPosNum < 0)
            {
                m_NowCursorPosNum = m_CursorPosNumList.size() - 1;
            }
        }

        if (m_NowCursorPosNum != TempPosNum)
        {
            m_CursorMoveTimer.Reset();
            m_SkillSelectCursor->SetCursor(m_CursorID[m_NowCursorID_Num], *(std::next(m_CursorPosNumList.begin(), m_NowCursorPosNum)));
        }
    }

    if ((GetJoypadInputState(joyPad) & PAD_INPUT_2) || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
    {
        //プレイヤーにスキルをセットする
        int tempSkillNum = m_ChooseSkillNum[*(std::next(m_CursorPosNumList.begin(), m_NowCursorPosNum))];
        UNIT_ID tempPlayerID = m_CursorID[m_NowCursorID_Num];

        switch (m_GameID)
        {
        case GAME_ID::FALL_GAME:
            CSkillManager::GetInstance().CreateSkill((SKILL_ID_FALLGAME)tempSkillNum, tempPlayerID);
            break;
        case GAME_ID::DODGE_BALL_GAME:
            CSkillManager::GetInstance().CreateSkill((SKILL_ID_DODGEBALL)tempSkillNum, tempPlayerID);
            break;
        case GAME_ID::DARUMA_FALL_DOWN_GAME:
            CSkillManager::GetInstance().CreateSkill((SKILL_ID_DARUMA)tempSkillNum, tempPlayerID);
            break;
        case GAME_ID::DEBUG_GAME:
            CSkillManager::GetInstance().CreateSkill((SKILL_ID_DODGEBALL)tempSkillNum, tempPlayerID);
            break;
        }

        //選択されたスキルを選択肢から取り除く
        m_CursorPosNumList.erase(std::next(m_CursorPosNumList.begin(), m_NowCursorPosNum));
        m_NowCursorPosNum = 0;

        //全員が選択を終了していない場合、次のプレイヤーのカーソルに切り替わる
        m_NowCursorID_Num++;
        if (m_NowCursorID_Num < (int)UNIT_ID::NONE &&
            m_CursorID[m_NowCursorID_Num] != UNIT_ID::NONE)
        {
            CreateCursor();
        }
        //全員が選択を終了している場合、シーンの移行を行う
        else
        {
            switch (m_GameID)
            {
            case GAME_ID::FALL_GAME:
                CSceneManager::GetInstance().ChangeScene(SCENE_ID::FALLGAME);
                break;
            case GAME_ID::DODGE_BALL_GAME:
                CSceneManager::GetInstance().ChangeScene(SCENE_ID::DODGEBALLGAME);
                break;
            case GAME_ID::DARUMA_FALL_DOWN_GAME:
                CSceneManager::GetInstance().ChangeScene(SCENE_ID::DARUMAFALLDOWN);
                break;
            case GAME_ID::DEBUG_GAME:
                CSceneManager::GetInstance().ChangeScene(SCENE_ID::DEBUGGAME);
                break;
            }
        }
    }
}