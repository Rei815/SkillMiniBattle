
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
     *  @param[in]  object       オブジェクト
     */
    void    Initialize(std::shared_ptr<IObject> object);


    /*!
     *  @brief      更新
     */
    void    Update(void);

    /*!
     *  @brief      解放
     */
    void    Finalize(void);

    /*!
     *  @brief      元に戻るまでの時間の設定
     *  @param[in]  float       時間
     */
    void   AddReturnTime(float time);
private:
    static const float  m_fall_speed;       //!< 落ちる速度
    static const float  m_return_height;    //!< 元に戻る高さ
    static const float  m_return_time;      //!< 元に戻るまでの時間

    float               m_StartHeight;      //!< 初期の高さ
    float               m_ReturnTime;       //!< 元に戻るまでの時間
    CTimer              m_ReturnTimer;      //!< 戻るまでのタイマー
};
