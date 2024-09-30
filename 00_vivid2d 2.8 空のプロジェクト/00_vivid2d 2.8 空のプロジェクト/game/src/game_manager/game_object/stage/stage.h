#pragma once
#include "../model_manager/model/model.h"
#include "../bullet_manager/bullet/bullet.h"
#include "../../../collider/box_collider/box_collider.h"

class CStage
{
public:
    /*!
     *  @brief      インスタンスの取得
     *
     *  @return     インスタンス
     */
    static CStage& GetInstance(void);

    /*!
     *  @brief      初期化
     */
    void        Initialize(void);

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
     *  @brief      モデル取得
     */
    CModel        GetModel() const;

    /*!
     *  @brief      モデルとの判定
     */
    void CheckHitUnit();
    

    /*!
    *  @brief      ステージの高さ取得
    */
    int        GetHeight() const;

    /*!
     *  @brief      ステージの横幅取得
     */
    int        GetWidth() const;

    /*!
     *  @brief      ステージの奥行取得
     */
    int        GetDebth() const;

private:
    /*!
     *  @brief      コンストラクタ
     */
    CStage(void);

    /*!
     *  @brief      コピーコンストラクタ
     *
     *  @param[in]  rhs     オブジェクト
     */
    CStage(const CStage& rhs);

    /*!
     *  @brief      デストラクタ
     */
    ~CStage(void);

    /*!
     *  @brief      代入演算子
     *
     *  @param[in]  rhs 代入オブジェクト
     *
     *  @return     自身のオブジェクト
     */
    CStage& operator=(const CStage& rhs);
    static const int       m_stage_height;
    static const int       m_stage_width;
    static const int       m_stage_debth;
	CModel          m_Model;
    CTransform      m_Transform;
    CBoxCollider    m_BoxCollider;
};