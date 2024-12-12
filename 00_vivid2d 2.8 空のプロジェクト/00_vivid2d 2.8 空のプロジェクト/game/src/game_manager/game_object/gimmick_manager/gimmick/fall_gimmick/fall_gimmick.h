
#pragma once
#include "..\gimmick.h"
#include <list>
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
    void    Initialize(IObject* object);

    /*!
     *  @brief      ������
     *  @param[in]  object          �I�u�W�F�N�g�̃|�C���^
     *  @param[in]  timer           �^�C�}�[�̐ݒ�
     *
     */
    void    Initialize(IObject* object, float time);

    /*!
     *  @brief      �X�V
     */
    void    Update(void);

    /*!
     *  @brief      ���
     */
    void    Finalize(void);

private:
    static const float  m_fall_speed;       //!< �����鑬�x
    static const float  m_remove_height;    //!< ���ɖ߂鍂��
    static const float  m_remove_time;      //!< ���ɖ߂�܂ł̎���
    float               m_StartHeight;      //!< �����̍���

};
