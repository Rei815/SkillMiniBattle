#pragma once

enum class GameObjectTag
{
    UNTAGGED, // 未分類
    PLAYER,
    FLOOR,    // ★全ての床にこのタグを使う
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