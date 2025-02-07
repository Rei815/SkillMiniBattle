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
	DARUMAFALLDOWN,		//!< ダルマさんが転んだシーン
	DODGEBALLGAME,		//!< ドッジボールゲームシーン
	BELTCONVEYORGAME,	//!< ベルトコンベアゲームシーン
	DEBUGGAME,			//!< デバッグゲームシーン
	RESULT_MINIGAME,	//!< ミニゲームリザルトシーン
	RESULT_GAME,		//!< ミニゲームリザルトシーン


	MAX			//!< シーンID数
};