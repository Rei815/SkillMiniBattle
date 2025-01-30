#pragma once

#include "vivid.h"
#include "..\ui.h"
#include <list>
#include <memory>
class  CSceneUIParent : public CUI
{
public:
    enum class STATE
    {
        WAIT,
        MOVE_ONE,
        BACK_ONE,
    };
    /*!
     *  @brief      �R���X�g���N�^
     */
    CSceneUIParent(UI_ID id);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CSceneUIParent(void);

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

    /*!
     *  @brief      ��Ԏ擾
     *
     *  @return     ���
     */
    STATE            GetState(void);

    /*!
     *  @brief      ��Ԑݒ�
     *
     *  @param[in]  state  ���
     */
    void            SetState(STATE state);
private:


    static const vivid::Vector2             m_position;             //!< �ʒu
    static const int            m_speed;                //!< �ړ����x
    static const float			m_down_final_height;	//!< �~���Ƃ��̍ŏI���x

    static const float          m_end_time;             //!< �I������
    float                       m_EaseTimer;            //!< �o�ߎ���
    float                       m_StartValue;           //!< �J�n�l
    float                       m_FinishValue;          //!< �I���l
    STATE                       m_State;
    float                       m_FinishPosition;
    using CHILDRENLIST = std::list<CUI*>;
    CHILDRENLIST               m_ChildrenList;
};