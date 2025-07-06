#pragma once

#include "vivid.h"
#include "..\ui.h"
#include <memory>
#include "../../../../utility/timer/timer.h"

/*!
 *  @brief      �}�[�NID
 */
enum class MARK_ID
{
    CIRCLE,     //!< �ۃ}�[�N
    CROSS,      //!< �o�c�}�[�N
    MOON,       //!< ���}�[�N
    SQUARE,     //!< �l�p�}�[�N
    SUN,        //!< ���z�}�[�N
    TRIANGLE,   //!< �O�p�}�[�N
    NONE,
};
class CFallOutTopic : public CUI
{
public:
    enum class STATE
    {
        APPEAR,     //!< �o��
        WAIT,       //!< �������Ȃ�
        SWITCHING,  //!< �G���؂�ւ�葱���Ă�����
        PICK_UP,    //!< �G�����܂������
        FINISH      //!< �Q�[���I�����̏��
    };

    /*!
     *  @brief      �R���X�g���N�^
     */
    CFallOutTopic(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CFallOutTopic(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(const vivid::Vector2& position);

    /*!
     *  @brief      �X�V
     */
    void        Update(void);

    /*!
     *  @brief      �`��
     */
    void        Draw(void);

    /*!
     *  @brief      ���
     */
    void        Finalize(void);

    void        SetMarkID(MARK_ID markID);

    void        SetTimer(float time);

    STATE       GetState();

    void        SetState(CFallOutTopic::STATE state);
private:
    static const std::string        m_file_name;        //!< �t�@�C����
    static const int                m_height;           //!< ����
    static const int                m_width;            //!< ��
    static const vivid::Rect        m_rect;             //!< �ǂݍ��ݔ͈�
    static const vivid::Vector2     m_anchor;           //!< ��_
    static const vivid::Vector2     m_scale;            //!< �g�k
    static const vivid::Vector2     m_adjust_position;  //!< �w�i�Ƃ̒����l
    static const float              m_speed;            //!< �����̑��x
    static const float              m_change_time;      //!< �؂�ւ�鎞��
    static const float              m_wait_time;        //!< �ҋ@����
    static const float              m_end_y;            //!< �o�����̒�~���鍂��
    static const float              m_end_time;         //!< �I������
    float                           m_EaseTimer;        //!< �J�n����
    float                           m_StartValue;       //!< �J�n�l
    float                           m_FinishValue;      //!< �I���l
    float                           m_Time;
    std::string                     m_FileName;
    vivid::Rect                     m_Rect;
    CTimer                          m_Timer;
    CTimer                          m_SelectTimer;      //!< ���肪���܂�܂ł̎���
    CTimer                          m_StopTimer;
    MARK_ID                         m_CurrentID;        //!< �����ID

    STATE                           m_State;
    std::shared_ptr<CUI>            m_BackGround;

};
