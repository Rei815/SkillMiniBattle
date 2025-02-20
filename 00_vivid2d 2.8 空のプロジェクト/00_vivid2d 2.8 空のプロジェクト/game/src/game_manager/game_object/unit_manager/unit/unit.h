
#pragma once

#include "unit_id.h"
#include "..\..\..\..\mathematics\mathematics.h"
#include "../../model_manager/model/model.h"
#include "..\..\bullet_manager\bullet\bullet.h"
#include "..\..\object_manager\object\object.h"
#include "../../launcher/shot/shot.h"


/*!
 *  @brief  ���j�b�g�̏��ID
 */
enum class UNIT_STATE
{
    APPEAR,
    ATTACK,
    DEFEAT,
};


/*!
 *  @class      IUnit
 *
 *  @brief      ���j�b�g�x�[�X�N���X
 *
 *  @author     Kazuya Maruyama
 *
 *  @date       2020/11/13
 *
 *  @since      1.0
 */
class IUnit
{
public:
    IUnit();
    /*!
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  category  ���j�b�g���ʎq
     *  @param[in]  unit_id     ���j�b�gID
     */
    IUnit(UNIT_CATEGORY category, UNIT_ID unit_id = UNIT_ID::NONE);

    /*!
     *  @brief      �f�X�g���N�^
     */
    virtual ~IUnit(void);

    /*!
     *  @brief      ������
     *
     *  @param[in]  position    �ʒu
     */
    virtual void    Initialize(UNIT_ID unit_id, const CVector3& position, const std::string& file_name, vivid::controller::DEVICE_ID controller);

    /*!
     *  @brief      �X�V
     */
    virtual void    Update(void);

    /*!
     *  @brief      �`��
     */
    virtual void    Draw(void);

    /*!
     *  @brief      ���
     */
    virtual void    Finalize(void);

    /*!
     *  @brief      �A�^������`�F�b�N
     *
     *  @param[in]  bullet  �e�N���X
     *
     *  @retval     true    �������Ă���
     *  @retval     false   �������Ă��Ȃ�
     */
    virtual bool    CheckHitBullet(IBullet* bullet);

    /*!
     *  @brief      �A�^������`�F�b�N
     *
     *  @param[in]  bullet  �e�N���X
     *
     *  @retval     true    �������Ă���
     *  @retval     false   �������Ă��Ȃ�
     */
    virtual bool    CheckHitBulletModel(IBullet* bullet);

    /*!
     *  @brief      ���j�b�gID�擾
     *
     *  @return     ���j�b�gID
     */
    UNIT_ID         GetUnitID(void);

    /*!
     *  @brief      �ʒu�擾
     *
     *  @return     �ʒu
     */
    CVector3        GetPosition(void);

    /*!
     *  @brief      �ʒu�ݒ�
     *
     *  @param[in]  position    �ʒu
     */
    void            SetPosition(const CVector3& position);

    /*!
     *  @brief      �A�N�e�B�u�t���O�擾
     *
     *  @return     �A�N�e�B�u�t���O
     */
    bool            GetActive(void);

    /*!
     *  @brief      �A�N�e�B�u�t���O�ݒ�
     *
     *  @param[in]  active  �A�N�e�B�u�t���O
     */
    void            SetActive(bool active);

    /*!
     *  @brief      ���j�b�g���ʎq�擾
     *
     *  @return     ���j�b�g���ʎq
     */
    UNIT_CATEGORY   GetUnitCategory(void);

    /*!
     *  @brief      ���G�t���O�擾
     *
     *  @return     ���G�t���O
     */
    bool            GetInvincibleFlag(void);

    /*!
     *  @brief      ���G�t���O�ݒ�
     *
     *  @param[in]  flag    ���G�t���O
     */
    void            SetInvincibleFlag(bool flag);

    /*!
     *  @brief      ��Ԏ擾
     *
     *  @return     ���ID
     */
    UNIT_STATE      GetUnitState(void);

    /*!
     *  @brief      ���G�t���O�ݒ�
     *
     *  @param[in]  flag    ���G�t���O
     */
    void            SetUnitState(UNIT_STATE state);

    /*!
     *  @brief      ���x�x�N�g���̎擾
     *
     */
    CVector3        GetVelocity();

    /*!
     *  @brief      ���x�x�N�g���̐ݒ�
     *
     */
    void            SetVelocity(const CVector3& velocity);

    /*!
     *  @brief      �w�O������̉e���ɂ��ړ����x�x�̃Z�b�g
     *
     *  @param[in]  velocity    �Z�b�g���鑬�x
     */
    void SetAffectedVelocity(CVector3 velocity);

    /*!
     *  @brief      �w�O������̉e���ɂ��ړ����x�x�̉��Z
     *
     *  @param[in]  velocity    ���Z���鑬�x
     */
    void AddAffectedVelocity(CVector3 velocity);

    /*!
     *  @brief      ���a�擾
     *
     *  @return     ���a
     */
    float           GetRadius(void);

    /*!
     *  @brief      �����擾
     *
     *  @return     ����
     */
    float           GetHeight(void);

    /*!
     *  @brief      �e���ǉ�
     *
     */
    void        AddShot(void);

    /*!
     *  @brief      ���ː��ǉ�
     *
     */
    void        AddBullet(void);

    /*!
     *  @brief      �e���ǉ�
     *
     */
    void        DamageUp(float damageRate);

    /*!
     *  @brief      �U�����擾
     *
     *  @return     �U����
     */
    float       GetDamageRate(void);

    /*!
     *  @brief      �s�k�t���O�擾
     *
     *  @return     �s�k�t���O
     */
    bool       GetDefeatFlag(void);

    /*!
     *  @brief      �s�k�t���O�ݒ�
     *
     *  @param[in]  flag    �s�k�t���O
     */
    void       SetDefeatFlag(bool flag);

    CModel      GetModel(void);

    /*!
         *  @brief      �n��ɂ��邩�ǂ�����ݒ�
         *
         *  @param[in]  flag    �ڒn�t���O
     */
    void        SetIsGround(bool flag);

    /*!
         *  @brief      �n��ɂ��邩�ǂ������擾
         *
         *  @return     �ڒn�t���O
     */
    bool        GetIsGround();

    /*!
     *  @brief      �d�͂�ݒ�
     *
     *  @param[in]  gravity    �d�͒l
     */
    void        SetGravity(const CVector3& gravity);

    /*!
     *  @brief      ��b�d�͂��擾
     *
     *  @return     �d�͒l
     */
    CVector3        GetDefaultGravity();


    /*!
     *  @brief      �A���t�@�l�����炵�Ă���
     */
    void    DecAlpha(float alpha = 0.0f);
    /*!
     *  @brief      �A���t�@�l�����ɖ߂�
     */
    void        RevertAlpha(float alpha);

    void        SetAlpha(float alpha);

    /*!
     *  @brief      �e�̃I�u�W�F�N�g���擾
     *
     *  @return     �e�̃I�u�W�F�N�g
     */
    IObject*    GetParent(void);

    /*!
     *  @brief      �e�̃I�u�W�F�N�g��ݒ�
     *
     *  @param[in]  parent    �e�̃I�u�W�F�N�g
     */
    void        SetParent(IObject* parent);

    void            SetForwardVector(const CVector3& forward_vector);

    CVector3        GetForwardVector();

protected:

    /*!
     *  @brief      �o��
     */
    virtual void    Appear(void);

    /*!
     *  @brief      �U��
     */
    virtual void    Attack(void);

    /*!
     *  @brief      �ˌ�
     *  @param[in]  aim         Player��_�����ǂ���
     *  @param[in]  position    ���ˈʒu
     */
    void        Fire(CShot* shot, bool aim, CVector3& position);

    /*!
     *  @brief      �ˌ�
     *  @param[in]  aim         Player��_�����ǂ���
     *  @param[in]  position    ���ˈʒu
     */
    void        Fire(CShot* shot, bool aim, CVector3& position, const CVector3& direction);

    /*!
     *  @brief      ��e
     *  @param[in]  bullet          ��e�����e
     *  @param[in]  hit_position    ��e�ʒu
     */
    virtual void    HitBullet(IBullet* bullet, CVector3 hit_position);

    /*!
     *  @brief      �Ռ���^����
     *  @param[in]  hit_position   �Ռ��̈ʒu
     *  @param[in]  direction      ����
     *  @param[in]  float          �Ռ���
     */
    virtual void    Impact(const CVector3& hit_position, const CVector3& direction, float power);

    /*!
     *  @brief      �s�k
     */
    virtual void    Defeat(void);

    /*!
     *  @brief      �폜
     */
    virtual void    Delete(void);

    static const float      m_destroy_scale_adjust;     //!< �G�t�F�N�g(destroy)�̑傫�������l
    static const float      m_alpha_speed;              //!< �A���t�@�l�̑��x
    static const CVector3   m_gravity;

    float                   m_Radius;
    float                   m_Height;
    CModel                  m_Model;
    CTransform	            m_Transform;		    //!< �g�����X�t�H�[��
    CVector3                m_ForwardVector;        //!< ���ʕ����̃x�N�g��
    CVector3	            m_Max_Vertex;		    //!< �ő咸�_���W
    CVector3                m_Velocity;             //!< ���x
    CVector3                m_AffectedVelocity;     //!< �O������̉e���ɂ�鑬�x
    CVector3                m_Gravity;              //!< �d��
    UNIT_CATEGORY           m_Category;             //!< ���j�b�g���ʎq
    UNIT_ID                 m_UnitID;               //!< ���j�b�gID
    bool                    m_ActiveFlag;           //!< �A�N�e�B�u�t���O
    bool                    m_InvincibleFlag;       //!< ���G�t���O
    UNIT_STATE              m_UnitState;            //!< ���ID
    bool                    m_AimFlag;              //!< �_�����ǂ���
    float                   m_DamageRate;
    CShot*                  m_Shot;
    bool                    m_RevertAlpha;              //!< �A���t�@�l��߂�
    float                   m_Alpha;                    //!< �A���t�@�l
    bool                    m_DefeatFlag;               //!< �s�k�t���O
    std::string             m_FileName;
    bool                    m_IsGround;                 //!< �n��ɂ��邩
    IObject*                m_Parent;                   //!< �e�̃I�u�W�F�N�g
};
