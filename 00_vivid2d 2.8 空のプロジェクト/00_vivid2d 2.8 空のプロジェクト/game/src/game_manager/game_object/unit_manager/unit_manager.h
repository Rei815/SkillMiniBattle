#pragma once

#include <list>
#include "unit\unit_id.h"
#include "unit\unit.h"
#include "..\bullet_manager\bullet\bullet.h"
#include "..\scene_manager\scene\game\game.h"
#include "unit/player/player.h"
class CUnitManager
{
public:

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
     */
    IUnit*      Create(UNIT_ID id, const CVector3& pos);

    /*!
     *  @brief      ���j�b�g�폜
     *
     *  @param[in]  id          ���j�b�gID
     */
    void      Delete(UNIT_ID id);

    /*!
     *  @brief      ���j�b�g�ƒe�Ƃ̃A�^������
     *
     *  @param[in]  bullet  �e�N���X
     */
    void        CheckHitBullet(IBullet* bullet);


    /*!
     *  @brief      ���j�b�g�ƃI�u�W�F�N�g�Ƃ̃A�^������
     *  @param[in]  object  �I�u�W�F�N�g�N���X
     */
    void        CheckHitObject(IObject* object);

    /*!
     *  @brief      �v���C���[�擾
     *
     *  @return     �v���C���[
     */
    CPlayer*      GetPlayer(UNIT_ID id);

    /*!
     *  @brief      �S�Ẵv���C���[�̃A�N�V�����t���O�̐ݒ�
     *
     */
    void      SetAllPlayerAction(bool flag);

    bool CheckHitLineEnemy(const CVector3& startPos, const CVector3& endPos);

    /*!
     *  @brief      ���j�b�g���X�g�^
     */
    using UNIT_LIST = std::list<IUnit*>;
    UNIT_LIST   GetUnitList();
    /*!
     *  @brief      �v���C���[���X�g�^
     */
    using DEFEAT_LIST = std::list<IUnit*>;

    DEFEAT_LIST GetDefeatList();
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
     *  @brief      ���j�b�g�ƃX�e�[�W�Ƃ̃A�^������̏����i�����j
     *
     *  @param[in]  object      �����蔻������鑊��I�u�W�F�N�g
     *  @param[in]  unit        �����蔻������郆�j�b�g
     *  @param[in]  startPos    �����蔻�����������̊J�n�n�_
     *  @param[in]  endPos      �����蔻�����������̏I���n�_
     */
    void    CheckHitObjectVertical(IObject* object, IUnit* unit, const CVector3& startPos, const CVector3& down_dir = CVector3(0.0f, -1.0f, 0.0f), float length = 1.0f);
    
    /*!
     *  @brief      ���j�b�g�ƃX�e�[�W�Ƃ̃A�^������̏����i�����j
     *
     *  @param[in]  object      �����蔻������鑊��I�u�W�F�N�g
     *  @param[in]  unit        �����蔻������郆�j�b�g
     *  @param[in]  startPos    �����蔻�����������̊J�n�n�_
     *  @param[in]  endPos      �����蔻�����������̏I���n�_
     */
    void    CheckHitObjectHorizontal(IObject* object, IUnit* unit, const CVector3& startPos, const CVector3& endPos);

    static const std::string                            m_file_name_list[];

    UNIT_LIST                                           m_UnitList;             //!< ���j�b�g���X�g
    DEFEAT_LIST                                         m_DefeatList;             //!< �����L���O���X�g

};
