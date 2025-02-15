#pragma once

#include <list>
#include "../../../mathematics/mathematics.h"

#include "effect\effect_id.h"
#include "effect/effect.h"
using namespace std;

class IEffect;

/*!
 *  @class      CEffectManager
 *
 *  @brief      �G�t�F�N�g�Ǘ��N���X
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
class CEffectManager
{
public:
    /*!
     *  @brief      �C���X�^���X�̎擾
     *
     *  @return     �C���X�^���X
     */
    static CEffectManager& GetInstance(void);

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
     *  @brief      �G�t�F�N�g����
     *
     *  @param[in]  id          �G�t�F�N�gID
     *  @param[in]  pos         �ʒu
     *  @param[in]  scale       �g�嗦
     */
    IEffect*        Create(EFFECT_ID id, const CVector3& pos = CVector3::ZERO, float scale = 1.0f);

    /*!
     *  @brief      �G�t�F�N�g����
     *
     *  @param[in]  id          �G�t�F�N�gID
     *  @param[in]  pos         �ʒu
     *  @param[in]  rot         ��]
     */
    IEffect*        Create(EFFECT_ID id, const CVector3& pos, const CVector3& rot);


    /*!
     *  @brief      �G�t�F�N�g����
     *
     *  @param[in]  id          �G�t�F�N�gID
     *  @param[in]  pos         �ʒu
     *  @param[in]  rot         ��]
     *  @param[in]  scale       �g�嗦
     */
    IEffect*        Create(EFFECT_ID id, const CVector3& pos, const CVector3& rot, const float scale);

    /*!
     *  @brief      �G�t�F�N�g����
     *
     *  @param[in]  id          �G�t�F�N�gID
     *  @param[in]  pos         �ʒu
     *  @param[in]  rot         ��]
     *  @param[in]  scale       �g�嗦
     */
    IEffect*        Create(EFFECT_ID id, const CVector3& pos, const CVector3& rot, const CVector3& scale);


    /*!
     *  @brief      �G�t�F�N�g����
     *
     *  @param[in]  id          �G�t�F�N�gID
     *  @param[in]  pos         �ʒu
     *  @param[in]  color       �F
     *  @param[in]  rotation    ��]�l
     */
    IEffect*        Create(EFFECT_ID id, const vivid::Vector2& pos, unsigned int color, float rotation);

    /*!
     *  @brief      �e�̈ʒu�ݒ�
     *
     *  @param[in]  effectID        �G�t�F�N�gid
     *  @param[in]  parentPos       �e�̈ʒu
     */
    void            SetParentPosition(EFFECT_ID effectID,CVector3& parentPos);

    /*!
     *  @brief      ���ׂẴG�t�F�N�g���ꎞ��~
     */
    void            PauseAllEffect();

    /*!
     *  @brief      ���ׂẴG�t�F�N�g���ĊJ
     */
    void            ResumeAllEffect();

private:

    IEffect* CreateClass(EFFECT_ID id);
    /*!
     *  @brief      �R���X�g���N�^
     */
    CEffectManager(void);

    /*!
     *  @brief      �R�s�[�R���X�g���N�^
     *
     *  @param[in]  rhs     �I�u�W�F�N�g
     */
    CEffectManager(const CEffectManager& rhs);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CEffectManager(void);

    /*!
     *  @brief      ������Z�q
     *
     *  @param[in]  rhs ����I�u�W�F�N�g
     *
     *  @return     ���g�̃I�u�W�F�N�g
     */
    CEffectManager& operator=(const CEffectManager& rhs);

    /*!
     *  @brief      �G�t�F�N�g���X�g�^
     */
    using EFFECT_LIST = list<IEffect*>;

    EFFECT_LIST     m_EffectList;   //!< �G�t�F�N�g���X�g
};
