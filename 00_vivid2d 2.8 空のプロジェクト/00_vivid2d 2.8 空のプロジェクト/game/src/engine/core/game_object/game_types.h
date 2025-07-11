#pragma once

enum class GAME_OBJECT_TAG
{
    UNTAGGED, // 未分類
    PLAYER,
    FLOOR,    
    WALL,   
    GIMMICK,
    BULLET,
};

enum class FACTION_CATEGORY
{
    NEUTRAL, // 中立（壁など、誰にも影響しない・されない）
    PLAYER,  // プレイヤー陣営
	PLAYER1, // プレイヤー1陣営
	PLAYER2, // プレイヤー2陣営
	PLAYER3, // プレイヤー3陣営
	PLAYER4, // プレイヤー4陣営

    
    ENEMY,   // 敵陣営
    GIMMICK, // 中立だが攻撃してくるギミックなど
};