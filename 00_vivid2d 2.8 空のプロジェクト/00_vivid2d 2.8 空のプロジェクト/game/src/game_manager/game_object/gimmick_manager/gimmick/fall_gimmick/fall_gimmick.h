
#pragma once
#include "..\gimmick.h"
#include <list>
class CFallGimmick : public CGimmick
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     */
    CFallGimmick();

    /*!
     *  @brief      デストラクタ
     */
    ~CFallGimmick(void);

    /*!
     *  @brief      初期化
     *
     */
    void    Initialize(IObject* object);

    /*!
     *  @brief      初期化
     *  @param[in]  object          オブジェクトのポインタ
     *  @param[in]  timer           タイマーの設定
     *
     */
    void    Initialize(IObject* object, float time);

    /*!
     *  @brief      更新
     */
    void    Update(void);

    /*!
     *  @brief      解放
     */
    void    Finalize(void);

private:
    static const float  m_fall_speed;       //!< 落ちる速度
    static const float  m_remove_height;    //!< 元に戻る高さ
    static const float  m_remove_time;      //!< 元に戻るまでの時間
    float               m_StartHeight;      //!< 初期の高さ

};
