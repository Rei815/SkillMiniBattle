#pragma once

enum class GameObjectTag
{
    UNTAGGED, // ������
    PLAYER,
    FLOOR,    // ���S�Ă̏��ɂ��̃^�O���g��
    GIMMICK,
    BULLET,
};

enum class FACTION_CATEGORY
{
    NEUTRAL, // �����i�ǂȂǁA�N�ɂ��e�����Ȃ��E����Ȃ��j
    PLAYER,  // �v���C���[�w�c
    ENEMY,   // �G�w�c
    GIMMICK, // ���������U�����Ă���M�~�b�N�Ȃ�
};