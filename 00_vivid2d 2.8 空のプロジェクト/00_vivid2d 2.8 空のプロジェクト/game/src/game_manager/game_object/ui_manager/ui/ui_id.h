#pragma once

/*!
 *  @brief      UIのID
 */
enum class UI_ID
{
    NONE,
    PAUSE,              //!< 一時停止
    FALLOUT_TOPIC,      //!< フォールアウトのお題
    FALLOUT_TOPIC_BG,   //!< フォールアウトのお題の背景
    TOPIC_SHUTTER,      //!< お題を隠すシャッター
    PLANE_GAME_IMAGE,   //!< ミニゲーム選択シーンでの平面の回転するサムネイル
    MENU_BG,            //!< メニューの背景
    MENU_POSTER,        //!< メニューポスター
    SCENE_TITLE,        //!< シーンのタイトル(ゲーム説明、スキル選択で使用)
    SKILL_ICON,         //!< スキルアイコン
    SKILL_GAUGE,        //!< スキルゲージ
    SKILL_CURSOR,       //!< スキルカーソル
    SKILL_NAME,         //!< スキル名
    SKILL_INFO,         //!< スキルの情報
    SKILL_VIDEO,        //!< スキルの動画
    FINISH_GAME_BG,     //!< ミニゲーム終了時の背景
    TITLE_LOGO,         //!< タイトルロゴ
    START_COUNTDOWN,    //!< 開始時のカウントダウン
    START_TEXT,         //!< スタートの文字
    FINISH_TEXT,        //!< フィニッシュの文字
    KEY,                //!< リザルトでもらえる鍵
    KEY_BG,             //!< 鍵の背景(黒一色)
    GAME_BG,            //!< 各ゲームの背景
    SCENE_UI_PARENT,    //!< シーンのUIの親(全てのUIを上下移動させる)
    TITLE_BUTTON,       //!< タイトルボタン
    GAME_VIDEO,         //!< ミニゲームの動画
    MINIGAME_TITLE,     //!< ミニゲームのタイトル
    MINIGAME_MANUAL,    //!< ミニゲームの操作説明
    MINIGAME_OVERVIEW,  //!< ミニゲームの概要
    PLAYER_READY,       //!< プレイヤーの準備状態の表示
    NOTICE,             //!< 張り紙
    NOTICE_WIDE,        //!< 横長の張り紙
    TEXT_MANUAL,        //!< 操作説明のテキスト
    TEXT_OVERVIEW,      //!< 概要のテキスト
    PLAYER_ICON,        //!< 各プレイヤーのアイコン
    CONCENTRATION_LINE, //!< ゲームリザルトシーンの背景(集中線)
    RESULT_WINNER,      //!< ゲームリザルトシーンで誰が勝利したかを表示
    ENTRY_X_BUTTON,     //!< エントリーシーン内でXボタンによるエントリー可能を伝える
    PLAYER_JOIN,        //!< どのプレイヤーが参加したかを表示
};
