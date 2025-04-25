#pragma once

enum class SCENE_ID
{
	DUMMY,					//!< ダミーID
	TITLE,					//!< タイトルシーン
	RANDOM_GAME,			//!< ゲームが決められるシーン
	SELECT_SKILL,			//!< スキルを決めるシーン
	GAME_MAIN,				//!< ゲームメインシーン
	FALL_GAME,				//!< フォールゲームシーン
	DARUMA_FALLDOWN_GAME,	//!< ダルマさんが転んだゲームシーン
	DODGEBALL_GAME,			//!< ドッジボールゲームシーン
	BELTCONVEYOR_GAME,		//!< ベルトコンベアゲームシーン
	RESULT_MINIGAME,		//!< ミニゲームリザルトシーン
	RESULT_GAME,			//!< ミニゲームリザルトシーン
	ENTRY,					//!< エントリーシーン
	MAX						//!< シーンID数
};