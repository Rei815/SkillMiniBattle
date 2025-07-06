#pragma once
enum class OBJECT_ID
{
    NONE, // ������ID

    // --- �v���C���[�Ƃ��đ��삷��I�u�W�F�N�g ---
    PLAYER,
    // --- �����I�u�W�F�N�g ---
    FALL_FLOOR_CIRCLE,
    FALL_FLOOR_CROSS,
    FALL_FLOOR_MOON,
    FALL_FLOOR_SQUARE,
    FALL_FLOOR_SUN,
    FALL_FLOOR_TRIANGLE,

    // --- �X�e�[�W�\���� ---
    CANNON,
    BELT_CONVEYOR,
    BELT_CONVEYOR_OBSTRUCTION_1,
    BELT_CONVEYOR_OBSTRUCTION_2,
    BELT_CONVEYOR_OBSTRUCTION_3,
    BELT_CONVEYOR_OBSTRUCTION_4,
    BELT_CONVEYOR_OBSTRUCTION_5,
    BELT_CONVEYOR_OBSTRUCTION_6,
    DARUMA_FALLDOWN_STAGE,
    DODGEBALL_STAGE,
    FALL_OUT_FLOOR,
    OGRE,

    // --- �X�L���ɂ���Đ��������I�u�W�F�N�g ---
    SKILL_WALL,
    SKILL_MIMICRY_OBJECT,
    SKILL_BARRIER_OBJECT,
    // --- �X�L���ɂ���Đ��������I�u�W�F�N�g ---
    FALL_GIMMICK,               //!< �����M�~�b�N
    DARUMA_FALLDOWN_GIMMICK,    //!< ����܂��񂪓]�񂾃M�~�b�N
    DODGEBALL_GIMMICK,          //!< �h�b�W�{�[���M�~�b�N
    BELT_CONVEYOR_GIMMICK,      //!< �x���g�R���x�A�M�~�b�N
    MAX,                        //!< ID�̑���
};