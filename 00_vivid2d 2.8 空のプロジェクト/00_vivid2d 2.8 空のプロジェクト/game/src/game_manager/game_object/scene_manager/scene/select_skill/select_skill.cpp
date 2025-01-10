#include "select_skill.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "..\..\..\camera\camera.h"
#include "..\..\..\skill_manager\skill_manager.h"
#include "..\..\..\data_manager\data_manager.h"
#include "..\..\..\ui_manager\ui\ui.h"
#include "..\..\..\ui_manager\ui\skill_icon\skill_icon.h"

const float CSelectSkill::m_cursor_move_time = 0.2f;
const float CSelectSkill::m_icon_scale = 0.4f;
const vivid::Vector2    CSelectSkill::m_icon_positionList[] =
{
    vivid::Vector2( 256, 360),		//Player1
    vivid::Vector2( 512, 360),		//Player2
    vivid::Vector2( 768, 360),		//Player3
    vivid::Vector2( 1024, 360)		//Player4
};

CSelectSkill::CSelectSkill(void)
    :m_CursorMoveTimer()
    ,m_NowCursorID_Num(0)
    , m_SkillSelectCursor(nullptr)
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

    //カーソルリストの初期化
    m_SkillCursorList.clear();

    //カーソル移動タイマーのリセット
    m_CursorMoveTimer.SetUp(m_cursor_move_time);

    //スキル抽選
    ChooseSkill();
    //スキルアイコンの表示
    CreateSkillIcon();

    //カーソルの初期化
    SetCursorID();
    m_SkillSelectCursor = nullptr;
    CreateCursor();
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


    vivid::DrawText(20, "スキル選択中, ENTERキーで決定", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));
}

void CSelectSkill::Finalize(void)
{
    CCamera::GetInstance().Finalize();

    for (int i = 0; i < (int)UNIT_ID::NONE; i++)
    {
        if (m_SkillSelectIcon[i] != nullptr)
        {
            m_SkillSelectIcon[i]->SetActive(false);
            m_SkillSelectIcon[i] = nullptr;
        }
    }

    if (m_SkillCursorList.size() != 0)
    {
        std::list<CSkillCursor*>::iterator it = m_SkillCursorList.begin();
        while (it != m_SkillCursorList.end())
        {
            (*it)->SetActive(false);
            ++it;
        }
    }

    if (m_SkillSelectCursor != nullptr)
    {
        m_SkillSelectCursor->SetActive(false);
        m_SkillSelectCursor = nullptr;
    }
}

void CSelectSkill::ChooseSkill(void)
{
    ResetChooseSkill();

    std::list<SKILL_ID> TempSkillNumList;

    //候補の取り出し
    switch (m_GameID)
    {
    case GAME_ID::FALL_GAME:
        for (int i = 0; i < (int)SKILL_ID_FALLOUT::MAX; i++)
            TempSkillNumList.push_back(ConvertGameSkillID((SKILL_ID_FALLOUT)i));
        break;
    case GAME_ID::DODGE_BALL_GAME:
        for (int i = 0; i < (int)SKILL_ID_DODGEBALL::MAX; i++)
            TempSkillNumList.push_back(ConvertGameSkillID((SKILL_ID_DODGEBALL)i));
        break;
    case GAME_ID::DARUMA_FALL_DOWN_GAME:
        for (int i = 0; i < (int)SKILL_ID_DARUMA::MAX; i++)
            TempSkillNumList.push_back(ConvertGameSkillID((SKILL_ID_DARUMA)i));
        break;
    case GAME_ID::DEBUG_GAME:
        for (int i = 0; i < (int)SKILL_ID_DODGEBALL::MAX; i++)
            TempSkillNumList.push_back(ConvertGameSkillID((SKILL_ID_DODGEBALL)i));
        break;
    }

    //抽選
    for (int i = 0; i < (int)UNIT_ID::NONE; i++)
    {
        if (!TempSkillNumList.empty())
        {
            if (TempSkillNumList.size() == 1)
            {
                m_ChooseSkillID[i] = *(TempSkillNumList.begin());
                TempSkillNumList.clear();
            }
            else
            {
                int TempNum = rand() % TempSkillNumList.size();
                
                m_ChooseSkillID[i] = *(std::next(TempSkillNumList.begin(), TempNum));
                TempSkillNumList.erase(std::next(TempSkillNumList.begin(), TempNum));
            }
        }
        else
        {
            m_ChooseSkillID[i] = SKILL_ID::MAX;
        }
    }
}

void CSelectSkill::ResetChooseSkill(void)
{
    for (int i = 0; i < (int)UNIT_ID::NONE; i++)
    {
        m_ChooseSkillID[i] = SKILL_ID::MAX;
    }
}

void CSelectSkill::CreateSkillIcon(void)
{
    CUIManager& uim = CUIManager::GetInstance();

    CSkillIcon* SkillIconUI = nullptr;

    for (int i = 0; i < (int)UNIT_ID::NONE; i++)
    {
        CUI* ui = uim.Create(UI_ID::SKILL_ICON);
        SkillIconUI = dynamic_cast<CSkillIcon*>(ui);
        
        if (SkillIconUI == nullptr) //ダウンキャストのチェック
        {
            ui->SetActive(false);
            continue;
        }

        SkillIconUI->SetIcon(m_ChooseSkillID[i], m_icon_positionList[i],m_icon_scale);

        m_SkillSelectIcon[i] = SkillIconUI;
    }
}

void CSelectSkill::SetCursorID(void)
{
    int CurrentPlayer = CDataManager::GetInstance().GetCurrentPlayer();

    for (int i = 0; i < (int)UNIT_ID::NONE; i++)
    {
        if (i < CurrentPlayer)
        {
            m_CursorID[i] = CDataManager::GetInstance().GetLastGameRanking((CurrentPlayer - 1) - i);
        }
        else
        {
            m_CursorID[i] = UNIT_ID::NONE;
        }
    }

    m_NowCursorID_Num = 0;
    CDataManager::GetInstance().ResetLastGameRanking();
}

void CSelectSkill::CreateCursor(void)
{
    CUI* ui = CUIManager::GetInstance().Create(UI_ID::SKILL_CURSOR);
    if (m_SkillSelectCursor != nullptr)
    {
        m_SkillCursorList.push_back(m_SkillSelectCursor);
        m_SkillSelectCursor = nullptr;
    }
    m_SkillSelectCursor = dynamic_cast<CSkillCursor*>(ui);

    if (m_SkillSelectCursor == nullptr) //ダウンキャストのチェック
    {
        ui->SetActive(false);
        return;
    }

    m_NowCursorPosNum = 0;

    
    m_SkillSelectCursor->SetCursor(m_CursorID[m_NowCursorID_Num], m_icon_positionList[*(std::next(m_CursorPosNumList.begin(), m_NowCursorPosNum))], m_icon_scale);
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
            m_SkillSelectCursor->SetPosition(m_icon_positionList[*(std::next(m_CursorPosNumList.begin(), m_NowCursorPosNum))]);
        }
    }

    if ((GetJoypadInputState(joyPad) & PAD_INPUT_2) || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RETURN))
    {
        //プレイヤーにスキルをセットする
        SKILL_ID tempSkillID = m_ChooseSkillID[*(std::next(m_CursorPosNumList.begin(), m_NowCursorPosNum))];
        UNIT_ID tempPlayerID = m_CursorID[m_NowCursorID_Num];

        CSkillManager::GetInstance().CreateSkill(tempSkillID, tempPlayerID);

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

SKILL_ID CSelectSkill::ConvertGameSkillID(SKILL_ID_DARUMA skill_id)
{
    SKILL_ID temp = SKILL_ID::MAX;

    switch (skill_id)
    {
    case SKILL_ID_DARUMA::DASH:
        temp = SKILL_ID::DASH;
        break;
    case SKILL_ID_DARUMA::SPEED_UP:
        temp = SKILL_ID::SPEED_UP;
        break;
    case SKILL_ID_DARUMA::INVISIBLE:
        temp = SKILL_ID::INVISIBLE;
        break;
    case SKILL_ID_DARUMA::STUN:
        temp = SKILL_ID::STUN;
        break;
    case SKILL_ID_DARUMA::MIMICRY:
        temp = SKILL_ID::MIMICRY;
        break;
    case SKILL_ID_DARUMA::SLOW:
        temp = SKILL_ID::SLOW;
        break;
    case SKILL_ID_DARUMA::OGRE_CONTOROL:
        temp = SKILL_ID::OGRE_CONTOROL;
        break;
    case SKILL_ID_DARUMA::RESURRECT_DARUMA:
        temp = SKILL_ID::RESURRECT_DARUMA;
        break;
    case SKILL_ID_DARUMA::MAX:
        temp = SKILL_ID::MAX;
        break;
    }

    return temp;
}

SKILL_ID CSelectSkill::ConvertGameSkillID(SKILL_ID_DODGEBALL skill_id)
{
    SKILL_ID temp = SKILL_ID::MAX;

    switch (skill_id)
    {
    case SKILL_ID_DODGEBALL::SPEED_UP:
        temp = SKILL_ID::SPEED_UP;
        break;
    case SKILL_ID_DODGEBALL::JUMP_UP:
        temp = SKILL_ID::JUMP_UP;
        break;
    case SKILL_ID_DODGEBALL::DASH:
        temp = SKILL_ID::DASH;
        break;
    case SKILL_ID_DODGEBALL::SPAWN_WALL:
        temp = SKILL_ID::SPAWN_WALL;
        break;
    case SKILL_ID_DODGEBALL::BARRIER:
        temp = SKILL_ID::BARRIER;
        break;
    case SKILL_ID_DODGEBALL::GRAVITY_AREA:
        temp = SKILL_ID::GRAVITY_AREA;
        break;
    case SKILL_ID_DODGEBALL::FLOATING:
        temp = SKILL_ID::FLOATING;
        break;
    case SKILL_ID_DODGEBALL::STRONG_WIND:
        temp = SKILL_ID::STRONG_WIND;
        break;
    case SKILL_ID_DODGEBALL::MAX:
        temp = SKILL_ID::MAX;
        break;
    }

    return temp;
}

SKILL_ID CSelectSkill::ConvertGameSkillID(SKILL_ID_FALLOUT skill_id)
{
    SKILL_ID temp = SKILL_ID::MAX;

    switch (skill_id)
    {
    case SKILL_ID_FALLOUT::SPEED_UP:
        temp = SKILL_ID::SPEED_UP;
        break;
    case SKILL_ID_FALLOUT::JUMP_UP:
        temp = SKILL_ID::JUMP_UP;
        break;
    case SKILL_ID_FALLOUT::FLOATING:
        temp = SKILL_ID::FLOATING;
        break;
    case SKILL_ID_FALLOUT::STOMP:
        temp = SKILL_ID::STOMP;
        break;
    case SKILL_ID_FALLOUT::RESURRECT:
        temp = SKILL_ID::RESURRECT_FALLOUT;
        break;
    case SKILL_ID_FALLOUT::STRONG_WIND:
        temp = SKILL_ID::STRONG_WIND;
        break;
    case SKILL_ID_FALLOUT::MAX:
        temp = SKILL_ID::MAX;
        break;
    }

    return temp;
}