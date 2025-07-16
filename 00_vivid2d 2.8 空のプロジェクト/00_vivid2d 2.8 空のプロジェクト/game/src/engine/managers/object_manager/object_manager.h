#pragma once

#include "vivid.h"
#include <list>
#include "object_id.h"
#include <memory>
#include "../../../engine/core/game_object/game_object.h"
#include "../bullet_manager/bullet/bullet.h"
#include "engine/components/collider_component/collision_result.h"
class CObjectManager
{
public:
    /*!
     *  @brief      �C���X�^���X�̎擾
     *
     *  @return     �C���X�^���X
     */
    static CObjectManager& GetInstance(void);

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
     *  @brief      �I�u�W�F�N�g����
     *
     *  @param[in]  id              �I�u�W�F�N�gID
     *  @param[in]  position        �ʒu
     */
    std::shared_ptr<CGameObject>    Create(OBJECT_ID id, const CTransform& transform, PLAYER_ID player_id = PLAYER_ID::NONE);

	/*!
	 *  @brief      �v���C���[���폜
	 *
	 *  @param[in]  player_id   �v���C���[ID
	 *
	 */
    void DeletePlayer(PLAYER_ID player_id);

    /*!
     *  @brief      �I�u�W�F�N�g���X�g�^
     */
    using OBJECT_LIST = std::list<std::shared_ptr<CGameObject>>;

    /*!
     *  @brief      ���X�g�擾
     *
     *  @return     �I�u�W�F�N�g���X�g
     */
    OBJECT_LIST GetList();

    template<typename T>
    std::vector<std::shared_ptr<CGameObject>> GetObjectsWithComponent()
    {
        std::vector<std::shared_ptr<CGameObject>> result;
        for (auto& obj : m_GameObjects)
        {
            if (obj->HasComponent<T>())
            {
                result.push_back(obj);
            }
        }
        return result;
    }

    // �ڍ׃o�[�W�����i�Փˈʒu���擾����j
    std::shared_ptr<CGameObject> CheckHitLineForAll(
        const CVector3& start,
        const CVector3& end,
        CGameObject* ignore_object, // �������g�𖳎����邽�߂̈���
        CollisionResult& out_result = CollisionResult()   // �Փˈʒu���i�[����
    );

    /*!
     *  @brief      ���j�b�g�ƒe�Ƃ̃A�^������
     *
     *  @param[in]  bullet  �e�N���X
     */
    void        CheckHitBullet(std::shared_ptr<IBullet> bullet);

private:

    /*!
     *  @brief      �I�u�W�F�N�g�X�V
     */
    void        UpdateObject(void);


    /*!
     *  @brief      �R���X�g���N�^
     */
    CObjectManager(void);

    /*!
     *  @brief      �R�s�[�R���X�g���N�^
     *
     *  @param[in]  rhs     �I�u�W�F�N�g
     */
    CObjectManager(const CObjectManager& rhs);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CObjectManager(void);

    /*!
     *  @brief      ������Z�q
     *
     *  @param[in]  rhs ����I�u�W�F�N�g
     *
     *  @return     ���g�̃I�u�W�F�N�g
     */
    CObjectManager& operator=(const CObjectManager& rhs);

    OBJECT_LIST             m_GameObjects;             //!< �I�u�W�F�N�g���X�g
};