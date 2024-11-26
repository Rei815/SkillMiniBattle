#pragma once

enum class SCENE_ID
{
	WAIT,			//!< ダミーID
	TITLE,			//!< タイトルシーン
	SELECTMODE,		//!< モードセレクトシーン
	SELECTPLAYER,	//!< プレイヤーセレクトシーン
	SELECTGAME,		//!< ゲームを決めるシーン
	SELECTSKILL,	//!< スキルを決めるシーン
	GAMEMAIN,		//!< ゲームメインシーン
	FALLGAME,		//!< フォールゲームシーン
	DODGEBALLGAME,	//!< ドッジボールゲームシーン
	DEBUGGAME,		//!< デバッグゲームシーン
	RESULT,			//!< リザルトシーン
	DARUMAFALLDOWN,	//!< ダルマさんが転んだシーン


	MAX			//!< シーンID数
};