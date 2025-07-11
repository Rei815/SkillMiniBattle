#pragma once

enum class GAME_OBJECT_TAG
{
    UNTAGGED, // ������
    PLAYER,
    FLOOR,    
    WALL,   
    GIMMICK,
    BULLET,
};

enum class FACTION_CATEGORY
{
    NEUTRAL, // �����i�ǂȂǁA�N�ɂ��e�����Ȃ��E����Ȃ��j
    PLAYER,  // �v���C���[�w�c
	PLAYER1, // �v���C���[1�w�c
	PLAYER2, // �v���C���[2�w�c
	PLAYER3, // �v���C���[3�w�c
	PLAYER4, // �v���C���[4�w�c

    
    ENEMY,   // �G�w�c
    GIMMICK, // ���������U�����Ă���M�~�b�N�Ȃ�
};