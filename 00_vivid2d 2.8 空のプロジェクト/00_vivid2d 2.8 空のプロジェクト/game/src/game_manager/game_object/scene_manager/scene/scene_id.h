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
	RESULT_MINIGAME,	//!< ミニゲームリザルトシーン
	RESULT_GAME,		//!< ゲーム全体リザルトシーン
	ENTRY,				//!< エントリーシーン

	DEBUGGAME,			//!< デバッグゲームシーン

	MAX			//!< シーンID数
};