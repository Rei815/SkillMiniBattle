#pragma once

//当たり判定の属性
enum COLLIDER_ATTRIBUTE
{
    DUMMY_ID,       //! ダミーID
    NON_ATTRIBUTE,  //! 属性なし
    PLAYER,         //! プレイヤーコライダー
    PLAYER_BULLET,  //! プレイヤー弾コライダー
    ENEMY,          //! エネミーコライダー
    ENEMY_BULLET,   //! エネミー弾コライダー
    STATGE,         //! ステージコライダー
};