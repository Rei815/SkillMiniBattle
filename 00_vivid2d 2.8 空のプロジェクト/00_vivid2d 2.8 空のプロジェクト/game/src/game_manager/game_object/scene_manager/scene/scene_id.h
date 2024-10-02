#pragma once

enum class SCENE_ID
{
	WAIT,			//!< ダミーID
	TITLE,			//!< タイトルシーン
	SELECTMODE,		//!< モードセレクトシーン
	SELECTPLAYER,	//!< プレイヤーセレクトシーン
	SELECTGAME,		//!< ゲームとスキルを決めるシーン
	GAMEMAIN,		//!< ゲームメインシーン
	FALLGAME,		//!< フォールゲームシーン
	DEBUGGAME,		//!< デバッグゲームシーン
	RESULT,			//!< リザルトシーン


	MAX			//!< シーンID数
};