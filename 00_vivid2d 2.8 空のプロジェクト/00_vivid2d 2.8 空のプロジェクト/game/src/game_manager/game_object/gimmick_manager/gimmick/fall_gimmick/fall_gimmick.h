
#pragma once
#include "..\gimmick.h"
#include "fall_object/fall_object.h"
class CFallGimmick : public CGimmick
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     *
     */
    CFallGimmick();

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CFallGimmick(void);

    /*!
     *  @brief      ������
     *
     */
    void    Initialize();

    /*!
     *  @brief      �X�V
     */
    void    Update(void);

    /*!
     *  @brief      �`��
     */
    void    Draw(void);

    /*!
     *  @brief      ���
     */
    void    Finalize(void);

private:
    CFallObject     m_FallObject_1;
    CFallObject     m_FallObject_2;
    CFallObject     m_FallObject_3;
    CFallObject     m_FallObject_4;
    CFallObject     m_FallObject_5;
    CFallObject     m_FallObject_6;
};
