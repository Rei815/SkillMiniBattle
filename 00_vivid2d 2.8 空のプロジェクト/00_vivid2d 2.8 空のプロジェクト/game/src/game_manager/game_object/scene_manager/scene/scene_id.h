#pragma once

enum class SCENE_ID
{
	WAIT,			//!< ダミーID
	TITLE,			//!< タイトルシーン
	SELECTMODE,		//!< モードセレクトシーン
	SELECTPLAYER,	//!< プレイヤーセレクトシーン
	SELECTGAME,		//!< ゲームとスキルを決めるシーン
	GAMEMAIN,		//!< ゲームメインシーン
	RESULT,			//!< リザルトシーン


	MAX			//!< シーンID数
};