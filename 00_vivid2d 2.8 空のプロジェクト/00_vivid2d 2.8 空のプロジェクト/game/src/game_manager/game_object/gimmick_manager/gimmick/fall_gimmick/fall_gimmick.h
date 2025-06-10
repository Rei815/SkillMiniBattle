
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
     *  @param[in]  object       �I�u�W�F�N�g
     */
    void    Initialize(std::shared_ptr<IObject> object);


    /*!
     *  @brief      �X�V
     */
    void    Update(void);

    /*!
     *  @brief      ���
     */
    void    Finalize(void);

    /*!
     *  @brief      ���ɖ߂�܂ł̎��Ԃ̐ݒ�
     *  @param[in]  float       ����
     */
    void   AddReturnTime(float time);
private:
    static const float  m_fall_speed;       //!< �����鑬�x
    static const float  m_return_height;    //!< ���ɖ߂鍂��
    static const float  m_return_time;      //!< ���ɖ߂�܂ł̎���

    float               m_StartHeight;      //!< �����̍���
    float               m_ReturnTime;       //!< ���ɖ߂�܂ł̎���
    CTimer              m_ReturnTimer;      //!< �߂�܂ł̃^�C�}�[
};
