#include "select_skill.h"
#include "..\..\scene_manager.h"
#include "..\..\..\game_object.h"
#include "..\..\..\camera\camera.h"
#include "..\..\..\skill_manager\skill_manager.h"
#include "..\..\..\ui_manager\ui\ui.h"
#include "..\..\..\ui_manager\ui\skill_select_icon\skill_select_icon.h"

const float CSelectSkill::m_cursor_move_time = 0.5f;

CSelectSkill::CSelectSkill(void)
    :m_NextGameID(GAME_ID::MAX)
    ,m_CursorMoveTimer()
{

}

CSelectSkill::~CSelectSkill(void)
{
}

void CSelectSkill::Initialize(void)
{
    CCamera::GetInstance().Initialize();
    CCamera::GetInstance().SetPosition(CVector3(0.0f, 600.0f, -5000.0f));
    CCamera::GetInstance().SetDirection(CVector3(0.0f, 0.0f, 1.0f));
    CUIManager::GetInstance().Initialize();

    //�X�L�����I�̃Z�b�g
    m_NextGameID = GAME_ID::MAX;
    ResetChooseSkill();

    //�A�C�R���̔z���������
    for (int i = 0; i < (int)UNIT_ID::NONE; i++)
    {
        m_SkillSelectIcon[i] = nullptr;
    }
    
    //�J�[�\�����W�̃��X�g�̏�����
    m_CursorPosNumList.clear();
    for (int i = 0; i < (int)UNIT_ID::NONE; i++)
    {
        m_CursorPosNumList.push_back(i);
    }
    m_NowCursorPosNum = 0;

    //�e�X�g�p�ɁA1P���珇�ԂɑI��
    m_CursorID = UNIT_ID::PLAYER1;

    //�J�[�\���̏�����
    m_SkillSelectCursor = nullptr;

    CreateCursor();

    //�J�[�\���ړ��^�C�}�[�̃��Z�b�g
    m_CursorMoveTimer.SetUp(m_cursor_move_time);
}

void CSelectSkill::Update(void)
{
    CCamera::GetInstance().Update();
    CUIManager::GetInstance().Update();
}

void CSelectSkill::Draw(void)
{
    CUIManager::GetInstance().Draw();


    vivid::DrawText(20, "�X�L���I��", vivid::Vector2(0, vivid::WINDOW_HEIGHT - 20));
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

void CSelectSkill::SetNextGameID(GAME_ID game_id)
{
    m_NextGameID = game_id;
}

void CSelectSkill::ChooseSkill(void)
{
    ResetChooseSkill();

    std::list<int> TempSkillNumList;

    switch (m_NextGameID)
    {
    case GAME_ID::FALL_GAME:
        for (int i = 0; i < (int)SKILL_ID_FALLGAME::MAX; i++)
            TempSkillNumList.push_back(i);
        break;
    case GAME_ID::DODGE_BALL_GAME:
        for (int i = 0; i < (int)SKILL_ID_DODGEBALL::MAX; i++)
            TempSkillNumList.push_back(i);
        break;
    case GAME_ID::DEBUG_GAME:
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
            switch (m_NextGameID)
            {
            case GAME_ID::FALL_GAME:
                m_ChooseSkillNum[i] = (int)(SKILL_ID_FALLGAME::MAX);
                break;
            case GAME_ID::DODGE_BALL_GAME:
                m_ChooseSkillNum[i] = (int)(SKILL_ID_DODGEBALL::MAX);
                break;
            case GAME_ID::DEBUG_GAME:
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
        
        if (SkillIconUI == nullptr) //�_�E���L���X�g�̃`�F�b�N�i�O�̂��߁j
        {
            ui->SetActive(false);
            continue;
        }

        if (m_ChooseSkillNum[i] == -1)
        {
            switch (m_NextGameID)
            {
            case GAME_ID::FALL_GAME:
                SkillIconUI->SetIcon(SKILL_ID_FALLGAME::MAX, i);
                break;
            case GAME_ID::DODGE_BALL_GAME:
                SkillIconUI->SetIcon(SKILL_ID_DODGEBALL::MAX, i);
                break;
            case GAME_ID::DEBUG_GAME:
                SkillIconUI->SetIcon(SKILL_ID_DODGEBALL::MAX, i);
                break;
            }
        }
        else
        {
            switch (m_NextGameID)
            {
            case GAME_ID::FALL_GAME:
                SkillIconUI->SetIcon((SKILL_ID_FALLGAME)m_ChooseSkillNum[i], i);
                break;
            case GAME_ID::DODGE_BALL_GAME:
                SkillIconUI->SetIcon((SKILL_ID_DODGEBALL)m_ChooseSkillNum[i], i);
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
        m_ChooseSkillNum[i] = -1;
    }
}


void CSelectSkill::CreateCursor(void)
{
    CUI* ui = CUIManager::GetInstance().Create(UI_ID::SKILL_SELECT_CURSOR);
    m_SkillSelectCursor = nullptr;
    m_SkillSelectCursor = dynamic_cast<CSkillSelectCursor*>(ui);

    if (m_SkillSelectCursor == nullptr) //�_�E���L���X�g�̃`�F�b�N�i�O�̂��߁j
    {
        ui->SetActive(false);
        return;
    }

    m_NowCursorPosNum = 0;

    
    m_SkillSelectCursor->SetCursor(m_CursorID, *(std::next(m_CursorPosNumList.begin(), m_NowCursorPosNum)));
}

void CSelectSkill::MoveCursor(void)
{
    m_CursorMoveTimer.Update();

    //�e�X�g�p�A���ۂɂ͊e�v���C���[�̃R���g���[���[������͂��擾
    if (m_CursorMoveTimer.Finished())
    {
        int TempPosNum = m_NowCursorPosNum;

        if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::D))
        {
            m_NowCursorPosNum++;
            if (m_NowCursorPosNum >= m_CursorPosNumList.size())
            {
                m_NowCursorPosNum = 0;
            }
        }
        if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::A))
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
            m_SkillSelectCursor->SetCursor(m_CursorID, *(std::next(m_CursorPosNumList.begin(), m_NowCursorPosNum)));
        }
    }

    if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::RETURN))
    {
        //�v���C���[�ɃX�L�����Z�b�g����i�������j


        //�I�����ꂽ�X�L����I���������菜��
        m_CursorPosNumList.remove(m_NowCursorPosNum);

        //�e�X�g�p�A���ۂ͎��ɏ��ʂ��Ⴂ�v���C���[�ɂȂ�
        //�S�����I�����I�����Ă���ꍇ�̓V�[���̈ڍs���s��
        if ((int)(m_CursorID)+1 >= (int)(UNIT_ID::NONE))
            m_CursorID = (UNIT_ID)((int)(m_CursorID)+1);
        CreateCursor();
    }
}