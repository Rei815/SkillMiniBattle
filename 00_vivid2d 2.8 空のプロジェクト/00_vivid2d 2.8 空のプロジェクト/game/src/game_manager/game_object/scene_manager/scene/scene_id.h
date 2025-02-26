#pragma once

enum class SCENE_ID
{
	WAIT,				//!< ダミーID
	TITLE,				//!< タイトルシーン
	SELECTMODE,			//!< モードセレクトシーン
	SELECTPLAYER,		//!< プレイヤーセレクトシーン
	SELECTGAME,			//!< ゲームを決めるシーン
	SELECTSKILL,		//!< スキルを決めるシーン
	GAMEMAIN,			//!< ゲームメインシーン
	FALLGAME,			//!< フォールゲームシーン
	DARUMAFALLDOWN,		//!< ダルマさんが転んだゲームシーン
	DODGEBALLGAME,		//!< ドッジボールゲームシーン
	BELTCONVEYORGAME,	//!< ベルトコンベアゲームシーン
	MAZE_GAME,			//!< 迷路ゲームシーン
	DEBUGGAME,			//!< デバッグゲームシーン
	RESULT_MINIGAME,	//!< ミニゲームリザルトシーン
	RESULT_GAME,		//!< ミニゲームリザルトシーン
	ENTRY,				//!< エントリーシーン


	MAX			//!< シーンID数
};