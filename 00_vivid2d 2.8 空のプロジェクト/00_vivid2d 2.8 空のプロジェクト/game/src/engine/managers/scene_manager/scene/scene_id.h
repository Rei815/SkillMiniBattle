#pragma once

enum class SCENE_ID
{
	DUMMY,					//!< ダミーID
	TITLE,					//!< タイトルシーン
	GAME_ROLL_AND_REVEAL,	//!< ゲームが選出され、情報が流れるシーン
	SELECT_SKILL,			//!< スキルを決めるシーン
	GAME_MAIN,				//!< ゲームメインシーン
	FALL_GAME,				//!< フォールゲームシーン
	DARUMA_FALLDOWN_GAME,	//!< ダルマさんが転んだゲームシーン
	DODGEBALL_GAME,			//!< ドッジボールゲームシーン
	BELTCONVEYOR_GAME,		//!< ベルトコンベアゲームシーン
	MINIGAME_RESULT,		//!< ミニゲームの結果発表シーン
	GAME_RESULT,			//!< 結果発表シーン
	ENTRY,					//!< エントリーシーン
	MAX						//!< シーンID数
};