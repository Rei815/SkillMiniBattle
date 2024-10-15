#pragma once
#include "../../../../model_manager/model/model.h"

class CDaruma_FallDownObject
{
public:
    CDaruma_FallDownObject();
    ~CDaruma_FallDownObject();

    /*!
     *  @brief      初期化
     *
     */
    void    Initialize(void);

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
    CModel			m_Model;
    CTransform		m_Transform;
    std::string     m_FileName;     //3Dモデルを指定するファイルパスの名前（例. data\\Models\\boss.mv1）
};