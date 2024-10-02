#pragma once

#include <list>
#include "unit\unit_id.h"
#include "unit\unit.h"
#include "..\bullet_manager\bullet\bullet.h"
#include "../stage/stage.h"
#include "..\scene_manager\scene\game\game.h"
#include "unit/player/player.h"

class CUnitManager
{
public:

    enum class AIM_ID
    {
        TARGET,
        NON_TARGET,
    };

    /*!
     *  @brief      �C���X�^���X�̎擾
     *
     *  @return     �C���X�^���X
     */
    static CUnitManager& GetInstance(void);

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
     *  @brief      ���j�b�g����
     *
     *  @param[in]  id          ���j�b�gID
     *  @param[in]  pos         �ʒu
     *  @param[in]  moveFlag    �����邩�ǂ���
     *  @param[in]  aimId    �����邩�ǂ���
     */
    void        Create(UNIT_ID id, const CVector3& pos, MOVE_ID moveId = MOVE_ID::WAIT, bool aimFlag = false);

    /*!
     *  @brief      ���j�b�g�ƒe�Ƃ̃A�^������
     *
     *  @param[in]  bullet  �e�N���X
     */
    void        CheckHitBullet(IBullet* bullet);


    /*!
     *  @brief      ���j�b�g�ƃX�e�[�W�Ƃ̃A�^������
     *
     */
    void        CheckHitStage();

    /*!
     *  @brief      �v���C���[�擾
     *
     *  @return     �v���C���[
     */
    CPlayer*      GetPlayer(void);

    /*!
     *  @brief      �S�Ẵv���C���[�̃A�N�V�����t���O�̐ݒ�
     *
     */
    void      SetAllPlayerAction(bool flag);

    CVector3 CheckHitLine(const CVector3& startPos, const CVector3& endPos);

    bool CheckHitLineEnemy(const CVector3& startPos, const CVector3& endPos);


private:

    /*!
     *  @brief      �R���X�g���N�^
     */
    CUnitManager(void);

    /*!
     *  @brief      �R�s�[�R���X�g���N�^
     *
     *  @param[in]  rhs     �I�u�W�F�N�g
     */
    CUnitManager(const CUnitManager& rhs);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CUnitManager(void);

    /*!
     *  @brief      ������Z�q
     *
     *  @param[in]  rhs ����I�u�W�F�N�g
     *
     *  @return     ���g�̃I�u�W�F�N�g
     */
    CUnitManager& operator=(const CUnitManager& rhs);

    /*!
     *  @brief      ���j�b�g�X�V
     */
    void        UpdateUnit(void);

    /*!
     *  @brief      ���j�b�g���X�g�^
     */
    using UNIT_LIST = std::list<IUnit*>;

    UNIT_LIST           m_UnitList;             //!< ���j�b�g���X�g

    /*!
     *  @brief      �v���C���[���X�g�^
     */
    using RANKING_LIST = std::list<CPlayer*>;

    RANKING_LIST           m_RankingList;             //!< �����L���O���X�g

};
    