#pragma once

#include <list>
#include "unit\unit_id.h"
#include "unit\unit.h"
#include "..\bullet_manager\bullet\bullet.h"
#include "../stage/stage.h"
#include "..\scene_manager\scene\game_main\game_main.h"
#include "unit/player/player.h"
#include "unit/boss_enemy/boss_enemy.h"

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
     *  @brief      �{�X�����j���ꂽ���H
     *
     *  @retval     true    �{�X�����j���ꂽ
     *  @retval     false   �{�X�����j����Ă��Ȃ�
     */
    bool        CheckDestoryBoss(void);


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
     *  @brief      �{�X�擾
     *
     *  @return     �{�X
     */
    IUnit*      GetBoss(void);

    /*!
     *  @brief      Wave�ő吔�擾
     *
     *  @return     Wave�ő吔
     */
    int GetMaxWave(void);

    /*!
     *  @brief      ���݂�Wave���擾
     *
     *  @return     ���݂�Wave��
     */
    int GetCurrentWave(void);

    CVector3 CheckHitLine(const CVector3& startPos, const CVector3& endPos);

    bool CheckHitLineEnemy(const CVector3& startPos, const CVector3& endPos);

    /*!
     *  @brief      Wave���I��������`�F�b�N
     *  @return     true   �I����Ă���
     */
    bool        CheckFinishWave(void);

    /*!
     *  @brief      Enemy�e�[�u���X�V
     */
    void        UpdateEnemyTable(void);

    /*!
     *  @brief      ���������L���t���O
     *  @param[in]  flag          ���������邩�ǂ���
     */
    void SetGenerateFlag(bool flag);

    /*!
     *  @brief      �Ō�̓G�t���O��ݒ�
     *  @param[in]  flag          �Ō�̓G�Ȃ�true
     */
    void SetAppearFinalEnemyFlag(bool flag);
    /*!
     *  @brief      �{�X�o��t���O���擾
     *  @return     true   �o�ꂵ��
     */
    bool GetAppearBossFlag();

    /*!
     *  @brief      ���݂�Wave���𑝉�������
     *
     */
    void AddWaveCurrentCount();

private:

    /*!
     *  @brief      Wave�Ō�̓G�����j���ꂽ���H
     *
     *  @retval     true    �Ō�̓G�����j���ꂽ
     *  @retval     false   �Ō�̓G�����j����Ă��Ȃ�
     */
    bool        CheckDestoryFinalEnemy(void);

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
     *  @brief      Enemy�̔z�u
     */
    void        DeployEnemy(void);




    /*!
     *  @brief      ���j�b�g�X�V
     */
    void        UpdateUnit(void);

    /*!
     *  @brief      Enemy�e�[�u���p�\����ID
     */
    enum ENEMY_TABLE_DATA_PARAM
    {
        ENEMY_TABLE_DATA_PARAM_ID,
        ENEMY_TABLE_DATA_PARAM_X,
        ENEMY_TABLE_DATA_PARAM_Y,
        ENEMY_TABLE_DATA_PARAM_Z,
        ENEMY_TABLE_DATA_PARAM_CREATE_TIME,
        ENEMY_TABLE_DATA_PARAM_MOVE_ID,
        ENEMY_TABLE_DATA_PARAM_WAVE_STATE,
    };

    /*!
     *  @brief      Enemy�e�[�u���p�\����
     */
    struct ENEMY_TABLE_DATA
    {
        UNIT_ID         id;
        int             x;
        int             y;
        int             z;
        int             create_frame;
        bool            aim_flag;
        MOVE_ID         move_id;
        CGameMain::WAVE_STATE         wave_state;
    };

    /*!
     *  UFO�e�[�u�����X�g
     */
    using ENEMY_TABLE = std:: list<ENEMY_TABLE_DATA>;

    /*!
     *  @brief      ���j�b�g���X�g�^
     */
    using UNIT_LIST = std::list<IUnit*>;

    UNIT_LIST           m_UnitList;             //!< ���j�b�g���X�g
    int                 m_NextUniqueId;         //!< �����̂��тɒl���ς��
    ENEMY_TABLE         m_EnemyTable;           //!< Enemy�e�[�u�����X�g
    bool                m_AppearBossFlag;       //!< �{�X�o��t���O
    bool                m_AppearFinalEnemyFlag; //!< �Ō�̓G�o��t���O
    int                 m_WaveCount;            //!< Wave�p�J�E���^�[
    int                 m_CreateTimer;          //!< ��������
    bool                m_GenerateFlag;         //!< ���������L���t���O
    int                 m_WaveCurrentCount;     //!< ���݂�Wave�p�J�E���^�[

    std::map<std::string, MOVE_ID> m_MoveIdList;
    std::map<std::string, CGameMain::WAVE_STATE> m_WaveStateList;
};
    