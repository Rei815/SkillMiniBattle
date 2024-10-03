
#pragma once
#include "..\gimmick.h"
#include "fall_object/fall_object.h"
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
    void    Initialize();

    /*!
     *  @brief      更新
     */
    void    Update(void);

    /*!
     *  @brief      描画
     */
    void    Draw(void);

    /*!
     *  @brief      解放
     */
    void    Finalize(void);

private:
    CFallObject     m_FallObject_1;
    CFallObject     m_FallObject_2;
    CFallObject     m_FallObject_3;
    CFallObject     m_FallObject_4;
    CFallObject     m_FallObject_5;
    CFallObject     m_FallObject_6;
};
