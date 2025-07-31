#pragma once
#include "../../../engine/core/component/component.h"
#include "../../../engine/mathematics/vector/vector3/vector3.h"
#include "../../../engine/utility/timer/timer.h"
#include "player_id.h"
#include <memory>
#include "../../../engine/utility/transform/transform.h"
#include "../../../engine/managers/bullet_manager/bullet/bullet.h"

// �O���錾
class CController;
class CSkill;
class TransformComponent;

// �v���C���[�̏��
enum class PLAYER_STATE
{
	APPEAR,     //!< �o��
	PLAY,       //!< �v���C��
	DAMAGED,    //!< ��e
	DEFEAT,     //!< �s�k
};
class PlayerComponent : public IComponent
{
public:

	/*!
	 *  @brief      �R���X�g���N�^
	 *  @param[in]  id             �v���C���[ID
	 *  @param[in]  transform      �g�����X�t�H�[��
	 */
    PlayerComponent(PLAYER_ID id, CTransform transform);

	/*!
	 *  @brief      �f�X�g���N�^
	 */
    ~PlayerComponent() override = default;

	/*!
	 *  @brief      �A�^�b�`���̏�����
     * 
	 *  @param[in]  owner          �R���|�[�l���g���A�^�b�`�����I�[�i�[�I�u�W�F�N�g
	 */
    void            OnAttach(CGameObject* owner) override;

	/*!
	 *  @brief      �X�V
	 *
	 *  @param[in]  delta_time     �O�t���[������̌o�ߎ���
	 *  @param[in]  owner          �R���|�[�l���g���f�^�b�`�����I�[�i�[�I�u�W�F�N�g
	 */
    void            Update(float delta_time, CGameObject* owner) override;

    /*!
     *  @brief      ��e
     * 
     *  @param[in]  bullet          ��e�����e
     *  @param[in]  hit_position    ��e�ʒu
     */
    void            HitBullet(std::shared_ptr<IBullet> bullet, CVector3 hit_position);

    /*!
     *  @brief      �Ռ���^����
     * 
     *  @param[in]  hit_position   �Ռ��̈ʒu
     *  @param[in]  direction      ����
     *  @param[in]  power          �Ռ���
     */
    void            Impact(const CVector3& hit_position, const CVector3& direction, float power);

    /*!
     *  @brief      �v���C���[�������Ă��邩���擾
     *
     *  @return     true : �����Ă���, false: �����Ă��Ȃ�
     */
    bool            GetPlayerMoving();

	/*!
	 *  @brief      �v���C���[��ID���擾
	 *
	 *  @return     �v���C���[��ID
	 */
    PLAYER_ID       GetPlayerID() const { return m_PlayerID; }

	/*!
	 *  @brief      �s�k�t���O���擾
	 *
	 *  @return     true : �s�k���Ă���, false: �s�k���Ă��Ȃ�
	 */
    bool            IsDefeated() const { return m_DefeatFlag; }

    /*!
     *  @brief      �s�k�t���O�ݒ�
     *
     *  @param[in]  flag    �s�k�t���O
     */
    void            SetDefeated(bool flag) { m_DefeatFlag = flag; }

    /*!
     *  @brief      ���G�t���O�擾
     *
     *  @return     ���G�t���O
     */
    bool            IsInvincible(void) const { return m_InvincibleFlag; }

    /*!
     *  @brief      ���G�t���O�ݒ�
     *
     *  @param[in]  flag    ���G�t���O
     */
    void            SetInvincible(bool flag) { m_InvincibleFlag = flag; }

    /*!
     *  @brief      �X�L�����擾
     *
     *  @return     �X�L��
     */
    std::shared_ptr<CSkill>     GetSkill() const { return m_Skill; }

    /*!
	 *  @brief      �X�L����ݒ�
     *  
	 *  @param[in]  skill   �X�L��
     */
    void            SetSkill(std::shared_ptr<CSkill> skill) { m_Skill = skill; }

    /*!
	 *  @brief      �ڒn���Ă��邩���擾
     *
	 *  @return	    true    �ڒn���Ă���, false �ڒn���Ă��Ȃ�
     */
    bool            IsGround() const { return m_IsGround; }

    /*!
     *  @brief      �ڒn���Ă��邩��ݒ�
     *
     *  @param[in]  isGround �ڒn���Ă��邩�̃t���O
     */
    void            SetIsGround(bool isGround) { m_IsGround = isGround; }

    /*!
     *  @brief      �s���̉s��ݒ�
     *
     *  @param[in]  flag    �s���t���O
     */
    void            SetActionFlag(bool flag) { m_ActionFlag = flag; }

	/*!
	 *  @brief      �v���C���[�̐��ʕ����̃x�N�g�����擾
	 *
	 *  @return     ���ʕ����̃x�N�g��
	 */
    CVector3        GetForwardVector() const { return m_ForwardVector; }

	/*!
	 *  @brief      �v���C���[�̐��ʕ����̃x�N�g����ݒ�
	 *
	 *  @param[in]  forward_vector ���ʕ����̃x�N�g��
	 */
    void            SetForwardVector(const CVector3& forward_vector);

    /*!
     *  @brief      �v���C���[�̍������擾
     *
     *  @return     ����
     */
    float           GetHeight() const { return m_height; }

    /*!
     *  @brief      �v���C���[�̔��a���擾
     *
     *  @return     ���a
     */
    float           GetRadius() const { return m_radius; }

    /*!
     *  @brief      ���x���擾
     *
     *  @return     ���x
     */
    CVector3        GetVelocity() const { return m_Velocity; }

    /*!
     *  @brief      ���x��ݒ�
     *
     *  @param[in]  velocity ���x
     */
    void            SetVelocity(const CVector3& velocity) { m_Velocity = velocity; }

    /*!
     *  @brief      ��{�̏d�͂��擾
     *
     *  @return     �d��
     */
    CVector3        GetDefaultGravity() const { return m_gravity; }

    /*!
     *  @brief      �d�͂�ݒ�
     *
     *  @param[in]  gravity �d��
     */
    void            SetGravity(const CVector3& gravity) { m_Gravity = gravity; }

    /*!
     *  @brief      �ڒn���Ă���I�u�W�F�N�g��ݒ�
     *
     *  @param[in]  gameObject �I�u�W�F�N�g
     */
    void            SetGroundObject(CGameObject* gameObject) { m_GroundObject = gameObject; }
    /*!
     *  @brief      �w�O������̉e���ɂ��ړ����x�x�̃Z�b�g
     *
     *  @param[in]  velocity    �Z�b�g���鑬�x
     */
    void            SetAffectedVelocity(CVector3 velocity) { m_AffectedVelocity = velocity; }

    /*!
     *  @brief      �w�O������̉e���ɂ��ړ����x�x�̉��Z
     *
     *  @param[in]  velocity    ���Z���鑬�x
     */
    void            AddAffectedVelocity(CVector3 velocity) { m_AffectedVelocity += velocity; }

    /*!
     *  @brief      �A���t�@�l�����炵�Ă���
     * 
	 *  @param[in]  alpha   ���点��A���t�@�l�̏��
     */
    void            DecAlpha(float alpha = 0.0f);
    /*!
     *  @brief      �A���t�@�l�𑝂₷
     * 
	 *  @param[in]  alpha   �A���t�@�l�̏��
     */
    void            RevertAlpha(float alpha = 1.0f);

	/*!
	 *  @brief      �A���t�@�l��ݒ�
	 *
	 *  @@param[in]  alpha   �A���t�@�l
	 */
    void            SetAlpha(float alpha);

    /*!
     *  @brief      �X�L�����ɂ��X�s�[�h�{���̏�Z
     * 
     *  @param[in]  rate    �{��
     */
    void            MulMoveSpeedRate(float rate = 1.0f);

    /*!
     *  @brief      �X�L�����ɂ��X�s�[�h�{���̏��Z
     * 
     *  @param[in]  rate    �{��
     */
    void            DivMoveSpeedRate(float rate = 1.0f);

    /*!
     *  @brief      �X�L�����ɂ��W�����v�{���̃Z�b�g
     *
     *  @param[in]  rate    �{��
     */
    void            SetJumpPowerRate(float rate = 1.0f) { m_JumpPower = rate; }

    /*!
     *  @brief      �X�L�����ɂ��W�����v�{���̏�Z
     *
     *  @param[in]  rate    �{��
     */
    void            MulJumpPowerRate(float rate = 1.0f);

    /*!
     *  @brief      �X�L�����ɂ��W�����v�{���̏��Z
     *
     *  @param[in]  rate    �{��
     */
    void            DivJumpPowerRate(float rate = 1.0f);
    /*!
     *  @brief      ���G���ʂ̕t�^
     *
     *  @param[in]  invincible_time    ���G����
     */
    void            StartInvincible(float invincible_time);

private:

	/*!
	 *  @brief      �R���g���[���[�̓��͂Ɋ�Â��ăv���C���[�𐧌�
	 */
    void            Control();


    /*!
     *  @brief      �o��
     */
    void            Appear(void);

    /*!
     *  @brief      �v���C��
     * 
	 *  @param[in]  delta_time �O�t���[������̌o�ߎ���
     */
    void            Play(float delta_time);

	/*!
	 *  @brief      �v���C���[�̈ړ�
	 *
	 *  @param[in]  delta_time �O�t���[������̌o�ߎ���
	 */
    void            Move(float delta_time);

    /*!
	 *  @brief      ���Ƃ̏Փˏ���
     * 
	 *  @param[in]  owner  �I�[�i�[�I�u�W�F�N�g
     */
	void            HandleGroundCollisions(CGameObject* owner);

	/*!
	*   @brief      �ǂƂ̏Փˏ���
    * 
	*   @param[in]  owner  �I�[�i�[�I�u�W�F�N�g
    */
    void            HandleWallCollisions(CGameObject* owner);

	/*!
	 *  @brief      �V��Ƃ̏Փˏ���
	 *
	 *  @param[in]  owner  �I�[�i�[�I�u�W�F�N�g
	 */
    void            HandleCeilingCollisions(CGameObject* owner);

	/*!
	 *  @brief      �T�u�X�e�b�v�ł̈ړ�����
	 *
	 *  @param[in]  totalMove      ���̃t���[���ł̑��ړ���
	 *  @param[in]  maxSubsteps    �ő�T�u�X�e�b�v��
	 */
    void            SubstepMove(const CVector3& totalMove, int maxSubsteps = 5);

    static const float              m_radius;                                   //!< ���a
    static const float              m_height;                                   //!< ����
    static const float              m_model_scale;                              //!< ���f���̑傫��
    static const float              m_move_speed;                               //!< �ړ����x
    static const float              m_jump_power;                               //!< �W�����v��
    static const float              m_fly_away_speed;                           //!< ��e���̐�����ё��x
    static const float              m_max_life;                                 //!< �ő僉�C�t
    static const float              m_max_invincible_time;                      //!< ���G����
    static const float              m_fall_accelerator;                         //!< ���������x
    static const float              m_destroy_scale_adjust;                     //!< �G�t�F�N�g(destroy)�̑傫�������l
    static const float              m_alpha_speed;                              //!< �A���t�@�l�̑��x
    static const CVector3           m_move_friction;                            //!< �ړ��p������
    static const CVector3           m_gravity;                                  //!< �d�͒l
    static const int                m_invincible_visible_interval;              //!< ���G���Ԓ��̓_�ŊԊu

    static const COLOR_F       m_player_body_color[(int)PLAYER_ID::NONE];  //!< �̂̐F
    static const COLOR_F       m_player_eye_color[(int)PLAYER_ID::NONE];   //!< �ڂ̐F

    std::shared_ptr<CSkill>         m_Skill;            //!< �X�L��
    std::shared_ptr<CController>    m_Controller;       //!< �R���g���[���[
    CGameObject*                    m_GroundObject;     //!< �ڒn�������̃I�u�W�F�N�g
    PLAYER_ID                       m_PlayerID;         //!< �v���C���[ID
    PLAYER_STATE                    m_PlayerState;      //!< ���ID
    CTimer                          m_InvincibleTimer;  //!< ���G���ԃ^�C�}�[
    CVector3                        m_Accelerator;      //!< �����x�e���ɂ��ړ����x
    CVector3                        m_InitialPosition;  //!< �����ʒu
    CVector3                        m_ForwardVector;    //!< ���ʕ����̃x�N�g��
    CVector3                        m_Velocity;         //!< ���x
    CVector3                        m_AffectedVelocity; //!< �O������̉e���ɂ�鑬�x
    CVector3                        m_Gravity;          //!< �d��
    float                           m_MoveSpeedRate;    //!< �ړ����x�̔{��
    float                           m_JumpPowerRate;    //!< �W�����v�͂̔{��
    float                           m_MoveSpeed;
    float                           m_JumpPower;
    float                           m_Alpha;            //!< �A���t�@�l
    bool                            m_StopFlag;         //!< ��~�t���O
    bool                            m_FrictionFlag;     //!< �����t���O
    bool                            m_ActionFlag;       //!< �s�������L���t���O
    bool                            m_ActiveFlag;       //!< �A�N�e�B�u�t���O
    bool                            m_InvincibleFlag;   //!< ���G�t���O
    bool                            m_DefeatFlag;       //!< �s�k�t���O
    bool                            m_IsGround;         //!< �n��ɂ��邩


};