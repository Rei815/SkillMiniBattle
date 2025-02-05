#include "select_skill.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "..\..\..\camera\camera.h"
#include "..\..\..\skill_manager\skill_manager.h"
#include "..\..\..\data_manager\data_manager.h"
#include "..\..\..\ui_manager\ui\ui.h"
#include "..\..\..\ui_manager\ui\skill_icon\skill_icon.h"
#include "..\..\..\ui_manager\ui\skill_name\skill_name.h"
#include "../../../sound_manager/sound_manager.h"


const float             CSelectSkill::m_cursor_move_time = 0.2f;

const vivid::Vector2    CSelectSkill::m_title_poster_scale = vivid::Vector2(2.0f, 0.2f);
const vivid::Vector2    CSelectSkill::m_title_poster_position = vivid::Vector2(vivid::WINDOW_WIDTH / 2.0f, vivid::WINDOW_HEIGHT / 6.0f);

const vivid::Vector2    CSelectSkill::m_icon_positionList[] =
{
    vivid::Vector2( vivid::WINDOW_WIDTH / 8.0f * 1.0f, vivid::WINDOW_HEIGHT / 7.0f * 3),		//Player1
    vivid::Vector2( vivid::WINDOW_WIDTH / 8.0f * 3.0f, vivid::WINDOW_HEIGHT / 7.0f * 3),		//Player2
    vivid::Vector2( vivid::WINDOW_WIDTH / 8.0f * 5.0f, vivid::WINDOW_HEIGHT / 7.0f * 3),		//Player3
    vivid::Vector2( vivid::WINDOW_WIDTH / 8.0f * 7.0f, vivid::WINDOW_HEIGHT / 7.0f * 3) 		//Player4
};

const vivid::Vector2    CSelectSkill::m_icon_poster_scale = vivid::Vector2(4.0f, 0.8f);
const vivid::Vector2    CSelectSkill::m_icon_poster_position = vivid::Vector2(vivid::WINDOW_WIDTH / 2.0f, vivid::WINDOW_HEIGHT / 5.0f * 2.0f);

const float             CSelectSkill::m_icon_scale = 0.3f;
const float             CSelectSkill::m_icon_name_scale = 0.1f;
const float             CSelectSkill::m_icon_name_position_up = 110.0f;

const float             CSelectSkill::m_info_scale = 0.5f;
const vivid::Vector2    CSelectSkill::m_info_position = vivid::Vector2(vivid::WINDOW_WIDTH / 4.0f * 3.0f, vivid::WINDOW_HEIGHT / 4.0f * 3.0f);

const float             CSelectSkill::m_video_scale = 0.5f;
const vivid::Vector2    CSelectSkill::m_video_position = vivid::Vector2(vivid::WINDOW_WIDTH / 4.0f * 1.0f, vivid::WINDOW_HEIGHT / 4.0f * 3.0f);

const vivid::Vector2    CSelectSkill::m_video_poster_scale = vivid::Vector2(1.5f, 0.8f);

CSelectSkill::CSelectSkill(void)
    :m_CursorMoveTimer()
    ,m_NowCursorID_Num(0)
    ,m_NowCursorPosNum(0)
    , m_SkillSelectIcon{nullptr}
    , m_SkillSelectCursor(nullptr)
    , m_SkillInfomation(nullptr)
    ,m_SkillVideo(nullptr)
    ,m_GameID(GAME_ID::MAX)
{

}

CSelectSkill::~CSelectSkill(void)
{
}

void CSelectSkill::Initialize(SCENE_ID scene_id)
{
    IScene::Initialize(scene_id);
    CSkillManager::GetInstance().Initialize();

    m_GameID = CDataManager::GetInstance().GetSelectGameID();

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

    //バックグラウンド表示
    CUIManager::GetInstance().Create(UI_ID::MENU_BG);

    CUIManager::GetInstance().Create(UI_ID::SCENE_TITLE);

    CUI* ui = CUIManager::GetInstance().Create(UI_ID::MENU_POSTER, m_icon_poster_position);
    ui->SetScale(m_icon_poster_scale);

    //スキル抽選
    ChooseSkill();
    //スキルアイコンの表示
    CreateSkillIcon();

    //カーソルの初期化
    SetCursorID();
    m_SkillSelectCursor = nullptr;

    //スキル説明の生成
    CUI* SkillInfo = CUIManager::GetInstance().Create(UI_ID::SKILL_INFO);
    m_SkillInfomation = dynamic_cast<CSkillInfomation*>(SkillInfo);
    if (m_SkillInfomation == nullptr)
    {
        SkillInfo->SetActive(false);
    }
    else
    {
        m_SkillInfomation->SetPosition(m_info_position);
        m_SkillInfomation->SetScale(m_info_scale);
    }

    //スキル動画の生成
    ui = CUIManager::GetInstance().Create(UI_ID::MENU_POSTER, m_video_position);
    ui->SetScale(m_video_poster_scale);

    CUI* SkillVideo = CUIManager::GetInstance().Create(UI_ID::SKILL_VIDEO);
    m_SkillVideo = dynamic_cast<CSkillVideo*>(SkillVideo);
    if (m_SkillVideo == nullptr)
    {
        SkillVideo->SetActive(false);
    }
    else
    {
        for (int i = 0; i < (int)UNIT_ID::NONE; i++)
        {
            m_SkillVideo->SetSkillVideo(i, m_ChooseSkillID[i]);
        }
        m_SkillVideo->SetSkillNum(0);
        m_SkillVideo->SetPosition(m_video_position);
        m_SkillVideo->SetScale(m_video_scale);
    }
    IScene* scene = (*CSceneManager::GetInstance().GetList().begin());
    m_SceneUIParent = (CSceneUIParent*)CUIManager::GetInstance().Create(UI_ID::SCENE_UI_PARENT, vivid::Vector2(vivid::GetWindowWidth() / 2, -vivid::GetWindowHeight() / 2));
    m_SceneUIParent->SetState(CSceneUIParent::STATE::MOVE_ONE);
}

void CSelectSkill::Update(void)
{
    MoveCursor();

    if (m_SceneUIParent)
    {
        if (m_SceneUIParent->GetState() == CSceneUIParent::STATE::WAIT)
        {
            m_SceneUIParent->ReleaseChildren();
            CUIManager::GetInstance().Delete(m_SceneUIParent);
            m_SceneUIParent = nullptr;
            CreateCursor();
        }
    }
}

void CSelectSkill::Draw(void)
{
}

void CSelectSkill::Finalize(void)
{
    CCamera::GetInstance().Finalize();
    CUIManager::GetInstance().Finalize();
    for (int i = 0; i < (int)UNIT_ID::NONE; i++)
    {
        if (m_SkillSelectIcon[i] != nullptr)
        {
            m_SkillSelectIcon[i]->SetActive(false);
            m_SkillSelectIcon[i] = nullptr;
        }
    }

    if (!m_SkillCursorList.empty())
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

    if (m_SkillInfomation != nullptr)
    {
        m_SkillInfomation->SetActive(false);
        m_SkillInfomation = nullptr;
    }

    if (m_SkillVideo != nullptr)
    {
        m_SkillVideo->SetActive(false);
        m_SkillVideo = nullptr;
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

/*
* スキルアイコンの生成
*/
void CSelectSkill::CreateSkillIcon(void)
{
    CUIManager& uim = CUIManager::GetInstance();
    CSkillName* SkillNameUI = nullptr;
    CSkillIcon* SkillIconUI = nullptr;

    for (int i = 0; i < (int)UNIT_ID::NONE; i++)
    {
        CUI* ui = uim.Create(UI_ID::SKILL_NAME);
        SkillNameUI = dynamic_cast<CSkillName*>(ui);
        if (SkillNameUI == nullptr) //ダウンキャストのチェック
        {
            ui->SetActive(false);
        }
        else
        {
            SkillNameUI->SetData(m_ChooseSkillID[i], m_icon_positionList[i] - vivid::Vector2(0.0f, m_icon_name_position_up), m_icon_name_scale);
        }

        ui = uim.Create(UI_ID::SKILL_ICON);

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
    if (m_SceneUIParent != nullptr) return;

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

            m_SkillVideo->SetSkillNum(*(std::next(m_CursorPosNumList.begin(), m_NowCursorPosNum)));
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

        //まだ選択を終了していないプレイヤーがいる場合、次のプレイヤーのカーソルに切り替わる
        m_NowCursorID_Num++;
        if (m_NowCursorID_Num < (int)UNIT_ID::NONE &&
            m_CursorID[m_NowCursorID_Num] != UNIT_ID::NONE)
        {
            CreateCursor();
            m_SkillVideo->SetSkillNum(*(std::next(m_CursorPosNumList.begin(), m_NowCursorPosNum)));
        }
        //全員が選択を終了している場合、シーンの移行を行う
        else if(m_SceneUIParent == nullptr)
        {
            switch (m_GameID)
            {
            case GAME_ID::FALL_GAME:
                CSoundManager::GetInstance().Play_SE(SE_ID::SCENE_MOVE, false);
                CSceneManager::GetInstance().ChangeScene(SCENE_ID::FALLGAME);
                break;
            case GAME_ID::DODGE_BALL_GAME:
                CSoundManager::GetInstance().Play_SE(SE_ID::SCENE_MOVE, false);
                CSceneManager::GetInstance().ChangeScene(SCENE_ID::DODGEBALLGAME);
                break;
            case GAME_ID::DARUMA_FALL_DOWN_GAME:
                CSoundManager::GetInstance().Play_SE(SE_ID::SCENE_MOVE, false);
                CSceneManager::GetInstance().ChangeScene(SCENE_ID::DARUMAFALLDOWN);
                break;
            case GAME_ID::DEBUG_GAME:
                CSoundManager::GetInstance().Play_SE(SE_ID::SCENE_MOVE, false);
                CSceneManager::GetInstance().ChangeScene(SCENE_ID::DEBUGGAME);
                break;
            }
        }
    }

    if (m_SkillInfomation != nullptr && !m_CursorPosNumList.empty() && m_NowCursorID_Num < (int)UNIT_ID::NONE && m_CursorID[m_NowCursorID_Num] != UNIT_ID::NONE)
    {
        m_SkillInfomation->SetSkillInfo(m_ChooseSkillID[*(std::next(m_CursorPosNumList.begin(), m_NowCursorPosNum))]);
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
    case SKILL_ID_FALLOUT::HIDE_TOPIC:
        temp = SKILL_ID::HIDE_TOPIC;
        break;
    case SKILL_ID_FALLOUT::MAX:
        temp = SKILL_ID::MAX;
        break;
    }

    return temp;
}