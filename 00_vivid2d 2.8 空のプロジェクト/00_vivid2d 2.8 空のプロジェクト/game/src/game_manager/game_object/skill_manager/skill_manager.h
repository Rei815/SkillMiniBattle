#pragma once

#include "vivid.h"
#include "skill/skill_id.h"
#include "skill/skill.h"
#include "../unit_manager/unit_manager.h"
#include "../unit_manager/unit/player/player.h"
#include "../unit_manager/unit/unit_id.h"
#include "../scene_manager/scene/game/game_id.h"

class CSkillManager
{
public:
    /*!
     *  @brief      �C���X�^���X�̎擾
     *
     *  @return     �C���X�^���X
     */
    static CSkillManager& GetInstance(void);

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
     *  @brief      �X�L�����X�g�^
     */
    using SKILL_LIST = std::list<CSkill*>;

    /*!
     *  @brief      �X�L�������i����܂��񂪂���񂾁j
     */
    void        CreateSkill(SKILL_ID_DARUMA skill_id, UNIT_ID player_id);

    /*!
     *  @brief      �X�L�������i�t�H�[���Q�[���j
     */
    void        CreateSkill(SKILL_ID_FALLGAME skill_id, UNIT_ID player_id);

    /*!
     *  @brief      �X�L�������i�h�b�W�{�[���j
     */
    void        CreateSkill(SKILL_ID_DODGEBALL skill_id, UNIT_ID player_id);

    /*!
     *  @brief      �X�L���t�^
     */
    void        SetSkill(void);

private:
    /*!
     *  @brief      �R���X�g���N�^
     */
    CSkillManager(void);

    /*!
     *  @brief      �R�s�[�R���X�g���N�^
     *
     *  @param[in]  rhs     �I�u�W�F�N�g
     */
    CSkillManager(const CSkillManager& rhs);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CSkillManager(void);

    /*!
     *  @brief      ������Z�q
     *
     *  @param[in]  rhs ����I�u�W�F�N�g
     *
     *  @return     ���g�̃I�u�W�F�N�g
     */
    CSkillManager& operator=(const CSkillManager& rhs);

    CSkill*     m_SetSkill[(int) UNIT_ID::NONE];

    SKILL_LIST  m_SkillList;             //!< �X�L�����X�g
};