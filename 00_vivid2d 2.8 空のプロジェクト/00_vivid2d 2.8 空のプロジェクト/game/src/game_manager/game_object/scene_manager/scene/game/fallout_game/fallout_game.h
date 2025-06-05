#pragma once

#include "..\game.h"
#include "..\..\..\..\ui_manager\ui\ui_id.h"
#include "../../../../ui_manager/ui/fallout_topic/fallout_topic.h"
#include <memory>
#include <array>
#include <random>
class CFallOutGame : public CGame
{
public:

    /*!
     *  @brief      �R���X�g���N�^
     */
    CFallOutGame(void);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CFallOutGame(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(SCENE_ID scene_id);

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


private:

    //�����鏰�̃|�C���^�ƃ}�[�N
    struct FALL_OBJECT�QINFO
    {
        IObject*    object;
        MARK_ID     markID = MARK_ID::CIRCLE;
    };

    /*!
     *  @brief      �X�^�[�g
     */
    void    Start(void);

    /*!
     *  @brief      �v���C
     */
    void    Play(void);

    /*!
     *  @brief      ����̑I��
     */
    void    ChooseTopic(void);

    /*!
     *  @brief      ����̃��Z�b�g
     */
    void    ResetTopic(void);

    /*!
     *  @brief      ����̒ǉ�
     */
    void    AddTopic(void);

    /*!
     *  @brief      ������I�u�W�F�N�g�̑I��
     * 
     *  @return     �I�u�W�F�N�gID
     */
    FALL_OBJECT�QINFO    ChooseObject(void);

    /*!
     *  @brief      �I��
     */
    void    Finish(void);

    /*!
     *  @brief      �I������
     */
    void    CheckFinish(void) override;

    /*!
     *  @brief      ����̏I������
     */
    void    FinishTopic(void);

    static const CTransform             m_floor_transform_list[];   //!< �����鏰�̃g�����X�t�H�[��
    static const float                  m_player_spawn_height;      //!< �v���C���[���o�����鍂��
    static const float                  m_time_accelerator;         //!< ������܂ł̑��x�𑝂₷
    static const float                  m_min_time;                 //!< ������܂ł̍ŏ�����
    static const float                  m_fall_time;                //!< ������܂ł̏�������
    static const float                  m_object_delay_time;        //!< �Ē��I�܂ł̎���
    static const float                  m_topic_interval_time;      //!< ���I�̊��o
    static const float                  m_add_topic_time;           //!< ���肪������܂ł̎���
    static const float                  m_reset_topic_time;         //!< ���Z�b�g�܂ł̑ҋ@����
    static const float                  m_defeat_height;            //!< �����鍂��
    static const float                  m_extend_return_time;       //!< ���̕��������т�܂ł̎���
    static const CVector3               m_camera_position;          //!< �J�����̈ʒu
    static const CVector3               m_camera_direction;         //!< �J�����̕���
    static const vivid::Vector2         m_topic_positionList[];     //!< ����ʒu
    static constexpr int                m_max_topic_num = 5;        //!< ���萔(5)
    static const CVector3               m_player_default_forward;   //!< �v���C���[�̃X�|�[�����̐��ʕ���
    float                               m_FallTime;                 //!< ������܂ł̎���
    std::array<CTimer,m_max_topic_num>  m_ChooseObjectTimer;        //!< ���I�^�C�}�[
    CTimer                              m_AddTopicTimer;            //!< ���肪������^�C�}�[
    CTimer                              m_ResetTopicTimer;          //!< ���胊�Z�b�g�^�C�}�[
    CTimer                              m_ExtendTimer;              //!< ���̕��������т�܂ł̃^�C�}�[

    using TOPIC_LIST = std::list<std::shared_ptr<CFallOutTopic>>;

    TOPIC_LIST                          m_TopicList;                //!< ����̃��X�g
    std::mt19937                        m_RandEngine; // �����Z���k�E�c�C�X�^�[�G���W��
};
