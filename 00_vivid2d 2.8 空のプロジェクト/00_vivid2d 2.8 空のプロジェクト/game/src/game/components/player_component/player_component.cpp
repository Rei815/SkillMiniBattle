#include "player_component.h"
#include "../../../engine/managers/controller_manager/controller_manager.h"
#include "../../../engine/core/game_object/game_object.h"
#include "../../../engine/components/transform_component/transform_component.h"
#include "../../../engine/components/model_component/model_component.h"
#include "../../../engine/managers/object_manager/object_manager.h"
#include "../../../engine/managers/effect_manager/effect_manager.h"
#include "../../../engine/managers/skill_manager/skill/skill.h"
const float             PlayerComponent::m_radius = 50.0f;
const float             PlayerComponent::m_height = 70.0f;
const float             PlayerComponent::m_model_scale = 0.33f;
const float             PlayerComponent::m_move_speed = 40.0f;
const float             PlayerComponent::m_jump_power = 1450.0f;
const float             PlayerComponent::m_fly_away_speed = 2400.0f;
const float             PlayerComponent::m_max_life = 3.0f;
const float             PlayerComponent::m_max_invincible_time = 1.0f;
const float             PlayerComponent::m_fall_accelerator = 0.025f;
const CVector3          PlayerComponent::m_move_friction = CVector3(0.9f, 0.975f, 0.9f);
const int               PlayerComponent::m_invincible_visible_interval = 4;
const float             PlayerComponent::m_alpha_speed = 0.025f;
const CVector3          PlayerComponent::m_gravity = CVector3(0.0f, -5000.0f, 0.0f);
const COLOR_F PlayerComponent::m_player_body_color[] =
{
    { 1.0f, 0.66f, 0.66f, 1.0f }, // Player1 (0xffffaaaa)
    { 0.66f, 0.66f, 1.0f, 1.0f }, // Player2 (0xffaaaaff)
    { 1.0f, 1.0f, 0.66f, 1.0f }, // Player3 (0xffffffaa)
    { 0.66f, 1.0f, 0.66f, 1.0f }  // Player4 (0xffaaffaa)
};

const COLOR_F PlayerComponent::m_player_eye_color[] =
{
    { 0.4f, 0.0f, 0.0f, 1.0f }, // Player1 (0xff660000)
    { 0.0f, 0.0f, 0.4f, 1.0f }, // Player2 (0xff000066)
    { 0.4f, 0.4f, 0.0f, 1.0f }, // Player3 (0xff666600)
    { 0.0f, 0.4f, 0.0f, 1.0f }  // Player4 (0xff006600)
};

PlayerComponent::PlayerComponent(PLAYER_ID id, CTransform transform)
    : m_MoveSpeedRate(1.0f)
    , m_JumpPowerRate(1.0f)
    , m_Skill(nullptr)
    , m_Accelerator(CVector3::ZERO)
    , m_InvincibleTimer(m_max_invincible_time)
    , m_StopFlag(false)
    , m_FrictionFlag(true)
    , m_ActionFlag(true)
    , m_Controller(nullptr)
    , m_ForwardVector(CVector3::FORWARD)
    , m_AffectedVelocity(CVector3::ZERO)
    , m_ActiveFlag(true)
    , m_PlayerID(id)
    , m_InvincibleFlag(false)
    , m_PlayerState(PLAYER_STATE::APPEAR)
    , m_Alpha(0.0f)
    , m_DefeatFlag(false)
    , m_Gravity(m_gravity)
	, m_IsGround(false)
    , m_GroundObject(nullptr)
	, m_Velocity(CVector3::ZERO)
	, m_MoveSpeed(m_move_speed)
	, m_JumpPower(m_jump_power)
	, m_InitialPosition(transform.position)

{
}

void PlayerComponent::OnAttach(CGameObject* owner)
{
    CControllerManager& cm = CControllerManager::GetInstance();
    CControllerManager::CONTROLLER_LIST controllerList = cm.GetList();
    CControllerManager::CONTROLLER_LIST::iterator it = controllerList.begin();
	m_Owner = owner;
    //ID�ɂ���ăJ�e�S���[�̐؂�ւ�
    switch (m_PlayerID)
    {
    case PLAYER_ID::PLAYER1:
        m_Owner->SetCategory(FACTION_CATEGORY::PLAYER1);
        break;
    case PLAYER_ID::PLAYER2:
        m_Owner->SetCategory(FACTION_CATEGORY::PLAYER2);
        break;
    case PLAYER_ID::PLAYER3:
        m_Owner->SetCategory(FACTION_CATEGORY::PLAYER3);
        break;
    case PLAYER_ID::PLAYER4:
        m_Owner->SetCategory(FACTION_CATEGORY::PLAYER4);
        break;
    }
    //�R���g���[���[�ɐݒ肳��Ă���UnitID�ƍ����Ă���ꍇ���g�̃R���g���[���[�Ƃ��Ď擾
    while (it != controllerList.end())
    {
        if ((*it)->GetPlayerID() == m_PlayerID)
        {
            m_Controller = std::shared_ptr<CController>(*it);
            break;
        }
        ++it;
    }
    auto transform = owner->GetComponent<TransformComponent>();
    owner->GetComponent<TransformComponent>()->SetScale(CVector3(m_model_scale, m_model_scale, m_model_scale));

    m_InitialPosition = transform->GetPosition();
    auto model = owner->GetComponent<ModelComponent>();
    model->SetMaterialColor(0, m_player_body_color[(int)m_PlayerID]);
    model->SetMaterialColor(1, m_player_eye_color[(int)m_PlayerID]);

    m_InvincibleTimer.SetUp(m_max_invincible_time);

    m_StopFlag = false;
    m_FrictionFlag = true;
	m_ForwardVector = CVector3::FORWARD;
    // �_�~�[�̃v���C���[�͓������A��������
    if (m_Controller->GetID() == CONTROLLER_ID::DUMMY)
    {
		m_Gravity = CVector3::ZERO;
    }
}

void PlayerComponent::Update(float delta_time, CGameObject* owner)
{
    switch (m_PlayerState)
    {
    case PLAYER_STATE::APPEAR:  Appear();           break;
    case PLAYER_STATE::PLAY:    Play(delta_time);   break;
    }

    // �킸���Ȉړ��͖������邽�߂�臒l
    const float a_little_speed = 0.01f;

    // �L�����N�^�[�ɑ��x������ꍇ�̂݁A������ς���
    if (m_Velocity.LengthSq() > a_little_speed)
    {
        // �ړ����Ă���ꍇ�F�ڕW�̌����́A�ړ������Bm_ForwardVector���X�V����B
        m_ForwardVector = CVector3(m_Velocity.x, 0.0f, m_Velocity.z).Normalize();

    }
    float targetAngle = atan2f(m_ForwardVector.x, m_ForwardVector.z) * 180.0f / DX_PI_F;

    if (!std::isnan(targetAngle))

    {
        // �v�Z�����p�x��TransformComponent�ɐݒ肷��
        auto transform = owner->GetComponent<TransformComponent>();
        if (transform)
        {
            CVector3 currentRotation = transform->GetRotation();
            transform->SetRotation({ currentRotation.x, targetAngle, currentRotation.z });
        }
    }
}
/*
 *  ��e
 */
void PlayerComponent::HitBullet(std::shared_ptr<IBullet> bullet, CVector3 hit_position)
{
    if (m_InvincibleFlag)
        return;

    m_ActionFlag = false;
    m_FrictionFlag = false;
    m_InvincibleFlag = true;
    m_IsGround = false;
    m_Accelerator = CVector3::ZERO;
    m_Accelerator.y = m_jump_power;

    //�Ռ���^����
    Impact(hit_position, bullet->GetVelocity().Normalize(), bullet->GetPower());
}

/*
*  �Ռ�
*/
void PlayerComponent::Impact(const CVector3& hit_position, const CVector3& direction, float power)
{
    auto transform = m_Owner->GetComponent<TransformComponent>();
    //���������������擾
    CVector3 TempVelocity = (transform->GetPosition() -hit_position);

    //���������̑��x�͍Ō�Ɍv�Z����̂ŁA��x�[���ɂ���
    TempVelocity.y = 0.0f;

    //�x�N�g���̑傫�����Q�ɂ���
    TempVelocity = TempVelocity.Normalize() * 2.0f;

    //�e�̑��x�x�N�g���̑傫�����P�ɂ��ĉ��Z����i�������������ƒe�̑��x���^�t�̏ꍇ�ɁA���������̑��x���ł��������̂�h�����߁j
    TempVelocity += direction;

    //���������̑��x�͍Ō�Ɍv�Z����̂ŁA�Ăу[���ɂ���
    TempVelocity.y = 0.0f;

    //���x��{���Œ������邽�߁A�x�N�g���̑傫�����P�ɂ���
    TempVelocity = TempVelocity.Normalize();

    //���������̃x�N�g����ǉ�
    TempVelocity.y = 0.2f;

    //���g�̈ړ����x���[���ɂ��A�O������̉e���ɂ��ړ����x���x�N�g���Ƃ��̔{���ŃZ�b�g����
    m_Velocity = CVector3::ZERO;

    // 2. �v�Z����������΂��x�N�g�����A���� m_Velocity �ɉ��Z����I
    m_Velocity += TempVelocity * m_fly_away_speed * power;

}

bool PlayerComponent::GetPlayerMoving()
{
    if (m_Controller == nullptr) return false;
    bool Input = false;

    if (m_Controller)
    {
        vivid::Vector2 stick = m_Controller->GetLeftStick();

        CVector3 moveDir(stick.x, 0.0f, -stick.y);
        // �X�e�B�b�N�̃f�b�h�]�[���i�������̈�j�����B
        // �A�i���O�X�e�B�b�N�̂킸���ȌX����A�j���[�g�����|�W�V�����̃Y���𖳎�����B
        // LengthSq()�͕����̒l�Ȃ̂ŁA0.5f�͎��ۂ̃X�e�B�b�N���͂̑傫������0.7�ȏ�̏ꍇ�ɔ������邱�Ƃ��Ӗ�����B
        if (moveDir.LengthSq() > 0.5f && !m_StopFlag) // �킸���ȓ��͂̃u���͖���
        {
            Input = true;

        }

        //�W�����v
        if (m_Controller->GetButtonDown(BUTTON_ID::A) && !m_StopFlag)
            Input = true;

    }


    return Input;
}

void PlayerComponent::SetForwardVector(const CVector3& forward_vector)
{
    if (forward_vector != CVector3::ZERO)
    {
        m_ForwardVector = forward_vector;
    }
}

void PlayerComponent::StartInvincible(float invincible_time)
{
    m_InvincibleFlag = true;
    m_InvincibleTimer.SetUp(invincible_time);
}

void PlayerComponent::DecAlpha(float alpha)
{
    //�A���t�@�l���ݒ�l�ɂȂ�����I��
    if (m_Alpha == alpha)
    {
        m_Alpha = alpha;
        return;
    }

    if (m_Alpha > 0.0f)
        m_Alpha -= m_alpha_speed;
    else
        m_Alpha = 0.0f;

    auto ModelComp = m_Owner->GetComponent<ModelComponent>();
    ModelComp->SetAlpha(m_Alpha);

}

void PlayerComponent::RevertAlpha(float alpha)
{
    //�A���t�@�l���ݒ�l�ɂȂ�����I��
    if (m_Alpha >= alpha)
    {
        m_Alpha = alpha;
        return;
    }

    m_Alpha += m_alpha_speed;

    auto ModelComp = m_Owner->GetComponent<ModelComponent>();
    ModelComp->SetAlpha(m_Alpha);
}

void PlayerComponent::SetAlpha(float alpha)
{
    m_Alpha = alpha;
    auto ModelComp = m_Owner->GetComponent<ModelComponent>();
    ModelComp->SetAlpha(m_Alpha);

}

void PlayerComponent::MulMoveSpeedRate(float rate)
{
    if (rate == 0.0f)
        return;

    m_MoveSpeedRate = m_MoveSpeedRate * rate;
}

void PlayerComponent::DivMoveSpeedRate(float rate)
{
    if (rate == 0.0f)
        return;

    m_MoveSpeedRate = m_MoveSpeedRate / rate;
}

void PlayerComponent::MulJumpPowerRate(float rate)
{
    if (rate == 0.0f)
        return;

    m_JumpPowerRate = m_JumpPowerRate * rate;
}

void PlayerComponent::DivJumpPowerRate(float rate)
{
    if (rate == 0.0f)
        return;

    m_JumpPowerRate = m_JumpPowerRate / rate;
}

void PlayerComponent::Control(void)
{
    if (m_Controller == nullptr) return;
    vivid::Vector2 stick = m_Controller->GetLeftStick();
    // �X�e�B�b�N�̓��͂���A�s�����������̃x�N�g�������
    // �R���g���[���[�͏�������}�C�i�X�ŕԂ��Ă��邱�Ƃ��������߁AZ�����͔��]
    CVector3 moveDir(stick.x, 0.0f, -stick.y);

    // �x�N�g���̒����������ł�����΁i�����͂�����΁j��������
    if (moveDir.LengthSq() > 0.01f) // �킸���ȓ��͂̃u���͖���
    {
        // �x�N�g���𐳋K�����āA������K�� 1 �ɂ���
        moveDir.Normalize();

        // ����1�̕����ɁA�{���̈ړ����x���|���ė͂����肷��
        m_Accelerator.x = moveDir.x * m_move_speed * m_MoveSpeedRate;
        m_Accelerator.z = moveDir.z * m_move_speed * m_MoveSpeedRate;
    }

    //�W�����v
    if (m_Controller->GetButtonDown(BUTTON_ID::A) && !m_StopFlag)
        if (m_IsGround == true)
        {
            m_GroundObject = nullptr;
            m_IsGround = false;

            m_Accelerator.y = m_jump_power * m_JumpPowerRate;

            auto transform = m_Owner->GetComponent<TransformComponent>();
            CEffectManager::GetInstance().Create(EFFECT_ID::JUMP, transform->GetPosition());

        }

    //�X�L��
    if (m_Skill != nullptr)
        if (m_Controller->GetButtonDown(BUTTON_ID::B) && !m_StopFlag)
            m_Skill->Action();

}

void PlayerComponent::Appear(void)
{
    RevertAlpha();
    if (m_Alpha == 1.0f)
        m_PlayerState = PLAYER_STATE::PLAY;
}

void PlayerComponent::Play(float delta_time)
{

    if (m_ActionFlag)
        Control();
    Move(delta_time);

	// ���G���Ԓ��̏���
    if (!m_InvincibleFlag)
        return;

    m_InvincibleTimer.Update();
    if (m_InvincibleTimer.Finished())
    {
        m_InvincibleTimer.SetUp(m_max_invincible_time);

        m_InvincibleFlag = false;
    }

}

void PlayerComponent::Move(float delta_time)
{
    if (!m_IsGround)
    {
        m_Velocity.y += m_Gravity.y * delta_time;
    }
    m_Velocity += m_Accelerator;
    CVector3 total_velocity = m_Velocity + m_AffectedVelocity;
    CVector3 totalMoveThisFrame = total_velocity * delta_time;


    SubstepMove(totalMoveThisFrame);

    if (m_FrictionFlag)
    {
        m_Velocity.x *= m_move_friction.x;
        m_Velocity.z *= m_move_friction.z;
    }
    m_Accelerator = CVector3::ZERO;
    m_AffectedVelocity = CVector3::ZERO;
}

void PlayerComponent::HandleGroundCollisions(CGameObject* owner)
{
    auto transform = m_Owner->GetComponent<TransformComponent>();
    if (!transform) return;
    CObjectManager& om = CObjectManager::GetInstance();

    const float ground_check_line_length = 100.0f;
    const float ground_check_offset = m_radius * 0.7f;
    bool foundGroundThisFrame = false;
    float highestGroundY = -FLT_MAX;
    CGameObject* tempGroundObject = nullptr;

    for (int i = 0; i < 9; i++)
    {
        float groundMultiplier = 1.0f;

        // ���̔�����~�̂悤�ɂ��邽�߂̔{���ݒ�
        if ((i % 3) != 1 && (i / 3) != 1)
            groundMultiplier = sinf(45.0f * DX_PI_F / 180.0f);
        CVector3 currentPos = transform->GetPosition();

        CVector3 startPos = currentPos + CVector3((-ground_check_offset + ground_check_offset * (i % 3)) * groundMultiplier, 0.0f, (-ground_check_offset + ground_check_offset * (i / 3)) * groundMultiplier);
        CVector3 endPos = startPos - CVector3(0, ground_check_line_length, 0);
        CollisionResult hitResult;

        if (auto hitObject = om.CheckHitLineForAll(startPos, endPos, m_Owner, hitResult))
        {
            if (hitObject->GetTag() == GAME_OBJECT_TAG::FLOOR)
            {
                // hitNormal: ���C�����������ʂ̖@���i�ʂɐ����ȃx�N�g���j
                // CVector3::UP: �^��������x�N�g��(0, 1, 0)
                 // 2�̃x�N�g���̓��ς��v�Z���A�ʂ̌X���𒲂ׂ�
                float dot = CVector3::Dot(hitResult.hitNormal, CVector3::UP);
                // ���ς̒l��1�ɋ߂��قǁA�@�����^��������Ă���i�����R�Ȓn�ʂł���j���Ƃ�����
                 // 0.9f �͖�25.8�x�ȉ��̌X�΂��u������n�ʁv�Ƃ݂Ȃ��A�Ƃ����ݒ�
                if (dot > 0.9f)
                {
                    foundGroundThisFrame = true;
                    tempGroundObject = hitObject.get();

                    // 9�{�̃��C�̒��ŁA�ł������ʒu�ɂ���n�ʂ�Y���W���L�^����
                    if (hitResult.hitPosition.y > highestGroundY)
                    {
                        highestGroundY = hitResult.hitPosition.y;
                    }
                }
            }
        }
    }

    CVector3 currentPos = transform->GetPosition();
    float distanceToGround = currentPos.y - (highestGroundY + m_height / 2.0f);

    // �u�n�ʂ�������v�u�������v�ŁA���u�n�ʂ������̂����߂��ɂ���v�ꍇ�̂ݐڒn���Ă���Ƃ݂Ȃ�
    const float snap_distance = 10.0f; // ���̋����ȓ��Ȃ�z���t��
    if (foundGroundThisFrame && m_Velocity.y <= 0 && distanceToGround <= snap_distance)
    {
        //�@���̕\�ʂ̍���
        float groundSurfaceY = highestGroundY + (m_height / 2.0f);

        m_IsGround = true;
        m_GroundObject = tempGroundObject;
        m_Velocity.y = 0;
        transform->SetPosition({ currentPos.x, groundSurfaceY, currentPos.z });
    }
    else
    {
        m_IsGround = false;
        m_GroundObject = nullptr;
    }

}


void PlayerComponent::HandleWallCollisions(CGameObject* owner)
{
    auto transform = owner->GetComponent<TransformComponent>();
    if (!transform) return;

    // 8�����i45�x���Ɓj�Ƀ��C���΂��ĕǂ��`�F�b�N
    for (int i = 0; i < 8; ++i)
    {
        CVector3 currentPos = transform->GetPosition();

        // �`�F�b�N��������̃x�N�g�����v�Z
        // �v���C���[�̑O������ɉ�]������ƁA�J�����ɒǏ]����ړ��Ȃǂŕ֗�
        // �����ł͒P�����̂��߁A���[���h���W��Z+��O���Ƃ��Čv�Z���܂�
        float angle = 45.0f * i;
        CVector3 checkDir = CVector3(sinf(angle * DX_PI_F / 180.0f), 0.0f, cosf(angle * DX_PI_F / 180.0f));

        // ���C�̎n�_�ƏI�_
        CVector3 startPos = currentPos;
        // ���C�̒����̓L�����N�^�[�̔��a�Ɠ����ɂ���
        CVector3 endPos = startPos + checkDir * m_radius;

        CollisionResult hitResult;
        // �������g�����O���āA�����Ƒ��̃I�u�W�F�N�g�̓����蔻����s��
        if (auto hitObject = CObjectManager::GetInstance().CheckHitLineForAll(startPos, endPos, owner, hitResult))
        {
            if (hitObject->GetTag() == GAME_OBJECT_TAG::WALL || hitObject->GetTag() == GAME_OBJECT_TAG::FLOOR)
            {
                // �q�b�g�����ꍇ�A�߂荞�񂾕����������o��
                CVector3 pushBackVector = endPos - hitResult.hitPosition;
                transform->Translate(-pushBackVector);
                // 2. �Ǖ����ɐi�����Ƃ��鑬�x��ł������i���蔲���΍�j
                CVector3 wallNormal = -checkDir; // �ǂ̖@���́A���C�̌����Ƌt
                float speedIntoWall = CVector3::Dot(m_Velocity, wallNormal);

                // �ǂɌ��������x����������ꍇ
                if (speedIntoWall > 0)
                {
                    // ���̑��x������ł������x�N�g���𑬓x�������
                    m_Velocity -= wallNormal * speedIntoWall;
                }
            }
        }
    }
}

void PlayerComponent::HandleCeilingCollisions(CGameObject* owner)
{
    auto transform = owner->GetComponent<TransformComponent>();
    if (!transform) return;

    // �㏸���łȂ���ΓV��Փ˔���͕s�v
    if (m_Velocity.y <= 0)
    {
        return;
    }

    // ���C�̒������`�i�L�����N�^�[�̔����̍��� + ���j
    const float rayLength = (m_height / 2.0f) + 5.0f;
    // ���C���΂��ʒu�̐��������̃I�t�Z�b�g
    const float rayHorizontalOffset = m_radius * 0.7f;

    CVector3 currentPos = transform->GetPosition();
    // �L�����N�^�[�̒��S���瓪��֌�������3x3�̊i�q��Ƀ��C���΂�
    for (int i = 0; i < 9; i++)
    {
        // �i�q��̃��C�̃I�t�Z�b�g���v�Z
        float col = static_cast<float>(i % 3) - 1.0f; // ���ʂ� -1, 0, 1 �̂����ꂩ
        float row = static_cast<float>(i / 3) - 1.0f; // ���ʂ� -1, 0, 1 �̂����ꂩ

        CVector3 offset(col * rayHorizontalOffset, 0.0f, row * rayHorizontalOffset);

        // �l���̃��C�̒����𒲐����A�~�`�ɋ߂Â���
        if (col != 0.0f && row != 0.0f)
        {
            offset *= 0.707f; // sin(45�x) �̋ߎ��l
        }   
        
        // ���C�̎n�_�ƏI�_
        CVector3 startPos = currentPos + offset;
        CVector3 endPos = startPos + CVector3(0.0f, rayLength, 0.0f); // Y+�����i��j��

        CollisionResult hitResult;

        if (auto hitObject = CObjectManager::GetInstance().CheckHitLineForAll(startPos, endPos, owner, hitResult))
        {
            if (hitObject->GetTag() == GAME_OBJECT_TAG::WALL || hitObject->GetTag() == GAME_OBJECT_TAG::FLOOR)
            {
                // �V��ɏՓ˂����ꍇ�AY�����̑��x��0�ɂ���
                m_Velocity.y = 0;

                // �߂荞�ݕ����v�Z���ĉ����߂�
                float penetrationDepth = endPos.y - hitResult.hitPosition.y;
                transform->Translate(CVector3(0.0f, -penetrationDepth, 0.0f));

                // 1�_�ł��Փ˂�����A���̃t���[���ł̓V�䔻��͏I�����ėǂ�
                return;
            }
        }
    }
}

void PlayerComponent::SubstepMove(const CVector3& totalMove, int maxSubsteps)
{
    auto transform = m_Owner->GetComponent<TransformComponent>();
    if (!transform) return;

    float totalMoveLength = totalMove.Length(totalMove);
    if (totalMoveLength < 0.001f) return;

    // �T�u�X�e�b�v�̉񐔂��v�Z
    int substeps = static_cast<int>(ceilf(totalMoveLength / (m_radius * 0.5f)));
    if (substeps > maxSubsteps) substeps = maxSubsteps;
    if (substeps < 1) substeps = 1;

    // 1�T�u�X�e�b�v������̈ړ���
    CVector3 substepMove = totalMove / static_cast<float>(substeps);

    // �������Ĉړ��ƏՓ˔�����J��Ԃ�
    for (int i = 0; i < substeps; ++i)
    {
        // === ���������̈ړ� (X��Z�𕪗�) ===

        //�܂���X�������ɓ�����
        transform->Translate(CVector3(substepMove.x, 0.0f, 0.0f));
        HandleWallCollisions(m_Owner); // �ǂ̏Փ˔���

        //����Z�������ɓ�����
        transform->Translate(CVector3(0.0f, 0.0f, substepMove.z));
        HandleWallCollisions(m_Owner); // �ǂ̏Փ˔���


        // === ���������̈ړ� (�n�ʂƓV��) ===

        //�Ō��Y�������ɓ�����
        transform->Translate(CVector3(0.0f, substepMove.y, 0.0f));

        if (substepMove.y > 0)
        {
            // �㏸���͓V��Ƃ̔���
            HandleCeilingCollisions(m_Owner);
        }
        else
        {
            // �������͒n�ʂƂ̔���
            HandleGroundCollisions(m_Owner);
        }
    }
}