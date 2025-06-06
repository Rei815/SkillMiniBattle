#pragma once

#include "vivid.h"
#include "..\ui.h"
#include <list>
#include <memory>
class  CSceneUIParent : public CUI
{
public:
    enum class STATE
    {
        NONE,
        WAIT,
        FINISH,
        MOVE_ONE,
        BACK_ONE,
    };
    /*!
     *  @brief      コンストラクタ
     */
    CSceneUIParent(UI_ID id);

    /*!
     *  @brief      デストラクタ
     */
    ~CSceneUIParent(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(const vivid::Vector2& position);

    /*!
     *  @brief      更新
     */
    void        Update(void);

    /*!
     *  @brief      描画
     */
    void        Draw(void);

    /*!
     *  @brief      解放
     */
    void        Finalize(void);

    /*!
     *  @brief      状態取得
     *
     *  @return     状態
     */
    STATE            GetState(void);

    /*!
     *  @brief      状態設定
     *
     *  @param[in]  state  状態
     */
    void            SetState(STATE state);

    /*!
     *  @brief      子との関係解除
     *
     */
    void            ReleaseChildren();
private:

    static const vivid::Vector2 m_position;             //!< 位置
    static const int            m_speed;                //!< 移動速度
    static const float			m_down_final_height;	//!< 降りるときの最終高度
    static const float			m_max_height;	        //!< 最高高度
    static const float			m_min_height;	        //!< 最低高度
    static const float			m_wait_height;	        //!< 待機する高さ

    using CHILDREN_LIST = std::list<std::shared_ptr<CUI>>;
    CHILDREN_LIST               m_ChildrenList;         //!< 子UIのリスト
    STATE                       m_State;                //!< 動きの状態
    bool                        m_WaitFlag;             //!< 待機するフラグ
};