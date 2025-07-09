#pragma once

#include <list>
#include "bullet\bullet_id.h"
#include "bullet\bullet.h"
#include "../launcher/launcher.h"
#include <memory>
class CBulletManager
{
public:
    /*!
     *  @brief      �C���X�^���X�̎擾
     *
     *  @return     �C���X�^���X
     */
    static CBulletManager& GetInstance(void);

    /*!
     *  @brief      ������
     */
    void        Initialize(void);

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
     *  @brief      �e���X�g�^
     */
    using BULLET_LIST = std::list<std::shared_ptr<IBullet>>;


    /*!
     *  @brief      �`��
     */
    BULLET_LIST       GetBulletList();
    /*!
     *  @brief      �e����
     *
     *  @param[in]  category  �������ʎq
     *  @param[in]  id          �eID
     *  @param[in]  pos         �ʒu
     *  @param[in]  dir         ����
     */
    std::shared_ptr<IBullet>        Create(FACTION_CATEGORY category,CShot::BulletParameters* bulletParameters, const CVector3& pos, const CVector3& dir);

    /*!
     *  @brief      �e����
     *
     *  @param[in]  category  �������ʎq
     *  @param[in]  id          �eID
     *  @param[in]  pos         �ʒu
     *  @param[in]  dir         ����
     */
    std::shared_ptr<IBullet>        Create(FACTION_CATEGORY category, BULLET_ID id, const CVector3& pos, const CVector3& dir);
    
    /*!
     *  @brief      ���f���Ƃ̔��˔���
     */
    void        CheckReflectModel(int model_handle);

private:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CBulletManager(void);

    /*!
     *  @brief      �R�s�[�R���X�g���N�^
     *
     *  @param[in]  rhs     �I�u�W�F�N�g
     */
    CBulletManager(const CBulletManager& rhs);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CBulletManager(void);

    /*!
     *  @brief      ������Z�q
     *
     *  @param[in]  rhs ����I�u�W�F�N�g
     *
     *  @return     ���g�̃I�u�W�F�N�g
     */
    CBulletManager& operator=(const CBulletManager& rhs);


    BULLET_LIST     m_BulletList;   //!< �e���X�g
};
