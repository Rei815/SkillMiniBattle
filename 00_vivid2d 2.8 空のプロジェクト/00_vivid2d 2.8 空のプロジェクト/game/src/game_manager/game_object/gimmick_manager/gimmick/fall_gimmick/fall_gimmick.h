
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
    int     m_CreateTime;
    int     m_CreateTimer;
};
