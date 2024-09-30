#pragma once

#include "../../../utility/utility.h"
#include "shot/shot.h"
#include <list>
#include "shot/shot_id.h"

class CLauncher
{
public:


    /*!
     *  @brief      �p�����[�^�\����
     *  @param bullet_interval  ���ˑ��x
     *  @param fire_interval    �U�����x
     *  @param capacity         ���U��
     *  @param speed            ���x
     *  @param deviation        �u��
     *  @param radius           ���a
     *  @param damage           �U����
     *  @param homingDelayTime  �U�����x������
     *  @param acceleration     ������
     */
    struct BulletParameters
    {
        int     bulletInterval;
        int     fireInterval;
        int     capacity;
        float   speed;
        float   deviation;
        float   radius;
        int     damage;
        int     homingDelayTime;
        float   acceleration;
    };

	/*!
	 *  @brief      �C���X�^���X�̎擾
	 *
	 *  @return     �C���X�^���X
	 */
	static CLauncher& GetInstance(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(void);

    /*!
     *  @brief      �X�V
     */
    void        Update(void);


    /*!
     *  @brief      ���
     */
    void        Finalize(void);


    CShot* Create(SHOT_ID shotID);

private:

    /*!
     *  @brief      �R���X�g���N�^
     */
    CLauncher(void);

    /*!
     *  @brief      �R�s�[�R���X�g���N�^
     *
     *  @param[in]  rhs     �I�u�W�F�N�g
     */
    CLauncher(const CLauncher& rhs);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CLauncher(void);

    /*!
     *  @brief      ������Z�q
     *
     *  @param[in]  rhs ����I�u�W�F�N�g
     *
     *  @return     ���g�̃I�u�W�F�N�g
     */
    CLauncher& operator=(const CLauncher& rhs);

    static const BulletParameters    m_bullet_parameters_[];

    /*!
     *  @brief      �V���b�g���X�g�^
     */
    using SHOT_LIST = std::list<CShot*>;

    SHOT_LIST     m_ShotList;   //!< �G�t�F�N�g���X�g

};